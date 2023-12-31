#pragma once
#include <string>
#include <sstream>
#include "Hellboy.h"
#include "../Bootloader/Bootloader.h"

class ChatBox {
	public:
	static void ScanUserMessage(std::string& p_UserMessage);
	static void GetCommandFromUserMessage(std::string message_array[]);
	static void DeleteUserMessage(std::string& p_UserMessage);
	static const char* CommandList[];
};



