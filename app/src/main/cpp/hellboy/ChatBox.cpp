#include "ChatBox.h"

const char* ChatBox::CommandList[] = {
	 "tp",
	 "warp",
	 "window",
	 "reset",
};

void ChatBox::DeleteUserMessage(std::string& p_UserMessage)
{
	p_UserMessage.clear();
}

void ChatBox::GetCommandFromUserMessage(std::string message_array[])
{
	std::string command;
	for (auto& item : ChatBox::CommandList)
		if (item == message_array[1])
			command = item;

	if (command == "tp")
	{
		if (message_array[2] == "refresh")
			checkpointBarn->ChangeLevel(Hellboy::level_name);
		else if (message_array[2] == "home")
			checkpointBarn->ChangeLevel("CandleSpace");
		else
			checkpointBarn->ChangeLevel(message_array[2].c_str());
	}

	if (command == "reset")
	{
		if (message_array[2] == "hell_configs")
			HellboyIO::reset_configs();
	}

	if (command == "warp")
	{
		char* endptr;
		float position[3];
		for (int i = 0; i < 3; ++i)
		{
			position[i] = strtof(message_array[2 + i].c_str(), &endptr);
			if (*endptr != '\0')
				return;
		}
		avatars["avatar_1"].Teleport(vec3(position[0], position[1], position[2]));
	}

	if (command == "window")
		if (hell_menus.find(message_array[2] + " " + message_array[3]) != hell_menus.end())
			*hell_menus[message_array[2] + " " + message_array[3]].state() = !*hell_menus[message_array[2]].state();

}

void ChatBox::ScanUserMessage(std::string& p_UserMessage)
{
#define PREFIX "-kj"
	if (p_UserMessage.find(PREFIX) == std::string::npos)
		return;

	std::stringstream stream(p_UserMessage);
	std::string line[20];
	for (int i = 0; stream.good() && i < 20; ++i)
		stream >> line[i];

	ChatBox::GetCommandFromUserMessage(line);
	ChatBox::DeleteUserMessage(p_UserMessage);
}
