#pragma once
#include "../include/imgui/imgui.h"


typedef struct{
	bool change_level;
	bool run_by_teleport;
}Trigger;
extern Trigger trigger;

//
typedef struct{
	float current = 0;
	float end = 0;
	float get_progress() {return current / (end - 1);}
}ProgressCounter;

struct ProgessBar{
	ProgressCounter farming;
};



struct Configs
{
	// UI
	bool ui_AutoResize = true;
	bool ui_ShowHellMenuText = true;

	// window state
	bool ws_avatar = true;
	bool ws_changeLevel = true;
	bool ws_settings = true;
	bool ws_music = true;
	bool ws_style = false;
	bool ws_demo = false;
	bool ws_debug = false;
	bool ws_farming = true;
	bool ws_inventory = true;
	bool ws_command = false;
	bool ws_magic = true;

	// window position
	ImVec2 wp_closet;

	// on load
	bool ol_alwaysMove = false;
	bool ol_show_commands = true;
	bool ol_use_commands = true;
	bool ol_fast_home = true;

	bool dummy_config = false;

	float kFontScale = 24;
};
extern Configs configs;