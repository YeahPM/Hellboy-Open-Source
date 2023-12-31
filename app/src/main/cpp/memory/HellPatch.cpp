#include "HellPatch.h"


void HellPatch::init(uintptr_t address, uint32_t patch_value)
{
	m_PatchValue = ((patch_value << 24) | (((patch_value >> 16) << 24) >> 16) | (((patch_value << 16) >> 24) << 16) | (patch_value >> 24));
	m_Address = address;
	KittyMemory::memRead(&m_OriginalValue, (void*)address, sizeof(uint32_t));
}

void HellPatch::init(const char *pattern, const char *mask, uint32_t patch_value, const size_t &offset)
{
	m_Address = get_from_memory(pattern, mask, BOOTLOADER, offset);
	m_PatchValue = ((patch_value << 24) | (((patch_value >> 16) << 24) >> 16) | (((patch_value << 16) >> 24) << 16) | (patch_value >> 24));
	KittyMemory::memRead(&m_OriginalValue, (void*)m_Address, sizeof(uint32_t));
}

void HellPatch::switchPatch()
{
	if (m_GetValue() ==  m_OriginalValue)
		KittyMemory::memWrite((void*)m_Address, &m_PatchValue, sizeof(uint32_t));
	else
		KittyMemory::memWrite((void*)m_Address, &m_OriginalValue, sizeof(uint32_t));
}

void HellPatch::switchPatch(bool& v)
{
	if (v)
		KittyMemory::memWrite((void*)m_Address, &m_PatchValue, sizeof(uint32_t));
	else
		KittyMemory::memWrite((void*)m_Address, &m_OriginalValue, sizeof(uint32_t));
}

void HellPatch::update()
{
	this->state = m_GetValue() != m_OriginalValue;
}


void HellPatch::update(bool &state) const
{
	state = m_GetValue() != m_OriginalValue;
}

uint32_t HellPatch::m_GetValue() const
{
	uint32_t buff;
	KittyMemory::memRead(&buff ,(void*)m_Address, sizeof(uint32_t));
	return buff;
}

