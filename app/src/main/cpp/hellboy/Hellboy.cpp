#include "Hellboy.h"
#include <cstring>
#include <unistd.h>
#include "../include/misc/obfuscate.h"
#include "../include/misc/Logger.h"
#include "../memory/memory.h"
#include "../memory/AddressesBase.h"
#include "../Bootloader/Bootloader.h"
#include <map>
#include <sstream>


#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

char Hellboy::level_name[100] = "Hello, World!";
std::string Hellboy:: user_id;
std::string Hellboy::user_session;
unsigned long Hellboy::bootloader;
time_t Hellboy::candle_run_interval = 1500000;
time_t Hellboy::star_run_interval = 1500000;

Trigger trigger;

ProgessBar progress;

ImGuiStyle HellboyStyle;
ImVec4* g_Colors;

HellAddress level_name_ptr;

time_t g_farming_interval;
nlohmann::ordered_json* g_farming_coordinates = nullptr;
std::map<std::string, MenuItem>hell_menus;
std::map<std::string, Seg_Info>libBootloader_Segments;

bool g_hell_menu_collapsed;

size_t Hellboy::StringFind(const char* const str, const char* const what)
{
	bool is_found = false;
	size_t position = -1;
	size_t size_of_str = strlen(str);
	size_t size_of_what = strlen(what);

	for (size_t i = 0; i < size_of_str; ++i)
	{
		if (str[i] != what[0])
			continue;

		for (size_t j = 0; j < size_of_what; ++j)
		{
			if (what[j] != str[i + j])
			{
				is_found = false;
				break;
			}
			is_found = true;
			position = i;
		}

		if (is_found)
			break;
	}
	return position;
}

void Hellboy::GetLevel()
{
	if (level_name_ptr)
	{
		size_t endpoint = Hellboy::StringFind(level_name_ptr, OBFUSCATE("\""));
		for (int i = 0; i < sizeof(level_name) / sizeof(level_name[0]); i++)
		{
			if (i < endpoint)
				level_name[i] = level_name_ptr.as_string()[i];
			else
				level_name[i] = '\0';
		}
		return;
	}
}

void Hellboy::SetSpell(int32_t id, int socket, bool spark)
{
	uintptr_t avatar_to_89 = *(uintptr_t*)(avatars[OBFUSCATE("avatar_1")].GetAvatar() + 0x98);
	if (!avatar_to_89)
		return;
	uintptr_t spell_socket = avatar_to_89 + 0x10;

	socket = socket * 0x30 - 0x30;
	*(int*)(spell_socket + socket) = id; 							//spell set for the socket
	*(int*)(spell_socket + 0xCB4) = 25; 							//spells allowed
	*(int*)(spell_socket + socket + 0xC) = -1; 						//time set for the spell
	*(int*)(spell_socket + socket + 0x1C) = spark ? 0 : 360;		//sets the spark to be on or off
}

int* Hellboy::GetSpell(int socket)
{
	uintptr_t avatar_to_89 = *(uintptr_t*)(avatars[OBFUSCATE("avatar_1")].GetAvatar() + 0x98);
	if (!avatar_to_89)
		return nullptr;

	uintptr_t spell_socket = avatar_to_89 + 0x10;

	socket = socket * 0x30 - 0x30;
	return (int*)(spell_socket + socket);
}

void Hellboy::OpenCloset(int id)
{
	//int* closet = (int*)(*(uintptr_t*)(*(skyRoots->game_ptr.as_ptr() + 0xCD) + 0x108) + 0x54);
	uintptr_t game_ptr_cd = *(skyRoots->game_ptr.as_ptr() + 0xCD);
	if (!game_ptr_cd)
		return;
	uintptr_t closet_ptr = *(uintptr_t*)(game_ptr_cd + 0x108);
	if (!closet_ptr)
		return;

	int* closet = (int*)(closet_ptr + 0x54);
	bool* is_opened = (bool*)(closet - 0xF);
	*(bool*)(closet - 0x1) = false;
	*(bool*)(closet + 0x1) = true;
	if (*closet == id && *is_opened)
		*is_opened  = false;
	else
		*is_opened = true;
	*closet = id;
}

