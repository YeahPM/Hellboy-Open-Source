#include "AddressesBase.h"
#include "../Bootloader/Avatar.h"
#include "hooks.h"
#include <chrono>
#include <thread>



uintptr_t *get_adr_val(uintptr_t address, uint32_t relOffset = 4)
{
	uintptr_t buf = 0;
	memcpy(&buf, reinterpret_cast<void*>(address), 4);
	long addr{0};
	CipherArm64::decode_adr_imm(buf, &addr);
	memcpy(&buf, reinterpret_cast<void*>(address + relOffset), 4);
	int32_t rel = 0;
	CipherArm64::decode_ldrstr_uimm(buf, &rel);
	return reinterpret_cast<uintptr_t*>(((address >> 12) << 12) + addr + rel);
}

uintptr_t *get_adr_val(const char *pattern, const char *mask, uintptr_t *address, uint32_t relOffset = 4, uint32_t patternOffset = 0)
{
	uintptr_t scan_address = Cipher::CipherScan(pattern, mask);
	if(address != nullptr) *address = scan_address;
	uintptr_t buf = 0;
	memcpy(&buf, (void *)scan_address, 4);
	long addr{0};
	CipherArm64::decode_adr_imm(buf, &addr);
	memcpy(&buf, (void *)(scan_address + relOffset), 4);
	int32_t rel = 0;
	CipherArm64::decode_ldrstr_uimm(buf, &rel);
	return (uintptr_t *)(((scan_address >> 12) << 12) + addr + rel);
}

Functions* functions = nullptr;
Allocations* allocations = nullptr;
K* k;
SkyRoots *skyRoots = nullptr;
std::unordered_map<std::string, HellPatch>patch;

void wait(time_t time = 0)
{
	std::chrono::seconds delay(time);
	std::this_thread::sleep_for(delay);
}



bool get_pointers()
{


	skyRoots->game_ptr.scan("\xA8\x83\x00\xD0\x00\x10\x80\x52\x13\x39\x06\xF9\xA1\xD4\xEC\x97\x00\xE4\x00\x6F", OBFUSCATE("??x?xxxxx??x???xxxxx"), BOOTLOADER);
	skyRoots->game_ptr = *get_adr_val(skyRoots->game_ptr.get_address(), 8);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("game_ptr: %lx"), skyRoots->game_ptr.get_address());



	return false;
}

void* get_functions(void*)
{
	functions = new Functions;
	functions->Avatar_Teleport.scan("\x16\x1C\x40\xF9\xF4\x03\x00\xAA\xE8\xC3\x00\x91", OBFUSCATE("xxxxxxxxxxx"), BOOTLOADER, -0x18);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("Avatar::Teleport(): %lx"), functions->Avatar_Teleport.get_address() - hellboy->bootloader);

	functions->Avatar_Avatar.scan("\x68\x0A\x00\xB9\x64\xCC\x1B\x94\x28\x82\x00\xF0\x08\x21\x43\xF9\x69\x74\x00", OBFUSCATE("xxxx??????x?x??x??x"), BOOTLOADER, -0x2C);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("Avatar::Avatar(): %lx"), functions->Avatar_Avatar.get_address() - hellboy->bootloader);

	functions->AvatarShout_DoShout.scan("\x08\xB0\x40\x39\x68\x28\x00\x35\x48\x77\x00\x90\x08\x61\x78\x39\xF8\x03\x05\x2A", OBFUSCATE("xxxx??xx?????????x?x"), BOOTLOADER, -0x30);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("AvatarShout::DoShout(): %lx"), functions  ->AvatarShout_DoShout.get_address() - hellboy->bootloader);

	functions->PianoButton_OnStart.scan("\x00\x00\x00\xB9\x00\x00\x00\xB9\x00\x00\x00\x52\x00\x00\x00\x52\x00\x00\x00\x52\x9F\x03\x1B\x6B", OBFUSCATE("???x???x???x???x???xxxxx"), BOOTLOADER, -0x24);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("PianoButton::OnStart(): %lx"), functions->PianoButton_OnStart.get_address() - hellboy->bootloader);

	functions->PianoButton_SimulateTap.scan("\x28\x00\x28\x9B\x00\x00\x00\x39\x00\x00\x00\x52", "xxxx???x???x", BOOTLOADER, -0x4);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("PianoButton::SimulateTap(): %lx"), functions->PianoButton_SimulateTap.get_address() - hellboy->bootloader);

	functions->CheckpointBarn_m_ChangeLevel.scan("\x33\xF4\x42\xF9\xF4\x03\x02\xAA\x7C\xC2\xFF\x97\xE1\x03\x00\xAA\xE0\x03\x13\xAA", OBFUSCATE("x?xxxxxx???xxxxxxxxx"), BOOTLOADER, -0x14);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("CheckpointBarn::m_ChangeLevel(): %lx"), functions->CheckpointBarn_m_ChangeLevel.get_address() - hellboy->bootloader);

	functions->Game_OnKeyboardComplete.scan("\xF3\x03\x00\xAA\x00\x00\x00\xF9\xF6\x03\x03\x2A", "xxxx???xxxxx", BOOTLOADER, -0x1C);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("Game::OnKeyboardComplete(): %lx"), functions->Game_OnKeyboardComplete.get_address() - hellboy->bootloader);

	functions->AccountSendChatMessageRequest_Queue.scan("\xF3\x03\x00\xAA\xE0\x03\x01\xAA\xF4\x03\x02\xAA\xF6\x03\x01\xAA\x00\x00\x00\x97", OBFUSCATE("xxxxxxxxxxxxxxxx???x"), BOOTLOADER, -0x14);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("AccountSendChatMessageRequest::Queue(): %lx"), functions->AccountSendChatMessageRequest_Queue.get_address() - hellboy->bootloader);

	functions->AccountBarn_HasUnlock.scan("\x00\x00\x00\x94\x00\x00\x00\xB4\x00\x00\x00\x52\x00\x00\x00\xA9\x00\x00\x00\xA8", OBFUSCATE("???x???x???x???x???x"), BOOTLOADER, -0x18);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("AccountBarn::HasUnlock(): %lx"), functions->AccountBarn_HasUnlock.get_address() - hellboy->bootloader);

	init_hooks();

	return nullptr;
}

