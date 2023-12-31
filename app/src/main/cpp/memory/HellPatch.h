#pragma once
#include "../include/KittyMemory/KittyMemory.h"
#include "../memory.h"
#include "../hellboy/Hellboy.h"

class HellPatch {
private:
	uintptr_t m_Address{};
	uint32_t m_PatchValue{};
	uint32_t m_OriginalValue{};

public:
	HellPatch() : m_Address(0), m_OriginalValue(0), m_PatchValue(0) {}

	void init(uintptr_t address, uint32_t patch_value);
	void init(const char* pattern, const char* mask, uint32_t patch_value, const size_t& offset = 0x0);

	bool state;
	void update();
	void update(bool& state) const;
	void switchPatch();
	void switchPatch(bool& v);

private:
	uint32_t m_GetValue() const;


};

