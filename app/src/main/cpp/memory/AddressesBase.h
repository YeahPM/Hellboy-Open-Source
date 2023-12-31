#pragma once
#include "../include/misc/obfuscate.h"
#include "HellAddress.h"
#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

#include "../include/cipher/Cipher.h"
#include "../include/cipher/CipherArm64.h"
#include "../hellboy/Hellboy.h"
#include "../include/nlohmann/json.hpp"
#include "HellPatch.h"
#include "SkyConst.h"
#include <unordered_map>



typedef struct{
	SkyConst ForceReactionMenu;
	SkyConst AllNpcsHaveRadar;
	SkyConst AwfulMode;
	SkyConst AwfulMode2;
	SkyConst OrbitMode;
	SkyConst SimulateNoConnection;
	SkyConst UseFakeExternalFriends;
	SkyConst DrawSunLighting;
	SkyConst DisableEnvironment;
	SkyConst AudienceShowFriendNames;
	SkyConst AppleTVMode;
	SkyConst LogCheckpoint;
	SkyConst EnableFluffyClouds;
	SkyConst SuperSlidey;
	SkyConst ForceNativeRes;
	SkyConst SerendipityTagTransDur;
	SkyConst ForceUnclampTime;
	SkyConst MaxBounceOffset;
	SkyConst MinBounceOffset;
	SkyConst ShadowBrightAlpha;
	SkyConst PongFadeOutDur;
	SkyConst PongPauseDur;
	SkyConst PongFadeInDur;
	SkyConst SerendipityTagScale;
	SkyConst WsOffset;
	SkyConst NormPosScalar;
	SkyConst TagIconOffset;
	SkyConst ArrowOffsetScalar;
	SkyConst ArrowScale;
	SkyConst GradientFacebook;
	SkyConst GradientAlpha;
	SkyConst GradientScale;
	SkyConst TguiStateCounter;
	SkyConst LumHighThresh;
	SkyConst RayTop;
	SkyConst RayMid;
	SkyConst GlowMid;
	SkyConst GlowTop;
	SkyConst NumberOffsetX;
	SkyConst NumberOffsetY;
	SkyConst FakeWaxMultiplier;
	SkyConst EnableFakeWaxMultiplier;
	SkyConst KeepCornerButtonsVisible;		// keep UI buttons on the corners visible
	SkyConst ForceMagnify;
	SkyConst HideNumber;					// hide currency numbers
	SkyConst DebugHudOffsetsCandle;
	SkyConst BgSize;
	SkyConst BgOffsetX;
	SkyConst BgOffsetY;
	SkyConst BgAlpha;
	SkyConst BadgeOffsetX;
	SkyConst BadgeOffsetY;
	SkyConst ChevronSize;
	SkyConst ChevronMargin;
	SkyConst CandleScale;
	SkyConst DropShadowA;
	SkyConst EnableVideoRecorderUI;
	SkyConst MaxVideoRecordSeconds;
	SkyConst UseFixedTimestepRecording;
	SkyConst DisplayStarIndex;
	SkyConst FlameToCandleScale;
	SkyConst EnableQuickMenu;
	SkyConst Invincibility;
	SkyConst EnableAllRelationshipAbilities;
	SkyConst BlackWhite;
	SkyConst ShoutAutoRelease;
	SkyConst Disable_Avatar;
	SkyConst ConstellationGateDisable;
	SkyConst AutoSkipAllTimelines;
	SkyConst FlameInHand;
	SkyConst AvatarCharcoaling;
	SkyConst DisableGiftRelationshipTimeCheck;
	SkyConst DisableWind;
	SkyConst ApplyForcesInFlightComputer;
	SkyConst EnableMultiplayer;
	SkyConst FishSchoolDebug;
	SkyConst Disable_Hud;
	SkyConst Disable_Ocean;
	SkyConst AllowOverride;
	SkyConst CheapFogEnabled;
	SkyConst FakeCapeLevelEnable;
	SkyConst RunSpeed;
	SkyConst FakeCapeLevel;
	SkyConst LiftUpForceMultiplier;
	SkyConst CheapFogHeight;
	SkyConst CheapFogHeightDensity;
}K;

typedef struct{
	HellAddress Avatar_Teleport;
	HellAddress Avatar_Avatar;
	HellAddress AvatarShout_DoShout;
	HellAddress PianoButton_SimulateTap;
	HellAddress PianoButton_OnStart;
	HellAddress CheckpointBarn_m_ChangeLevel;
	HellAddress Game_OnKeyboardComplete;
	HellAddress AccountSendChatMessageRequest_Queue;
	HellAddress AccountBarn_HasUnlock;
}Functions;

typedef struct{
	HellAddress avatar_ptr;
	HellAddress game_ptr;
	HellAddress avatar_xpos;
}SkyRoots;

extern Functions* functions;
extern SkyRoots* skyRoots;

typedef struct{
	HellAddress game_speed;
	HellAddress screenshot_resolution;
	HellAddress nentity;
	HellAddress user_auth_ptr{0};
	HellAddress cape_opacity;
}Allocations;

extern K* k;
extern Allocations* allocations;

extern std::unordered_map<std::string, HellPatch>patch;

extern bool get_pointers();
extern void* get_functions(void*);
extern void* get_patches(void*);
extern void* get_bool_constants(void*);
extern bool get_allocations_from_memory();