void Hellboy::IterationFarming(nlohmann::ordered_json& coordinates, time_t interval)
{
	if (!trigger.run_by_teleport)
		return;

	if (coordinates.empty())
	{
		progress.farming.current = 0;
		trigger.run_by_teleport = false;
		return;
	}

	progress.farming.end = (float)coordinates.size();
	for ( ;progress.farming.current < progress.farming.end; )
	{
		if (!trigger.run_by_teleport)
		{
			progress.farming.current = 0;
			return;
		}

		nlohmann::ordered_json& position = coordinates[progress.farming.current];
		avatars[OBFUSCATE("avatar_1")].Teleport({position[0], position[1], position[2]});
		if (progress.farming.current < progress.farming.end)
			usleep(interval);
		++progress.farming.current;
	}
	progress.farming.current = 0;
	trigger.run_by_teleport = false;
}

bool Hellboy::get_auth;
void Hellboy::GetUserAuth()
{
	if (!Hellboy::get_auth)
		return;
	static std::string user_key = OBFUSCATE(R"("user":")");
	static std::string session_key = OBFUSCATE(R"("session":")");
	HellAddress user_auth;

	user_auth.scan(OBFUSCATE(R"({"user":")"), OBFUSCATE("xxxxxxxxx"), ANON_SCUDO_MALLOC);

	if (!user_auth.is_address())
		return;

	std::string auth = user_auth.as_string();

	size_t user_start = auth.find(user_key) + user_key.length();
	size_t user_end = auth.find('\"', user_start);
	size_t session_start = auth.find(session_key) + session_key.length();
	size_t session_end = auth.find('\"', session_start);

	Hellboy::user_id = auth.substr(user_start, user_end - user_start);
	Hellboy::user_session = auth.substr(session_start, session_end - session_start);

	Hellboy::get_auth = false;

}

uintptr_t* GetDeviceInfo() {
	return (uintptr_t*)skyRoots->game_ptr.as_ptr()[17];
}
bool Hellboy::ScreenToWorldView(Vec4<float>& result, Vec4<float> cords)
{
	long double ret = ((long double(*)(float*, uintptr_t*, uintptr_t*, bool))(Cipher::get_libBase() + 0xD46A98))(&cords.x,
	 (skyRoots->game_ptr.as_ptr() + 0x238), GetDeviceInfo(), true);
	float* points = (float*)&ret;
	result = {points[0], points[1], points[2], points[3]};
	return true;
}

uintptr_t Hellboy::get_avatar()
{
	uintptr_t address;
	address = get_from_memory(OBFUSCATE(R"(u_localAvatarPos)"), OBFUSCATE("xxxxxxxxxxxxxxxx"), ANON_SCUDO_MALLOC, 0x20);
	if (!address)
	{
		LOGW(OBFUSCATE(TAG_MEMSCAN),  OBFUSCATE("Failed to get u_localAvatarPos"), 0);
		return 0;
	}
	skyRoots->avatar_xpos = *(uintptr_t*)address;
	LOGW(OBFUSCATE(TAG_MEMSCAN),  OBFUSCATE("pointer 1 to avatar_xpos 0x%lx"), address);

	uintptr_t avatar_pos[2] = { skyRoots->avatar_xpos.get_address() };
	uintptr_t ptr_2 = get_from_memory((char*)avatar_pos, OBFUSCATE("xxxxxxxx"), ANON_SCUDO_MALLOC, 0x0, address + 100);
	if (ptr_2)
	{
		LOGI(OBFUSCATE(TAG_MEMSCAN),  OBFUSCATE("pointer 2 to avatar_xpos 0x%lx"), ptr_2);
		return ptr_2 - 24;
	}
	LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("pointer 2 to avatar position is not found"), 0);
	return 0;
}

