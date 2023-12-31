#include "SkySong.h"
#include <thread>
#include "../memory/hooks.h"
#include "../memory/AddressesBase.h"

std::vector<nlohmann::ordered_json> SkySong::SheetList;
unsigned int SkySong::selected_sheet = 0;
State SkySong::state = State::Stop;

bool SkySong::ImportSheet()
{
	return requestFile("application/json", SkySong::readFile, false);
}

void SkySong::m_PlayNote(nlohmann::ordered_json& notes)
{
	for (auto& note : notes.items())
	{
		if (state != State::Play)
			return;
		uintptr_t game = skyRoots->game_ptr.get_address();
		uintptr_t KaraokeFeedback = *(uintptr_t*)(*(uintptr_t*)(game + 0x668) + 0x110);
		uintptr_t PianoButton = KaraokeFeedback + 0x50 + note.value()[0].get<int>() * 0x290;
		*(int*)(PianoButton + 0x208) = note.value()[0].get<int>();
		*(int*)(PianoButton + 0x210) = instruments[g_instrument_type].type;
		*(int*)(PianoButton + 0x224) = instruments[g_instrument_type].id;
		orig_PianoButton_OnStart(PianoButton, skyRoots->game_ptr.as_ptr());
	}
}

void SkySong::Start()
{
	LOGI(TAG_MUSIC, "Start");
	if (SkySong::SheetList.empty())
		return LOGE(TAG_MUSIC, "Sheet is empty");

	LOGI(TAG_MUSIC, "Playing a song..");
	nlohmann::ordered_json& sheet = SkySong::SheetList[SkySong::selected_sheet];
	LOGI(TAG_MUSIC, "Sheet is Empty: %s", sheet.empty() ? "true" : "false");
	for (auto& column : sheet[0]["columns"].items())
	{
		SkySong::m_PlayNote(column.value()[1]);
		std::this_thread::sleep_for(std::chrono::microseconds(MPB / sheet[0]["bpm"].get<int>()));
		if (state == State::Stop)
			return;

		if (SkySong::state == State::Pause)
			LOGI(TAG_MUSIC, "Song is paused");

		while (SkySong::state == State::Pause) {}
	}
	LOGI(TAG_MUSIC, "Song is over");
	SkySong::state = State::Skip;
}

[[noreturn]] void* SkySong::Update(void* argv)
{
	LOGI(TAG_MUSIC, "SkySong Update is on");
	while (true)
	{
		switch (SkySong::state)
		{
		case State::Stop:
			break;
		case State::Play:
			SkySong::Start();
			break;
		case State::Error:
			state = State::Skip;
			break;
		case State::Skip:
			break;
		}
	}
	LOGI(TAG_MUSIC, "SkySong Update is off");
}

void SkySong::Init()
{
	pthread_t thread;
	pthread_create(&thread, nullptr, SkySong::Update, nullptr);
	pthread_detach(thread);
}

void SkySong::readFile(int fd)
{
	FILE* file = fdopen(fd, "r");
	if (file == nullptr)
	{
		LOGE(TAG_MUSIC, "Error opening file");
		return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);

	char* buffer = new char[fileSize + 1];
	size_t bytesRead = fread(buffer, 1, fileSize, file);
	if (bytesRead != fileSize)
	{
		LOGE(TAG_MUSIC, "Error reading file");
		delete[] buffer;
		fclose(file);
		return;
	}

	buffer[fileSize] = '\0';
	fclose(file);

	try
	{
		nlohmann::ordered_json JsonSheet = nlohmann::ordered_json::parse(buffer);
		if (!JsonSheet.empty())
			LOGE(TAG_MUSIC, "Song %s imported", JsonSheet[0]["name"].get<std::string>().c_str());
		SkySong::SheetList.emplace_back(JsonSheet);
		LOGE(TAG_MUSIC, "Number of sheets %lu", SkySong::SheetList.size());
	}
	catch (const std::exception& e)
	{
		LOGE(TAG_MUSIC, "Error parsing JSON: %s", e.what());
		delete[] buffer;
		return;
	}

	delete[] buffer;
}

