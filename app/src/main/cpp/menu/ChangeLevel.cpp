#include "menu.h"


void draw_change_level_window()
{
	bool disabled = trigger.change_level;
	ImGui::BeginDisabled(disabled);

	if (ImGui::BeginTable(OBFUSCATE("###Teleport"), 2))
	{
		ImGui::TableSetupColumn(OBFUSCATE("Gate"), ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableSetupColumn(OBFUSCATE("Realm"), ImGuiTableColumnFlags_WidthStretch);

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);

		if (ImGui::Button(OBFUSCATE("Go Home"), ImVec2(-1.0f, 0.0f)))
		{
			trigger.change_level = true;
			checkpointBarn->ChangeLevel(OBFUSCATE("CandleSpace"));
		}

		if (ImGui::Button(OBFUSCATE("Refresh"), ImVec2(-1.0f, 0.0f)))
		{
			trigger.change_level = true;
			vec3 pos = *avatars[OBFUSCATE("avatar_1")].GetPos();
			checkpointBarn->ChangeLevel(Hellboy::level_name);
			avatars[OBFUSCATE("avatar_1")].Teleport(pos);
		}
		ImGui::Separator();

		static nlohmann::ordered_json* realms = &sky_levels[OBFUSCATE("Isle of Dawn")];
		static float color_index = 0;
		int iteration_index = 0;
		for (auto gate = sky_levels.begin(); gate != sky_levels.end(); ++gate, ++iteration_index)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, iteration_index == (int)color_index ? g_Colors[ImGuiCol_ButtonHovered] : g_Colors[ImGuiCol_Button]);
			if (ImGui::Button(gate.key().c_str(), ImVec2(-1.0f, 0.0f)))
			{
				realms = &gate.value();
				color_index = (float)iteration_index;
			}
			ImGui::PopStyleColor(1);
		}
		ImGui::TableSetColumnIndex(1);
		ImGui::BeginChild(OBFUSCATE("Realms"));
		ImGui::Spacing();
		for (auto& realm : realms->items())
		{
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(color_index / 7.0f, 0.5f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(color_index / 7.0f, 0.7f, 0.5f));
			if (ImGui::Button(realm.key().c_str(), ImVec2(-1.0f, 0.0f)))
			{
				checkpointBarn->ChangeLevel(realm.value().get<std::string>().c_str());
				trigger.change_level = true;
			}
			ImGui::PopStyleColor(2);
		}
		ImGui::EndChild();
		ImGui::EndTable();
	}
	if (disabled)
		ImGui::EndDisabled();
}