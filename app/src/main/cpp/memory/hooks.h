#pragma once

#include "../hellboy/Hellboy.h"
#include "../include/cipher/Cipher.h"


// Avatar::Avatar();
extern CipherBase *Avatar_Avatar_hook;
extern void (*orig_Avatar_Avatar)(long this_ptr);
extern void my_Avatar_Avatar(long this_ptr);

// AvatarShout::DoShout();
extern CipherBase *AvatarShout_DoShout_hook;
extern void (*orig_AvatarShout_DoShout)(long avatar_shout, int a2, int a3, unsigned int a4, unsigned int a5, unsigned int a6, long double a7, float a8, float a9, float a10, long double a11, float a12);
extern void my_AvatarShout_DoShout(long avatar_shout, int a2, int a3, unsigned int a4, unsigned int a5, unsigned int a6, long double a7, float a8,float a9, float a10, long double a11, float a12);

// MusicMenu
struct Instrument{
	const char* name;
	const char* icon;
	int type;
	int id;
};

static Instrument instruments[] = {
	{
		"Harp", 
		"UiOutfitPropHarp",
		0,
		0
	},
	{
		"Piano", 
		"UiOutfitPropPiano",
		0, 
		1
	},
	{
		"White Piano",
		"UiOutfitPropAP05Piano",
		0, 
		2
	},
	{
		"Guitar",
		"UiOutfitPropAP04Guitar",
		0, 
		3
	},
	{
		"Ukulele", 
		"UiOutfitPropAP04Ukulele",
		0, 
		4
	},
	{
		"Xylophone",
		"UiOutfitPropAP05Xylophone",
		0, 
		5

	},
	{
		"Reskin Electric Guitar",
		"UiOutfitPropReskinAP14Guitar",
		0, 
		6
	},
	{
		"Lute",
		"UiOutfitPropAP09Lute",
		0, 
		7
	},
	{
		"Kalimba",
		"UiOutfitPropAP12Kalimba",
		0, 
		8
	},
	{
		"Aurora Microphone", 
		"UiOutfitPropAP16Microphone",
		0, 
		9
	},
	{
		"ArpeggiatorBell",
		"UiPlaceholder",
		0, 
		10
	},
	{
		"Bass",
		"UiOutfitPropBass",
		1, 
		0
	},
	{
		"Drum",
		"UiOutfitPropDrum",
		2, 
		0
	},
	{
		"Bell A",
		"UiOutfitPropAP02BellA",
		2, 
		1
	},
	{
		"Bell B",
		"UiOutfitPropAP02BellB",
		2, 
		2
	},
	{
		"HandPan",
		"UiOutfitPropAP07HandPan",
		2, 
		3
	},
	{
		"Dundun",
		"UiOutfitPropAP08Dundun",
		2, 
		4
	},
	{
		"Reskin HandPan",
		"UiOutfitPropReskinHandPan",
		2, 
		5
	},
	{
		"Reskin Dundun",
		"UiOutfitPropReskinDundun",
		2, 
		6
	},
	{
		"Horn",
		"UiOutfitPropHorn",
		3, 
		0
	},
	{
		"Flute",
		"UiOutfitPropAP03LongFlute",
		3, 
		1
	},
	{
		"PanFlute",
		"UiOutfitPropAP03PanFlute",
		3, 
		2
	},
	{
		"Bugle",
		"UiOutfitPropAP10Bugle",
		3, 
		3
	},
	{
		"Ocarina",
		"UiOutfitPropOcarina",
		3, 
		4
	},
	{
		"Reskin Bugle",
		"UiOutfitPropReskinBugle",
		3, 
		5
	},
};

// pianoButton::OnStart();
extern int g_instrument_type;
extern bool g_sound_selector;
extern uintptr_t g_PianoButton;
extern CipherBase *PianoButton_OnStart_hook;
extern void (*orig_PianoButton_OnStart)(uintptr_t PianoButton, uintptr_t *game);
extern void my_PianoButton_OnStart(uintptr_t PianoButton, uintptr_t *game);

// pianoButton::SimulateTap();
extern bool g_karaoke_mode;
extern CipherBase *PianoButton_SimulateTap_hook;
extern void (*orig_PianoButton_SimulateTap)(uintptr_t instrumentMenu, int key, char a3);
extern void my_PianoButton_SimulateTap(uintptr_t instrumentMenu, int key, char a3);

// Game::onKeyboardComplete();
extern std::string g_UserMessage;
extern CipherBase *Game_OnKeyboardComplete_hook;
extern void (*orig_Game_OnKeyboardComplete)(long *game, char *message, bool a3, bool a4);
extern void my_Game_OnKeyboardComplete(long *game, char *message, bool a3, bool a4);

// AccountSendChatMessageRequest::Queue();
extern CipherBase *AccountSendChatMessageRequest_Queue_hook;
extern void (*orig_AccountSendChatMessageRequest_Queue)(long AccountSendChatMessageRequest, char *message, const char *channel);
extern void my_AccountSendChatMessageRequest_Queue(long AccountSendChatMessageRequest, char *message, const char *channel);

// AccountBarn::HasUnlock();
extern bool g_has_unlock;
extern CipherBase *AccountBarn_HasUnlock_hook;
extern bool (*orig_AccountBarn_HasUnlock)(int64_t a1, uint8_t* a2);
extern bool my_AccountBarn_HasUnlock(int64_t a1, uint8_t* a2);


extern void init_hooks();