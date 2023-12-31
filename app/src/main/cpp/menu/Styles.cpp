#include "menu.h"



void draw_styles_window()
{
	if (ImGui::Button("Export"))
	{
		ImGui::LogToClipboard();
		ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;\n");
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const ImVec4& col = HellboyStyle.Colors[i];
			const char* name = ImGui::GetStyleColorName(i);
			ImGui::LogText("colors[ImGuiCol_%s] = ImVec4(%.3ff, %.3ff, %.3ff, %.3ff);\n", name, col.x, col.y, col.z, col.w);
		}
		ImGui::LogFinish();
	}

	ImGui::SetNextItemWidth(120);

	static ImGuiTextFilter filter;
	filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

	static ImGuiColorEditFlags alpha_flags = 0;
	if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None))
		alpha_flags = ImGuiColorEditFlags_None;

	ImGui::SameLine();
	if (ImGui::RadioButton("Alpha", alpha_flags == ImGuiColorEditFlags_AlphaPreview))
		alpha_flags = ImGuiColorEditFlags_AlphaPreview;

	ImGui::SameLine();
	if (ImGui::RadioButton("Both", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf))
		alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf;

	ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	ImGui::PushItemWidth(-160);
	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		const char* name = ImGui::GetStyleColorName(i);
		if (!filter.PassFilter(name))
			continue;
		ImGui::PushID(i);
		ImGui::ColorEdit4("##color", (float*)&HellboyStyle.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
		ImGui::SameLine(0.0f, HellboyStyle.ItemInnerSpacing.x);
		ImGui::TextUnformatted(name);
		ImGui::PopID();
	}
	ImGui::EndChild();
}
