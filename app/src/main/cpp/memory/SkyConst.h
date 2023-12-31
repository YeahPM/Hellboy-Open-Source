#pragma once

#include <string>
#include <type_traits>
#include "memory.h"
#include "../hellboy/Hellboy.h"

#define TAG_SKYCONSTS "HB-SKYCONSTS"


class SkyConst {
public:
	static HellAddress start;

public:
	std::string name;

private:
	uintptr_t m_address{};

	static std::string process_name(std::string a_name);

	public:
	SkyConst(const std::string &a_name);
	SkyConst();

	void scan(const std::string& a_name);

	template<class T>T* get() const { return (T*)m_address; }

};