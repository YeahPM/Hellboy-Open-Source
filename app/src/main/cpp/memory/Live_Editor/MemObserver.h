#pragma once

#include <fstream>
#include <sstream>
#include <android/log.h>
#include <unistd.h>
#include <unordered_map>

#include "../../include/cipher/Cipher.h"
#include "../../include/misc/Logger.h"
#include "../../include/misc/obfuscate.h"

#define TAG_MEMOBSERVER "HB-MEMOBSERVER"

#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

struct MapObject{
	uintptr_t start;
	uintptr_t end;
	size_t size;
	std::string perms;

	MapObject(uintptr_t a_start, uintptr_t a_end, size_t a_size, std::string a_perms) : start(a_start), end(a_end), size(a_size), perms(a_perms) {};
	MapObject() = default;
};

class MemObserver {
private:

	pid_t m_ProcessID;
	std::string m_PeocessDir;



public:
	MemObserver();
	std::unordered_map<std::string, MapObject> m_ProcessMap;
	void m_UpdateMap();
};
