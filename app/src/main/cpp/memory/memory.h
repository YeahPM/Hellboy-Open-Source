#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <link.h>
#include <string>
#include <map>

enum Section{
	BOOTLOADER = 0,
	ANON_LIBC_MALLOC,
	ANON_SCUDO_SECONDARY,
	ANON_BSS,
	ANON_SCUDO_MALLOC,
};

struct Seg_Info
{
	std::size_t start;
	std::size_t size;
	Seg_Info(std::size_t _start, std::size_t _size) : start(_start), size(_size) {}
	Seg_Info() = default;
};

extern bool scudo_detected;
extern bool malloc_detected;

extern uintptr_t get_from_memory(const char* pattern, const char* mask, const Section& section, const size_t& offset = 0x0, uintptr_t start_ptr = 0x0);
extern uintptr_t get_from_segment(const char* pattern, const char* mask, const char* segment, std::map<std::string, Seg_Info>& elf_info, const size_t& offset = 0x0, uintptr_t start_ptr = 0x0);

extern void init_elf_segments(std::map<std::string, Seg_Info>& container, const char* elf_name);
extern void get_segments(const char* lib_path, std::map<std::string, Seg_Info>& container);