void Hellboy::setColors(ImGuiStyle* dst, bool trigger)
{
	static ImGuiStyle imGuiStyle{};
	if(trigger)
	{
		memcpy(&imGuiStyle, dst, sizeof(ImGuiStyle));
		ImGui::StyleColorsDark();
		ImVec4* Style = dst->Colors;
		dst->Alpha 								= 1.000f;
		dst->WindowRounding 					= 12.00f;
		dst->ChildRounding 						= 12.00f;
		dst->FrameRounding 						= 12.00f;
		dst->ScrollbarSize 						= 50.00f;
		dst->ScrollbarRounding 					= 2.000f;
		dst->GrabMinSize 						= 13.00f;
		dst->GrabRounding 						= 8.000f;
		dst->LogSliderDeadzone 					= 6.000f;
		dst->TabRounding 						= 4.000f;
		dst->TabBorderSize 						= 1.000f;
		dst->ScrollbarSize 						= 20.00f;
		dst->WindowTitleAlign 					= ImVec2(0.510f, 0.500f);
		dst->WindowPadding 						= ImVec2(9.000f, 8.000f);
		dst->DisplaySafeAreaPadding 			= ImVec2(10.00f, 3.000f);
		Style[ImGuiCol_Text] 					= ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		Style[ImGuiCol_TextDisabled] 			= ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		Style[ImGuiCol_WindowBg] 				= ImVec4(0.000f, 0.000f, 0.000f, 0.720f);
		Style[ImGuiCol_TabActive] 				= ImVec4(0.801f, 0.239f, 0.329f, 1.000f);
		Style[ImGuiCol_ChildBg] 				= ImVec4(0.070f, 0.070f, 0.070f, 0.810f);
		Style[ImGuiCol_PopupBg] 				= ImVec4(0.080f, 0.080f, 0.080f, 0.940f);
		Style[ImGuiCol_Border] 					= ImVec4(0.000f, 0.000f, 0.000f, 0.500f);
		Style[ImGuiCol_BorderShadow] 			= ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		Style[ImGuiCol_FrameBg] 				= ImVec4(0.039f, 0.039f, 0.039f, 0.353f);
		Style[ImGuiCol_FrameBgHovered] 			= ImVec4(0.000f, 0.000f, 0.000f, 0.400f);
		Style[ImGuiCol_FrameBgActive] 			= ImVec4(0.529f, 0.188f, 0.243f, 1.000f);
		Style[ImGuiCol_TitleBg] 				= ImVec4(0.039f, 0.039f, 0.039f, 0.400f);
		Style[ImGuiCol_TitleBgActive] 			= ImVec4(0.000f, 0.000f, 0.000f, 0.710f);
		Style[ImGuiCol_TitleBgCollapsed] 		= ImVec4(0.000f, 0.000f, 0.000f, 0.510f);
		Style[ImGuiCol_MenuBarBg] 				= ImVec4(0.140f, 0.140f, 0.140f, 1.000f);
		Style[ImGuiCol_ScrollbarBg] 			= ImVec4(0.020f, 0.020f, 0.020f, 0.530f);
		Style[ImGuiCol_ScrollbarGrab] 			= ImVec4(0.801f, 0.759f, 0.759f, 1.000f);
		Style[ImGuiCol_ScrollbarGrabHovered] 	= ImVec4(0.665f, 0.630f, 0.630f, 1.000f);
		Style[ImGuiCol_ScrollbarGrabActive] 	= ImVec4(0.549f, 0.501f, 0.501f, 1.000f);
		Style[ImGuiCol_CheckMark] 				= ImVec4(0.529f, 0.188f, 0.243f, 1.000f);
		Style[ImGuiCol_SliderGrab] 				= ImVec4(0.529f, 0.188f, 0.243f, 1.000f);
		Style[ImGuiCol_SliderGrabActive] 		= ImVec4(0.109f, 0.109f, 0.109f, 1.000f);
		Style[ImGuiCol_Button] 					= ImVec4(0.160f, 0.156f, 0.160f, 0.300f);
		Style[ImGuiCol_ButtonHovered] 			= ImVec4(0.529f, 0.188f, 0.243f, 1.000f);
		Style[ImGuiCol_ButtonActive] 			= ImVec4(0.260f, 0.261f, 0.261f, 1.000f);
		Style[ImGuiCol_Header] 					= ImVec4(0.350f, 0.170f, 0.190f, 0.870f);
		Style[ImGuiCol_HeaderHovered] 			= ImVec4(0.574f, 0.608f, 0.649f, 0.800f);
		Style[ImGuiCol_HeaderActive] 			= ImVec4(0.412f, 0.432f, 0.455f, 0.800f);
		Style[ImGuiCol_Separator] 				= ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		Style[ImGuiCol_SeparatorHovered] 		= ImVec4(0.749f, 1.000f, 0.996f, 1.000f);
		Style[ImGuiCol_SeparatorActive] 		= ImVec4(0.749f, 1.000f, 0.996f, 1.000f);
		Style[ImGuiCol_ResizeGrip] 				= ImVec4(0.529f, 0.188f, 0.243f, 1.000f);
		Style[ImGuiCol_ResizeGripHovered] 		= ImVec4(0.523f, 0.263f, 0.263f, 0.670f);
		Style[ImGuiCol_ResizeGripActive] 		= ImVec4(0.083f, 0.083f, 0.083f, 0.950f);
		Style[ImGuiCol_Tab] 					= ImVec4(0.252f, 0.256f, 0.260f, 0.800f);
		Style[ImGuiCol_TabHovered] 				= ImVec4(0.369f, 0.372f, 0.376f, 0.800f);
		Style[ImGuiCol_TabActive] 				= ImVec4(0.530f, 0.205f, 0.249f, 0.873f);
		Style[ImGuiCol_TabUnfocused] 			= ImVec4(0.530f, 0.205f, 0.249f, 0.873f);
		Style[ImGuiCol_TabUnfocusedActive] 		= ImVec4(0.530f, 0.205f, 0.249f, 0.873f);
		Style[ImGuiCol_PlotLines] 				= ImVec4(0.610f, 0.610f, 0.610f, 1.000f);
		Style[ImGuiCol_PlotLinesHovered] 		= ImVec4(1.000f, 0.430f, 0.350f, 1.000f);
		Style[ImGuiCol_PlotHistogram] 			= ImVec4(0.900f, 0.700f, 0.000f, 1.000f);
		Style[ImGuiCol_PlotHistogramHovered] 	= ImVec4(1.000f, 0.600f, 0.000f, 1.000f);
		Style[ImGuiCol_TextSelectedBg] 			= ImVec4(0.260f, 0.590f, 0.980f, 0.350f);
		Style[ImGuiCol_DragDropTarget] 			= ImVec4(1.000f, 1.000f, 0.000f, 0.900f);
		Style[ImGuiCol_NavHighlight] 			= ImVec4(0.260f, 0.590f, 0.980f, 1.000f);
		Style[ImGuiCol_NavWindowingHighlight] 	= ImVec4(1.000f, 1.000f, 1.000f, 0.700f);
		Style[ImGuiCol_NavWindowingDimBg] 		= ImVec4(0.800f, 0.800f, 0.800f, 0.200f);
		Style[ImGuiCol_ModalWindowDimBg] 		= ImVec4(0.800f, 0.800f, 0.800f, 0.350f);
	}
	else
		memcpy(dst, &imGuiStyle, sizeof(ImGuiStyle));
}




void Hellboy::SpeedUpAndDelay(time_t time, bool& trigger)
{
	if (!trigger)
		return;
	float game_speed = *allocations->game_speed.as_float();
	*allocations->game_speed.as_float() = 30.0f;
	std::chrono::microseconds delay(time);
	std::this_thread::sleep_for(delay);
	*allocations->game_speed.as_float() = game_speed;
	trigger = false;
}
