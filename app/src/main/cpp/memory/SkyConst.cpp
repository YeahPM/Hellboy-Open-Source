#include "SkyConst.h"

HellAddress SkyConst::start;

SkyConst::SkyConst(const std::string &a_name) : name(process_name(a_name)) {}

SkyConst::SkyConst() = default;

std::string SkyConst::process_name(std::string a_name)
{
	if (a_name.empty())
		return "";
	if (a_name[0] == 'k')
		a_name.erase(a_name.begin());

	for (int i = 1; i < a_name.size(); i++)
		if (std::isupper(a_name[i]) && std::islower(a_name[i - 1]))
			a_name.insert(i, " ");

	return a_name;
}

void SkyConst::scan(const std::string &a_name)
{
	name = process_name(a_name);
	std::string mask;

	for (int i = 0; i < a_name.length(); ++i)
		mask += 'x';

	uintptr_t address = 0;
	address = get_from_memory(a_name.c_str(), mask.c_str(), BOOTLOADER, 0x0, SkyConst::start.get_address());
	if (address)
	{
		uintptr_t group[2] = {address};
		address = get_from_memory((char*)group, OBFUSCATE("xxxxxxxx"), ANON_BSS);
		if (address)
		{
			m_address = *(uintptr_t*)(address + 0x28);
			LOGI(OBFUSCATE(TAG_SKYCONSTS), OBFUSCATE("%s pointer obtained. offset: %lx"), a_name.c_str(), this->m_address - hellboy->bootloader);
		}
		else
			LOGI(OBFUSCATE(TAG_SKYCONSTS), OBFUSCATE("%s failed"), a_name.c_str());


	}
}

