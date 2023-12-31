#include "HellAddress.h"

HellAddress::HellAddress(uintptr_t addr) : m_address(addr) {}

HellAddress::HellAddress(const char* a_pattern, const char* a_mask,
						 const Section& a_section, const size_t& a_offset, uintptr_t a_start_ptr)
{
	m_address = get_from_memory(a_pattern, a_mask, a_section, a_offset, a_start_ptr);
	if (m_address)
	{
		pattern = a_pattern;
		mask = a_mask;
		section = a_section;
		offset = a_offset;
		start_ptr = a_start_ptr;

		LOGI(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("HellAddress: scan success."), 0);
	}
	else
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("HellAddress: scan failure."), 0);
}

uintptr_t HellAddress::get_address() const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("get_address: m_address is 0"), 0);
	return m_address;
}

uintptr_t* HellAddress::as_ptr(size_t a_offset) const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("as_ptr: m_address is 0"), 0);
	return (uintptr_t*)m_address + a_offset;
}

float* HellAddress::as_float(size_t a_offset) const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("as_float: m_address is 0"), 0);
	return (float*)m_address + a_offset;
}

bool* HellAddress::as_bool(size_t a_offset) const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("as_bool: m_address is 0"), 0);
	return (bool*)m_address + a_offset;
}

char*  HellAddress::as_string(size_t a_offset) const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("as_string: m_address is 0"), 0);
	return (char*)m_address + a_offset;
}

int* HellAddress::as_int(size_t a_offset) const
{
	if (!m_address)
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("as_int: m_address is 0"), 0);
	return (int*)m_address + a_offset;
}

void HellAddress::operator+(long m_offset)
{
	m_address += m_offset;
}

void HellAddress::operator+(const HellAddress& m_offset)
{
	m_address += m_offset.m_address;
}

HellAddress& HellAddress::operator=(uintptr_t a_address)
{
	m_address = a_address;
	return *this;
}

HellAddress::operator bool() const
{
	if (!m_address)
		LOGW(TAG_HELLADDRESS, "operator bool(): m_address is 0");
	return this->is_address();
}

HellAddress::operator const char*() const
{
	if (!m_address)
		LOGW(TAG_HELLADDRESS, "operator const char*() : m_address is 0");
	return (const char*)m_address;
}

HellAddress& HellAddress::operator=(const HellAddress& a_address)
{
	m_address = a_address.m_address;
	return *this;
}

bool HellAddress::scan()
{
	m_address = get_from_memory(pattern, mask, section, offset, start_ptr);
	if (m_address)
	{
		LOGI(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("scan success %lx."), m_address);
		return true;
	}
	LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("scan failure."), 0);
	m_address = 0;
	return false;
}

bool HellAddress::scan(const char *a_pattern, const char *a_mask, const Section &a_section, const size_t& a_offset, uintptr_t a_start_ptr)
{
	m_address = get_from_memory(a_pattern, a_mask, a_section, a_offset, a_start_ptr);
	if (m_address)
	{
		LOGI(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("scan: scan success."), 0);
		return true;
	}
	else
		LOGW(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("scan: scan failure."), 0);
	return false;
}

bool HellAddress::wait(time_t time)
{
	static int counter;
	++counter;
	LOGI(OBFUSCATE(TAG_HELLADDRESS), OBFUSCATE("address cooldown: %d"), counter);
	std::chrono::seconds delay(time);
	std::this_thread::sleep_for(delay);
	if (counter >= 5)
		return this->is_address();
}

void HellAddress::scan_or_wait(const char *a_pattern, const char *a_mask, const Section& a_section,const size_t &a_offset, uintptr_t a_start_ptr)
{
	while (!this->scan(a_pattern, a_mask, a_section, a_offset, a_start_ptr))
		if (this->wait(10000))
			break;
}

bool HellAddress::is_address() const
{
	return (m_address > 1000000000);
}






