#include "memory.h"

#include <fstream>
#include <sstream>
#include <android/log.h>
#include <unistd.h>

#include "../include/cipher/Cipher.h"
#include "../include/misc/Logger.h"
#include "../include/misc/obfuscate.h"

#ifdef RELEASE_MODE
#define OBFUSCATE(data) AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

bool scudo_detected;
bool malloc_detected;
bool find_scudo_section()
{
	if (scudo_detected)
		return scudo_detected;

	if (malloc_detected)
		return !malloc_detected;

	static pid_t pid = getpid();
	std::string maps_file = std::string(OBFUSCATE("/proc/")) + std::to_string(pid) + std::string(OBFUSCATE("/maps"));
	std::ifstream maps(maps_file);
	if (!maps)
	{
		LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Failed to open %s"), maps_file.c_str());
		return false;
	}

	std::string line;
	while (std::getline(maps, line))
	{
		std::istringstream iss(line);
		std::string address, perms, offset, dev, inode;
		std::string name;
		iss >> address >> perms >> offset >> dev >> inode;
		std::getline(iss, name);
		if (!name.empty() && name[0] == ' ')
			name.erase(name.begin());
		if(name.length() == 0)
			continue;
		if (name.find(OBFUSCATE("[anon:scudo:secondary]")) != std::string::npos)
		{
			maps.close();
			scudo_detected = true;
			__android_log_print(ANDROID_LOG_INFO, OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("[anon:scudo:secondary] detected"), 0);
			return scudo_detected;
		}
		if (name.find(OBFUSCATE("[anon:libc_malloc]")) != std::string::npos)
		{
			maps.close();
			__android_log_print(ANDROID_LOG_INFO, OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("[anon:libc_malloc] detected"), 0);
			malloc_detected = true;
			return !malloc_detected;
		}
	}
	maps.close();
	return false;
}


std::string get_section_name(const Section& section)
{
	switch (section) {
		case BOOTLOADER:
			return  {OBFUSCATE("libBootloader.so")};
		case ANON_BSS:
			return {OBFUSCATE("[anon:.bss]")};
		case ANON_SCUDO_SECONDARY:
			return {OBFUSCATE("[anon:scudo:secondary]")};
		case ANON_LIBC_MALLOC:
			return {OBFUSCATE("[anon:libc_malloc]")};
		case ANON_SCUDO_MALLOC:
			if (find_scudo_section())
				return {OBFUSCATE("[anon:scudo:secondary]")};
			else
				return {OBFUSCATE("[anon:libc_malloc]")};
		default:
			return {OBFUSCATE("libBootloader.so")};
	}
}

uintptr_t get_from_memory(const char* pattern, const char* mask, const Section& section, const size_t& offset, uintptr_t start_ptr)
{
	std::string section_name = get_section_name(section);
	static pid_t pid = getpid();
	std::string maps_file = std::string(OBFUSCATE("/proc/")) + std::to_string(pid) + std::string(OBFUSCATE("/maps"));
	std::ifstream maps(maps_file);
	if (!maps)
	{
		LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Failed to get maps"), 0);
		return 0;
	}
	LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("---------------------< Memory Scanning >---------------------"), 0);

	std::string line;
	bool bootloader_found;

	while (std::getline(maps, line))
	{
		std::istringstream iss(line);
		std::string address, perms, a_offset, dev, inode, name;
		iss >> address >> perms >> a_offset >> dev >> inode;
		std::getline(iss, name);

		// remove whitespaces from the section's name
		name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch); }));

		char *endptr;
		unsigned long start = std::strtoul(address.substr(0, address.find('-')).c_str(), &endptr, 16);
		if (*endptr != '\0')
		{
			LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Failed to parse start address: %s"), address.substr(0, address.find('-')).c_str());
			continue;
		}
		unsigned long end = std::strtoul(address.substr(address.find('-') + 1).c_str(), &endptr, 16);
		if (*endptr != '\0') {
			LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Failed to parse end address: %s"), address.substr(address.find('-') + 1).c_str());
			continue;
		}

		size_t size = end - start;
		name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch); }));

		if(name.length() == 0)
			continue;

		// remove the directory from shared libraries
		std::size_t found = name.find_last_of('/');
		if (found != std::string::npos)
			name = name.substr(found + 1);

		// only scan bootloader's bss "if bss was the section required"
		if (section == ANON_BSS && !bootloader_found)
		{
			if (name.find(OBFUSCATE("libBootloader.so")) != std::string::npos)
				bootloader_found = true;
			continue;
		}

		if (name.find(section_name) != std::string::npos)
		{
			LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Scanning: %s | start: %lx | size: %lx"), name.c_str(), start, size);
			uintptr_t result_address = 0;
			try{
				if (start_ptr)
				{
					if (start > start_ptr)
						continue;
					result_address = Cipher::CipherScan(start_ptr, size - (start_ptr - start), pattern, mask);
				}
				else
					result_address = Cipher::CipherScan(start, size, pattern, mask);
			}
			catch (std::out_of_range& error)
			{
				LOGE(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("error: %s"), error.what());
			}

			if (result_address)
			{
				result_address += offset;
				LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Found inside \"%s\" at the address %lx"), name.c_str(), result_address);
				LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("-------------------------------------------------------------"), 0);
				maps.close();
				return result_address;
			}
		}
	}
	maps.close();
	LOGW(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Filed to find %s in %s"), pattern, section_name.c_str());
	LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("-------------------------------------------------------------"), 0);
	return 0;
}


