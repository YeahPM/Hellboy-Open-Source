#include "MemObserver.h"


MemObserver::MemObserver()
{
	m_ProcessID = getpid();
	m_PeocessDir = std::string(OBFUSCATE("/proc/")) + std::to_string(m_ProcessID) + std::string(OBFUSCATE("/maps"));
	m_UpdateMap();
}

void MemObserver::m_UpdateMap()
{
	std::ifstream maps(m_PeocessDir);
	if (!maps)
	{
		LOGW(OBFUSCATE(TAG_MEMOBSERVER), OBFUSCATE("Failed to get maps"), 0);
		return;
	}

	std::string line;
	std::unordered_map<std::string, MapObject> ProcessMap;
	unsigned long map_idx = 0;
	while (std::getline(maps, line))
	{
		std::istringstream iss(line);
		std::string address, perms, offset, dev, inode, name;
		iss >> address >> perms >> offset >> dev >> inode;
		std::getline(iss, name);

		// remove whitespaces from the section's name
		name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch); }));

		char *endptr;
		unsigned long start = std::strtoul(address.substr(0, address.find('-')).c_str(), &endptr, 16);
		unsigned long end = std::strtoul(address.substr(address.find('-') + 1).c_str(), &endptr, 16);


		size_t size = end - start;
		name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch); }));

		if(name.length() == 0)
			continue;

		// remove the directory from shared libraries
		std::size_t found = name.find_last_of('/');
		if (found != std::string::npos)
			name = name.substr(found + 1);

		char nameBuff[1000];
		sprintf(nameBuff, " [%lu]", map_idx++);
		ProcessMap.emplace(nameBuff, MapObject(start, end, size, perms));

	}
	m_ProcessMap.clear();
	m_ProcessMap = ProcessMap;
}
