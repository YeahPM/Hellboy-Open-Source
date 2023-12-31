#pragma once

#include <ctime>
#include "../include/nlohmann/json.hpp"
#include "../include/misc/fileselector.h"
#include "../include/misc/Logger.h"
#include <pthread.h>
#include <vector>

#define TAG_MUSIC "HB-MUSIC"

// microseconds per beat
#define MPB 60000000


enum State{
	Stop = 0,
	Play,
	Pause,
	Error,
	Skip,
};

class SkySong {
private:
	static std::time_t BPM;
	static void m_PlayNote(nlohmann::ordered_json& notes);

private:
	static void readFile(int fd);

public:
	static std::vector<nlohmann::ordered_json> SheetList;
	static unsigned int selected_sheet;
	static bool ImportSheet();

public:
	static void Start();
	static void Play() { SkySong::state = State::Play; }
	static void Stop() { SkySong::state = State::Stop; }
	static void Pause() { SkySong::state = State::Pause; }
	static void Init();


	[[noreturn]] static  void* Update(void* argv);
	static State state;
};