struct{
	std::string name;
	std::string path;
}lib;

int callback(struct dl_phdr_info* info, size_t size, void* data)
{
	if (strstr(info->dlpi_name, lib.name.c_str()))
		lib.path = info->dlpi_name;
	return 0;
}

void init_elf_segments(std::map<std::string, Seg_Info>& container, const char* elf_name)
{
	lib.name = elf_name;
	dl_iterate_phdr(callback, nullptr);
	get_segments(lib.path.c_str(), container);
	lib.name.erase();
	lib.path.erase();
}

void get_segments(const char* lib_path, std::map<std::string, Seg_Info>& container)
{
	int fd = open(lib_path, O_RDONLY);
	if (fd == -1)
	{
		LOGE(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("failed to find the elf: %s\n"), lib_path);
		return;
	}

	struct stat elf_stat{};
	if (fstat(fd, &elf_stat) == -1)
	{
		LOGE(OBFUSCATE(TAG_MEMSCAN), "failed to get the elf stat: %s\n", lib_path);
		return;
	}

	void* elf_address = mmap(nullptr, elf_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (elf_address == MAP_FAILED)
	{
		LOGE(OBFUSCATE(TAG_MEMSCAN), "could not map the elf: %s\n", lib_path);
		return;
	}

	auto* elf_header = (Elf64_Ehdr*)elf_address;
	auto* section_header = (Elf64_Shdr*)((char*)elf_address + elf_header->e_shoff);

	Elf64_Shdr* section_header_string_table = &section_header[elf_header->e_shstrndx];
	const char* section_header_string_table_base = (const char*)((char*)elf_header + section_header_string_table->sh_offset);

	LOGI(OBFUSCATE(TAG_MEMSCAN), "Segments in %s:\n", lib_path);
	for (std::size_t i = 0; i < elf_header->e_shnum; i++)
	{
		const char* sec_name = section_header_string_table_base + section_header[i].sh_name;
		LOGI(OBFUSCATE(TAG_MEMSCAN), "Segment (%s): start=%llx, size=%llx\n", sec_name, section_header[i].sh_addr, section_header[i].sh_size);
		container[sec_name] = Seg_Info(section_header[i].sh_addr, section_header[i].sh_size);
	}

	munmap(elf_address, elf_stat.st_size);
	close(fd);
}

uintptr_t get_from_segment(const char* pattern, const char* mask, const char* segment, std::map<std::string, Seg_Info>& elf_info, const size_t& offset, uintptr_t start_ptr)
{
	uintptr_t result_address = 0;
	if (elf_info.find(segment) == elf_info.end())
	{
		LOGI(OBFUSCATE(TAG_MEMSCAN), "get_from_segment(): failure. no such a segment \"%s\"", segment);
		return 0;
	}
	if (elf_info[segment].start == 0)
	{
		LOGI(OBFUSCATE(TAG_MEMSCAN), "get_from_segment(): starts at 0");
		return 0;
	}
	LOGI(OBFUSCATE(TAG_MEMSCAN), "scanning segment \"%s\"", segment);

	if (start_ptr)
	{
		if (elf_info[segment].start > start_ptr)
			return 0;
		result_address = Cipher::CipherScan(start_ptr, elf_info[segment].size, pattern, mask);
	}
	else
		result_address = Cipher::CipherScan(elf_info[segment].start + Cipher::get_libBase(), elf_info[segment].size, pattern, mask);
	result_address += offset;
	LOGI(OBFUSCATE(TAG_MEMSCAN), "scanning with \"get_from_segment():\" found: %lx", result_address);
	return result_address;
}
