#include "HellWidget.h"
#include "Hellboy.h"

bool HellWidget::ClickablePiece(const char* label, const char* icon, bool is_active, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, nullptr, true);

	ImVec2 pos = window->DC.CursorPos;
	// Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

	// Render
	const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	ImGui::RenderNavHighlight(bb, id);
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

	if (g.LogEnabled)
		ImGui::LogSetNextTextDecoration("[", "]");

	ImRect TextPos({ bb.Min.x + style.FramePadding.x, bb.Min.y }, bb.Max - style.FramePadding);
	ImGui::RenderTextClipped(TextPos.Min, TextPos.Max, label, nullptr, &label_size, ImVec2(0, 0.5f), &bb);


	ImTextureID textureId = IconLoader::getImage(icon).textureId;
	char buff[100] = "";
	sprintf(buff, "%s%s", label, icon);
	ImGui::PushID(buff);
	window->DrawList->AddImage(textureId, {bb.Max.x - 50, bb.Max.y - 50}, {bb.Max.x, bb.Max.y});
	ImGui::PopID();

	float thickness = 5.0f;
	ImVec2 p1 = { bb.Min.x, bb.Max.y - thickness * 0.5f };
	ImVec2 p2 = { bb.Max.x, bb.Max.y - thickness * 0.5f };
	ImU32 color = ImGui::GetColorU32(is_active ? ImVec4(0.000f, 0.840f, 0.102f, 1.000f) : style.Colors[ImGuiCol_MenuBarBg]);
	float rounding = style.FrameRounding * 2.0f;
	//window->DrawList->Flags |= ImDrawFlags_RoundCornersBottom;
	window->DrawList->AddRectFilled(p1, p2, color, rounding, ImDrawFlags_RoundCornersBottom);


	// Automatically close popups
	//if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
	//    CloseCurrentPopup();

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
	return pressed;
}

ImVec2 HellWidget::DockWindowToScreen()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImVec2& pos = window->Pos;
	ImVec2& size = window->Size;
	ImVec2& displaySize = ImGui::GetIO().DisplaySize;
	const ImVec2 dockSpace = { 150 * displaySize.x / 1920, 150 * displaySize.y / 1080 };
	if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		if (pos.y < dockSpace.y)
			window->Pos = ImVec2(pos.x, 0);
		else if (pos.y + size.y > displaySize.y - dockSpace.y)
			window->Pos = ImVec2(pos.x, displaySize.y - size.y);
		else if (pos.x < dockSpace.x)
			window->Pos = ImVec2(0, pos.y);
		else if (pos.x + size.x > displaySize.x - dockSpace.x)
			window->Pos = ImVec2(displaySize.x - size.x, pos.y);
	}
	return pos;
}

bool HellWidget::SwitchingIcon(const char* name, const char* icon, bool* state, float size, bool no_text)
{
	char buff[100];
	bool is_clicked;
	sprintf(buff, "%s%p%s", icon, &state, name);
	ImGui::PushID(buff);

	ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0, 0, 0, 0});

	is_clicked = IconLoader::iconButton(icon, size, *state ? ImVec4(0.000f, 0.840f, 0.102f, 1.000f) : g_Colors[ImGuiCol_ButtonHovered]);

	if (is_clicked)
		*state = !*state;

	if (!no_text)
	{
		ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20 * ImGui::GetIO().DisplaySize.y / 1080);
		ImGui::Text("%s", name);
	}

	ImGui::PopStyleColor(3);
	ImGui::PopID();
	return is_clicked;
}

ImVec4 HellWidget::IsButtonOn(bool is_on)
{
	static ImVec4* color = ImGui::GetStyle().Colors;
	return is_on ? color[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
}