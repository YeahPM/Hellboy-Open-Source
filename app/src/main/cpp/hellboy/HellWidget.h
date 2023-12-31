#pragma once
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui_internal.h"
#include "../include/iconloader/IconLoader.h"

class HellWidget {
public:
	static bool ClickablePiece(const char *label, const char* icon, bool is_active, const ImVec2 &size_arg, ImGuiButtonFlags flags);

	static ImVec2 DockWindowToScreen();

	static bool SwitchingIcon(const char *name, const char *icon, bool *state, float size, bool no_text = false);

	static ImVec4 IsButtonOn(bool is_on);
};


