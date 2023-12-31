#pragma once

#include "memory.h"
#include <cstdint>
#include "../include/misc/Logger.h"
#include "../include/misc/obfuscate.h"
#define TAG_HELLADDRESS "HellAddress"

#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif
#include <chrono>
#include <thread>


class HellAddress {
private:
	uintptr_t m_address;

public:
	explicit HellAddress() = default;
	explicit HellAddress(uintptr_t a_addr);
	explicit HellAddress(const char* a_pattern, const char* a_mask, const Section& a_section, const size_t& a_offset = 0x0, uintptr_t a_start_ptr = 0x0);

	~HellAddress() = default;

	uintptr_t get_address() const;

	uintptr_t* as_ptr(size_t a_offset = 0x0) const;

	float* as_float(size_t a_offset = 0x0) const;

	int* as_int(size_t a_offset = 0x0) const;

	bool* as_bool(size_t a_offset = 0x0) const;

	char* as_string(size_t a_offset = 0x0) const;

	void operator+(long a_offset);
	void operator+(const HellAddress& a_offset);

	HellAddress& operator=(uintptr_t a_address);
	HellAddress& operator=(const HellAddress& a_address);
	operator bool() const;
	operator const char*() const;

	bool wait(time_t time = 0);

	void scan_or_wait(const char* a_pattern, const char* a_mask, const Section& a_section, const size_t& a_offset = 0x0, uintptr_t a_start_ptr = 0x0);

public:
	const char* pattern{};
	const char* mask{};
	Section section;
	size_t offset{};
	uintptr_t start_ptr{};
	bool scan();
	bool scan(const char* a_pattern, const char* a_mask, const Section& a_section, const size_t& a_offset = 0x0, uintptr_t a_start_ptr = 0x0);

	bool is_address() const;

};



