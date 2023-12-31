#pragma once

#include <cstdint>
#include "../memory/memory.h"
#include "../memory/HellAddress.h"
#include "coordinates.h"
#include "../include/imgui/imgui.h"
#include "../include/Vec4.h"
#include "../include/StbImage/create_texture.h"
#include "levels.h"
#include "HellboyIO.h"
#include "SkyIcons.h"


#include <map>
#include <unordered_map>

typedef void (*func)();
extern func (*start_ptr)();


struct vec3 {
	float x, y, z;
	constexpr vec3() : x(0.0f), y(0.0f), z(0.0f) { }
	constexpr vec3(float _x, float _y, float _z)  : x(_x), y(_y), z(_z) { }
};

struct vec4 {
	float x, y, z, w;
	constexpr vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
	constexpr vec4(float _x, float _y, float _z, float _w)  : x(_x), y(_y), z(_z), w(_w) { }
};


typedef void(*Menu)();
struct MenuItem{
private:
	void(*m_menu)();
	const char* m_icon;
	bool m_state;
	bool* m_is_allowed;
	bool m_is_public;

public:
	bool is_resizeable;
	MenuItem() = default;
	MenuItem(void(*menu)(), const char* icon, bool state, bool* is_allowed, bool is_public)
	 : m_menu(menu), m_icon(icon), m_state(state), m_is_allowed(is_allowed), m_is_public(is_public) {}

	void menu() {
		return m_menu();
	}

	const char* icon() {
		return m_icon;
	}

	bool* state() {
		return &m_state;
	}

	bool* is_allowed() {
		return m_is_allowed;
	}

	bool* is_public() {
		return &m_is_public;
	}
};

typedef struct
{
	vec3 color;
	int VOID[0x1C];
	float size;
	float brightness;
}SunSizeIntMoonPhase;

extern HellAddress level_name_ptr;
extern ImGuiStyle HellboyStyle;
extern ImVec4* g_Colors;
extern ProgessBar progress;
extern time_t g_farming_interval;
extern nlohmann::ordered_json* g_farming_coordinates;
extern std::map<std::string, MenuItem>hell_menus;
extern std::map<std::string, Seg_Info>libBootloader_Segments;


extern bool g_hell_menu_collapsed;


class Hellboy{
	public:

	static char level_name[100];
	static std::string user_id;
	static std::string user_session;
	static unsigned long bootloader;
	static time_t candle_run_interval;
	static time_t star_run_interval;


	static size_t StringFind(const char* const str, const char* const what);
	static void GetLevel();
	static uintptr_t get_avatar();

	static void setColors(ImGuiStyle *dst, bool trigger);

	static void SpeedUpAndDelay(time_t time, bool& trigger);

	static bool get_auth;
	static void GetUserAuth();

	static void IterationFarming(nlohmann::ordered_json& coordinates, time_t interval);

	static void OpenCloset(int id);

	static void SetSpell(int32_t id, int socket, bool spark);

	static bool ScreenToWorldView(Vec4<float>& result, Vec4<float> cords);

	static int* GetSpell(int socket);
};

extern Hellboy* hellboy;