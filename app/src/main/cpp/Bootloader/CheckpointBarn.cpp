#include "CheckpointBarn.h"

#include "../memory/AddressesBase.h"
#include "../memory/hooks.h"

CheckpointBarn* checkpointBarn;

CheckpointBarn::CheckpointBarn() = default;

uintptr_t *CheckpointBarn::m_GetCheckPointBarnPtr()
{
	// from  [Live v0.20.1 (210508)] offset: 0x5CEB18
	return *(uintptr_t**)(*skyRoots->game_ptr.as_ptr() + 0x5D8);
}

long CheckpointBarn::m_ChangeLevel(const char *LevelName)
{
	return ((long(*)(uintptr_t*, uintptr_t*, const char*))(functions->CheckpointBarn_m_ChangeLevel.get_address()))(this->m_GetCheckPointBarnPtr(), skyRoots->game_ptr.as_ptr(), LevelName);
}

void CheckpointBarn::ChangeLevel(const char *LevelName)
{
	m_ChangeLevel(LevelName);
}





