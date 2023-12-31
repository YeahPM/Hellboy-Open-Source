#pragma once

#include <fstream>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "Configs.h"
#include "../include/nlohmann/json.hpp"
#include "../include/misc/Logger.h"
#include "../include/misc/obfuscate.h"
#include "../include/imgui/imgui.h"
#include "../hellboy/Hellboy.h"

#define TAG_HBIO "HB-IO"


#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

typedef void (*func)();
//extern func (*start_ptr)();


class HellboyIO
{
public:
	static char mod_path[128];
	static char configs_dir[128];
	static char styles_dir[128];
	void static GetModPath();
	void static SaveConfigs();
	void static LoadConfigs();

	static void reset_configs();

	static void save_style();

	static void load_style();
};