void* get_patches(void*)
{
	patch[OBFUSCATE("lock_coordinates")].init("\x00\x00\x00\x3D\x00\x00\x00\x54\x00\x00\x00\x00\x00\x00\x00\x72\x00\x01\x27\x1E", OBFUSCATE("???x???x???????xxxxx"), 0xE003002A);
	patch[OBFUSCATE("allow_upgrade_emote")].init("\xFA\x03\x00\x2A\x00\x00\x00\x37\x00\x00\x00\x36\x00\x00\x00\x91", OBFUSCATE("xxxx???x???x???x"), 0x3A008052);
	patch[OBFUSCATE("upgrade_emote")].init("\x00\x00\x00\xB9\x00\x00\x00\x35\x00\x00\x00\x14\x00\x00\x00\x91\x00\x00\x00\xD1", OBFUSCATE("???x???x???x???x???x"), 0x28278052);
	patch[OBFUSCATE("iphone_headphones")].init("\xE0\x03\x27\x1E\x00\x00\x00\xB9\x00\x20\x2A\x1E", OBFUSCATE("xxxx???xxxxx"), 0x0090241E);
	patch[OBFUSCATE("simulate_scooter")].init("\x00\xDC\x20\x6E\x01\xD8\x30\x7E\x00\x04\x14\x5E\x00\x28\x21\x1E\x00\x00\x00\x91", OBFUSCATE("xxxxxxxxxxxxxxxx???x"), 0x0090361E);
	patch[OBFUSCATE("krill_paralyse")].init("\x20\x09\x2A\x1E\x00\x00\x00\x72\x00\x00\x00\xB9", OBFUSCATE("xxxx???x???x"), 0x0090361E);
	patch[OBFUSCATE("outfits_reveal")].init("\x00\x00\x00\x1E\x01\x04\x03\x1F\x03\x08\x20\x1E\x03\x08\x23\x1E\x00\x08\x01\x1F\x60\x08\x20\x1E\x00\x00\x00\xBD", OBFUSCATE("???xxxxxxxxxxxxxxxxxxxxx???x"), 0xE003271E);
	patch[OBFUSCATE("fast_home")].init("\x00\x00\x00\x54\x00\x00\x00\x6F\x00\x00\x00\xAD\x00\x00\x00\xF9\x00\x00\x00\xD1\xE1\x03\x15\xAA", OBFUSCATE("???x???x???x???x???xxxxx"), 0x1F2003D5);
	patch[OBFUSCATE("unlock_zoom")].init("\x00\x00\x00\xBD\x20\x38\x29\x1E\x00\x00\x00\x1E", OBFUSCATE("???xxxxx???x"), 0xE003271E);
	patch[OBFUSCATE("sun_and_moon")].init("\x00\x00\x00\xBC\xC0\x03\x5F\xD6\x00\x00\x00\xFD", OBFUSCATE("???xxxxx???x"), 0xE003002A);
	patch[OBFUSCATE("remove_winds")].init("\x41\xDC\x22\x6E\x24\xD8\x30\x7E\x21\x04\x14\x5E\x21\x28\x24\x1E\x21\xC0\x21\x1E", OBFUSCATE("xxxxxxxxxxxxxxxxxxxx"), 0xE003271E);
	patch[OBFUSCATE("absorb_wax")].init("\x21\xDC\x21\x6E\x23\xD8\x30\x7E\x21\x04\x14\x5E\x21\x28\x23", OBFUSCATE("xxxxxxxxxxxxxxx"), 0xD503201F);
	return nullptr;
}

void* get_bool_constants(void*)
{
	k = new K;
	SkyConst::start = get_from_memory(OBFUSCATE("threaded_app"), OBFUSCATE("xxxxxxxxxxx"), BOOTLOADER);
	k->ForceReactionMenu.scan(OBFUSCATE("kForceReactionMenu"));
        // find the names yourself or roman will get crazy

	return nullptr;
}

bool get_allocations_from_memory()
{
	wait();
	allocations = new Allocations;
	allocations->game_speed.scan_or_wait(OBFUSCATE("\x89\x88\x08\x3D"), OBFUSCATE("xxxx"), ANON_SCUDO_MALLOC, 0x14);
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("allocations->game_speed: %lx"), allocations->game_speed.get_address());

	{
		int group[7] = {67, 0, 1175, 3, 1, 0};
		allocations->screenshot_resolution.scan((char*)group, OBFUSCATE("xxxxxxxx????xxxxxxxxxxxx"), ANON_SCUDO_MALLOC, 0x15C);
		LOGI(OBFUSCATE(TAG_HELLBOY), "allocations->screenshot_resolution: %lx", allocations->screenshot_resolution.get_address());
	}


	allocations->cape_opacity.scan("\xFA\x7E\xAA\xBE", OBFUSCATE("xxxx"), ANON_SCUDO_MALLOC, -0xC);
	LOGI(OBFUSCATE(TAG_HELLBOY), "allocations->cape_opacity: %lx", allocations->cape_opacity.get_address());


	return false;
}

void ignored_consts()
{

}
