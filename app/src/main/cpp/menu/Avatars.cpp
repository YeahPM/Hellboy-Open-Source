#include "menu.h" 


void avatar_pos_grib(Avatar* avatar)
{
	static const char* xyz[3] = { " :x", " :z", " :y"};
	for (int i = 0; i < 3; ++i)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i + 2 / 7.0f, 0.5f, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i + 2 / 7.0f, 0.6f, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i + 2 / 7.0f, 0.7f, 0.5f));
		ImGui::SetNextItemWidth(ImGui::GetFontSize() * 4);
		ImGui::DragFloat(xyz[i], (float*)avatar->GetPos() + i, 0.5f, 0.0f, 0.0f, "%.3f");
		ImGui::PopStyleColor(3);
		if (i < 2)
			ImGui::SameLine();
	}
}

void draw_avatar_window()
{
	if (avatars.empty())
		return;

	static const char* avatar_1 = OBFUSCATE("avatar_1");
	static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
	if (ImGui::CollapsingHeader(OBFUSCATE("Me")))
	{
		HellWidget::SwitchingIcon(OBFUSCATE("Use Custom Shout Color"), icons.UiMenuReactionShock, &avatars[avatar_1].CustomShoutColor, size);
		ImGui::SameLine();
		if (IconLoader::iconButton(icons.UiEmoteCallDefault, size, *(ImVec4*)avatars[avatar_1].ShoutColor))
			avatars[avatar_1].DoShout();
		ImGui::ColorEdit3("Shout Color", avatars[avatar_1].ShoutColor);
		avatar_pos_grib(&avatars[avatar_1]);
	}

	if (ImGui::CollapsingHeader(OBFUSCATE("Others")))
	{
		static bool show_players = true;
		static Avatar* avatar = nullptr;
		if (ImGui::RadioButton(OBFUSCATE("Players"), show_players))
		{
			show_players = true;
			avatar = nullptr;
		}

		ImGui::SameLine();
		if (ImGui::RadioButton(OBFUSCATE("Spirits"), !show_players))
		{
			show_players = false;
			avatar = nullptr;
		}

		if (ImGui::BeginTable(OBFUSCATE("###Avatars"), 2))
		{
			float column_width = size + (ImGui::GetStyle().FramePadding.x * 2);
			ImGui::TableSetupColumn(OBFUSCATE("avatars"), ImGuiTableColumnFlags_WidthFixed, column_width);
			ImGui::TableSetupColumn(OBFUSCATE("options"), ImGuiTableColumnFlags_WidthStretch, 350);

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::BeginChild(OBFUSCATE("Avatar Child 1 "));

			int avatars_idx = 0;
			for (auto& it : avatars)
			{
				if (it.first == avatar_1 || it.second.GetPos()->y == 0.0)
					continue;

				if (it.second.IsBot() && show_players)
					continue;
				if (!it.second.IsBot() && !show_players)
					continue;

				/*Vec4<float> res;
				vec3* pos = avatar->GetPos();
				Hellboy::ScreenToWorldView(res, {pos->x, pos->y, pos->z, 0});
				ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
				ImVec2 text_size = ImGui::CalcTextSize(avatar->IsBot() ? "Spirit" : "Player");
				draw_list->AddRectFilled({res.x, res.y}, ImVec2(res.x + text_size.x, res.y + text_size.y), IM_COL32(0, 0, 0, 100));
				draw_list->AddText({res.x, res.y}, 0xFFFFFFFF, avatar->IsBot() ? "Spirit" : "Player");
				 */

				char index[25];
				sprintf(index, OBFUSCATE("%s : %d##"), it.second.IsBot() ? OBFUSCATE("Spirit") : OBFUSCATE("Player"), avatars_idx++);

				ImGui::PushID(index);
				static const char* UiMenuCollectMask = OBFUSCATE("UiMenuCollectMask");
				static const char* UiEmoteStanceDefault = OBFUSCATE("UiEmoteStanceDefault");

				ImGui::PushStyleColor(ImGuiCol_Button, avatar == &it.second ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
				if (IconLoader::iconButton(it.second.IsBot() ? UiMenuCollectMask : UiEmoteStanceDefault, size))
					avatar = &it.second;
				ImGui::PopStyleColor();
				ImGui::PopID();

			}
			ImGui::EndChild();

			ImGui::TableSetColumnIndex(1);
			ImGui::BeginChild(OBFUSCATE("Avatar Child 2"));
			if (avatar)
			{
				char info[225] = "";
				sprintf(info, OBFUSCATE("Coordinates:\n| x: %.6f | y: %.6f | z: %.6f"),
						avatar->GetPos()->x, avatar->GetPos()->y, avatar->GetPos()->z);
				ImGui::Text("%s", info);

				HellWidget::SwitchingIcon(OBFUSCATE("Use Custom Shout Color"), icons.UiMenuReactionShock, &avatars[avatar_1].CustomShoutColor, size);
				if (IconLoader::iconButton(icons.UiEmoteCome, size))
					avatar->Teleport(*avatars[avatar_1].GetPos(), true);
				ImGui::SameLine();
				if (IconLoader::iconButton(icons.UiEmoteRise, size))
					avatars[avatar_1].Teleport(*avatar->GetPos(), true);
				ImGui::SameLine();
				if (IconLoader::iconButton(icons.UiEmoteCallDefault, size, *(ImVec4*)avatar->ShoutColor))
					avatar->DoShout();

				ImGui::ColorEdit3(OBFUSCATE("Shout Color"), avatar->ShoutColor);
				avatar_pos_grib(avatar);
			}

			ImGui::EndChild();
			ImGui::EndTable();
		}
	}
}