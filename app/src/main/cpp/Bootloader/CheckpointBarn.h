#pragma once


#include <cstdint>

class CheckpointBarn {
private:
	static uintptr_t* m_GetCheckPointBarnPtr();
	long m_ChangeLevel(const char* LevelName);

public:
	CheckpointBarn();
	void ChangeLevel(const char* LevelName);

};

extern CheckpointBarn* checkpointBarn;
