#include "hooks.h"
#include "../include/cipher/Cipher.h"
#include "../Bootloader/Avatar.h"
#include "AddressesBase.h"

// Avatar::Avatar(); to get all avatars from the constructor
HOOK_DEF(void, Avatar_Avatar, long this_ptr)
{
	static int counter = 1;
	char string[25];
	sprintf(string, OBFUSCATE("avatar_%d"), counter);
	avatars.emplace(string, Avatar(this_ptr, counter++ - 1));
	return orig_Avatar_Avatar(this_ptr);
}

// AvatarShout::DoShout(); to control shouts
HOOK_DEF(void, AvatarShout_DoShout, long avatar_shout, int a2, int a3, unsigned int a4, unsigned int a5, unsigned int a6, long double a7, float a8, float a9, float a10, long double a11, float max_size)
{
	for (auto& avatar : avatars)
		if (avatar.second.CustomShoutColor && avatar_shout == *(long*)(avatar.second.GetAvatar() + 0x60))
			return orig_AvatarShout_DoShout(avatar_shout, a2, a3, a4, a5, a6, a7, a8, a9, a10, *(long double*)avatar.second.ShoutColor, max_size);

	return orig_AvatarShout_DoShout(avatar_shout, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, max_size);
}

// pianoButton::OnStart(); auto click the piano button
int g_instrument_type = 0;
bool g_sound_selector;
uintptr_t g_PianoButton;
HOOK_DEF(void, PianoButton_OnStart, uintptr_t PianoButton, uintptr_t *game)
{
	if (!g_PianoButton)
		g_PianoButton = PianoButton;

	if (g_sound_selector)
	{
		*(int*)(PianoButton + 0x210) = instruments[g_instrument_type].type;
		*(int*)(PianoButton + 0x224) = instruments[g_instrument_type].id;
	}
	return orig_PianoButton_OnStart(PianoButton, game);
}

bool g_karaoke_mode;

HOOK_DEF(void, PianoButton_SimulateTap, uintptr_t KaraokeFeedback, int key, char a3)
{
	if (g_karaoke_mode)
	{
		uintptr_t PianoButton = KaraokeFeedback + 0x50 + key * 0x290;
		*(int*)(PianoButton + 0x208) = key;
		*(int*)(PianoButton + 0x210) = instruments[g_instrument_type].type;
		*(int*)(PianoButton + 0x224) = instruments[g_instrument_type].id;
		orig_PianoButton_OnStart(PianoButton, skyRoots->game_ptr.as_ptr());
	}
	return orig_PianoButton_SimulateTap(KaraokeFeedback, key, a3);
}

//\xE0\x03\x08\xAA\xE1\x03\x13\xAA\xE2\x03\x15\xAA\x00\x00\x00\x97\x00\x00\x00\xF9\x00\x00\x00\xB4 xxxxxxxxxxxx???x???x???x
//+170
std::string g_UserMessage;
HOOK_DEF(void, Game_OnKeyboardComplete, long *game, char* message, bool a3, bool a4)
{
#define PREFIX "-kj"
	if (strlen(message) > 0 && configs.ol_use_commands)
		g_UserMessage = message;
	if (!configs.ol_show_commands && g_UserMessage.find(PREFIX) != std::string::npos)
		return;
	return orig_Game_OnKeyboardComplete(game, message, a3, a4);
}

HOOK_DEF(void, AccountSendChatMessageRequest_Queue, long AccountSendChatMessageRequest, char* message, const char* channel)
{
	//note: AccountSendChatMessageRequest = *(long*)(*(long*)(skyRoots->game_ptr.get_address() + 0x1D8) + 0x140);
	if (strstr(message, "-kj msg all"))
		return orig_AccountSendChatMessageRequest_Queue(AccountSendChatMessageRequest, message + 11, "public");
	else
		return orig_AccountSendChatMessageRequest_Queue(AccountSendChatMessageRequest, message, channel);
}

bool g_has_unlock;
HOOK_DEF(bool, AccountBarn_HasUnlock, int64_t a1, uint8_t* a2)
{
	if (g_has_unlock)
		return true;

	return orig_AccountBarn_HasUnlock(a1, a2);
}

void init_hooks()
{
	SETUP_HOOK(Avatar_Avatar_hook, orig_Avatar_Avatar , my_Avatar_Avatar, functions->Avatar_Avatar.get_address())
	SETUP_HOOK(AvatarShout_DoShout_hook, orig_AvatarShout_DoShout, my_AvatarShout_DoShout, functions->AvatarShout_DoShout.get_address())
	SETUP_HOOK(PianoButton_OnStart_hook, orig_PianoButton_OnStart, my_PianoButton_OnStart, functions->PianoButton_OnStart.get_address())
	SETUP_HOOK(PianoButton_SimulateTap_hook, orig_PianoButton_SimulateTap, my_PianoButton_SimulateTap, functions->PianoButton_SimulateTap.get_address())
	SETUP_HOOK(Game_OnKeyboardComplete_hook, orig_Game_OnKeyboardComplete, my_Game_OnKeyboardComplete, functions->Game_OnKeyboardComplete.get_address())
	SETUP_HOOK(AccountSendChatMessageRequest_Queue_hook, orig_AccountSendChatMessageRequest_Queue, my_AccountSendChatMessageRequest_Queue, functions->AccountSendChatMessageRequest_Queue.get_address());
	SETUP_HOOK(AccountBarn_HasUnlock_hook, orig_AccountBarn_HasUnlock, my_AccountBarn_HasUnlock, functions->AccountBarn_HasUnlock.get_address())
}
