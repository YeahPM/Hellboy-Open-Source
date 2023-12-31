#include "menu.h" 

void draw_teleport_list(nlohmann::ordered_json& list)
{
	float window_width = ImGui::GetContentRegionAvail().x;
	float half_window_width = window_width / 2 - HellboyStyle.FramePadding.x;
	for (auto& key : list.items())
	{
		if (key.value()[OBFUSCATE("level_name")].get<std::string>() == Hellboy::level_name)
		{
			if (key.value()[OBFUSCATE("content")].empty())
				continue;

			vec3 position;
			unsigned int counter = 0;
			float button_length;
			unsigned int content_size = key.value()[OBFUSCATE("content")].size();
			for (auto& content : key.value()[OBFUSCATE("content")].items())
			{
				if (counter % 2)
					ImGui::SameLine();

				std::string spot_name = content.value()[OBFUSCATE("spot_name")].get<std::string>();
				// render all buttons with half width but the last one with full width if it's alone
				counter == content_size - 1 && !(counter % 2) ? button_length = window_width : button_length = half_window_width;
				++counter;
				if (ImGui::Button(spot_name.c_str(), ImVec2(button_length, 50)))
				{
					position.x = content.value()[OBFUSCATE("coordinates")][0].get<float>();
					position.y = content.value()[OBFUSCATE("coordinates")][1].get<float>();
					position.z = content.value()[OBFUSCATE("coordinates")][2].get<float>();
					avatars[OBFUSCATE("avatar_1")].Teleport(position);
				}
			}
		}
	}
}

void draw_farming_list(const char* title, const char* icon, nlohmann::ordered_json& coordinates, bool& state, int& point)
{
	ImGui::Begin(title, &state);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 4, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once);
	static ImFont* font = ImGui::GetFont();
	if (font->FontSize > 24)
		ImGui::SetWindowFontScale(24 / font->FontSize);
	ImGui::BeginChild(OBFUSCATE("List"));
	int idx = 0;
	for (auto& positions : coordinates.items())
	{
		char posBuff[100] = "";
		nlohmann::ordered_json& position = positions.value();
		vec3 pos(position[0], position[1], position[2]);
		sprintf(posBuff, OBFUSCATE("[%.3f, %.3f, %.3f]"), pos.x, pos.y, pos.z);

		bool is_active = (point == idx);
		float piece_width = ImGui::GetContentRegionAvail().x;
		if (is_active)
			ImGui::SetScrollHereY();

		if (HellWidget::ClickablePiece(posBuff, icon, is_active, ImVec2(piece_width, 50), ImGuiButtonFlags_None))
		{
			avatars[OBFUSCATE("avatar_1")].Teleport(pos);
			point = idx;
		}
		++idx;
	}
	ImGui::EndChild();
	ImGui::End();
}

void draw_farming_window()
{
	if (avatars.empty())
		return;

	float window_width = ImGui::GetContentRegionAvail().x;
	static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
	float half_window_width = ImGui::GetContentRegionAvail().x / 2;

	enum RUNTYPE {CANDLE = 0, STAR, OOB};
	static RUNTYPE runtype;

	ImGui::PushStyleColor(ImGuiCol_Button , runtype == CANDLE ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	if (IconLoader::iconButton(icons.UiMenuCandleOutline, size))
		runtype = CANDLE;
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button , runtype == STAR ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	if (IconLoader::iconButton(icons.UiMenuCollect, size))
		runtype = STAR;
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button , runtype == OOB ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	if (IconLoader::iconButton(icons.UiMusicSustain, size))
		runtype = OOB;

	ImGui::PopStyleColor(3);

	struct Point { int limit; int current; };
	static Point candle_point;
	static Point star_point;
	static bool single_candle_farm_window;
	static bool single_start_farm_window;
	switch (runtype)
	{
		case CANDLE:
			if (trigger.run_by_teleport)
			{
				if (IconLoader::iconButton(icons.UiMenuHideCandle, size))
					trigger.run_by_teleport = false;

				if (candle_point.current <= candle_point.limit)
					candle_point.current = progress.farming.current;
				ImGui::SameLine();
				ImGui::ProgressBar(progress.farming.get_progress(), ImVec2(ImGui::GetContentRegionAvail().x, size + HellboyStyle.FramePadding.y));
			}
			else if (IconLoader::iconButton(icons.UiMenuHeartCandle, size))
			{
				// the run is done in the Update function on another thread
				g_farming_coordinates = &candles_coordinates[Hellboy::level_name];
				g_farming_interval = Hellboy::candle_run_interval;
				if (candle_point.current >= candle_point.limit || candle_point.current > 0)
					candle_point.current = 0;
				progress.farming.current = candle_point.current;
				trigger.run_by_teleport = true;
			}

			if (candles_coordinates.contains(Hellboy::level_name))
			{
				candle_point.limit = candles_coordinates[Hellboy::level_name].size() - 1;
				static std::string run_level;
				if (run_level != Hellboy::level_name)
				{
					candle_point.current = -1;
					run_level = Hellboy::level_name;
				}

				if (IconLoader::iconButton(icons.UiMenuInboxReply, size))
				{
					if (candles_coordinates[Hellboy::level_name].empty())
						return;
					if (candle_point.current <= 0)
						candle_point.current = 0;
					else
						--candle_point.current;

					float x = candles_coordinates[run_level][candle_point.current][0];
					float y = candles_coordinates[run_level][candle_point.current][1];
					float z = candles_coordinates[run_level][candle_point.current][2];
					avatars[OBFUSCATE("avatar_1")].Teleport({x, y, z});
				}
				ImGui::SameLine();
				if (IconLoader::iconButton(icons.UiMenuHand, size))
				{
					if (candles_coordinates[Hellboy::level_name].empty())
						return;
					if (candle_point.current >= candle_point.limit)
						candle_point.current = candle_point.limit;
					else
						++candle_point.current;

					float x = candles_coordinates[run_level][candle_point.current][0];
					float y = candles_coordinates[run_level][candle_point.current][1];
					float z = candles_coordinates[run_level][candle_point.current][2];
					avatars[OBFUSCATE("avatar_1")].Teleport({x, y, z});
				}
				ImGui::SameLine();
				HellWidget::SwitchingIcon(OBFUSCATE("Single Candle Farm"), icons.UiSocialChatLog, &single_candle_farm_window, size, true);
			}
			break;
		case STAR:
			if (trigger.run_by_teleport)
			{
				if (IconLoader::iconButton(icons.UiMiscFavoriteOutline, size))
					trigger.run_by_teleport = false;

				if (star_point.current <= star_point.limit)
					star_point.current = progress.farming.current;
				ImGui::SameLine();
				ImGui::ProgressBar(progress.farming.get_progress(), ImVec2(ImGui::GetContentRegionAvail().x, size + HellboyStyle.FramePadding.y));
			}
			else if (IconLoader::iconButton(icons.UiMiscFavorite, size))
			{
				// the run is done in the Update function on another thread
				g_farming_coordinates = &stars_coordinates[Hellboy::level_name];
				g_farming_interval = Hellboy::star_run_interval;
				if (star_point.current >= star_point.limit || star_point.current > 0)
					star_point.current = 0;
				progress.farming.current = star_point.current;
				trigger.run_by_teleport = true;
			}

			if (stars_coordinates.contains(Hellboy::level_name))
			{
				star_point.limit = stars_coordinates[Hellboy::level_name].size() - 1;
				static std::string run_level;
				if (run_level != Hellboy::level_name)
				{
					star_point.current = -1;
					run_level = Hellboy::level_name;
				}

				if (IconLoader::iconButton(icons.UiMenuInboxReply, size))
				{
					if (stars_coordinates[Hellboy::level_name].empty())
						return;
					if (star_point.current <= 0)
						star_point.current = 0;
					else
						--star_point.current;

					float x = stars_coordinates[run_level][star_point.current][0];
					float y = stars_coordinates[run_level][star_point.current][1];
					float z = stars_coordinates[run_level][star_point.current][2];
					avatars[OBFUSCATE("avatar_1")].Teleport({x, y, z});
				}
				ImGui::SameLine();
				if (IconLoader::iconButton(icons.UiMenuHand, size))
				{
					if (stars_coordinates[Hellboy::level_name].empty())
						return;
					if (star_point.current >= star_point.limit)
						star_point.current = star_point.limit;
					else
						++star_point.current;

					float x = stars_coordinates[run_level][star_point.current][0];
					float y = stars_coordinates[run_level][star_point.current][1];
					float z = stars_coordinates[run_level][star_point.current][2];
					avatars[OBFUSCATE("avatar_1")].Teleport({x, y, z});
				}
				ImGui::SameLine();
				HellWidget::SwitchingIcon(OBFUSCATE("Single Star Farm"), icons.UiSocialChatLog, &single_start_farm_window, size, true);
			}

			break;
		case OOB:
			break;
		default:
			break;
	}



	bool disabled = trigger.run_by_teleport;
	ImGui::BeginDisabled(disabled);
	ImGui::Separator();
	if (single_candle_farm_window)
		draw_farming_list(OBFUSCATE("Candles List"), "UiOutfitPendantAP02", candles_coordinates[Hellboy::level_name], single_candle_farm_window, candle_point.current);
	if (single_start_farm_window)
		draw_farming_list(OBFUSCATE("Star List"), "UiOutfitPendantAP02", stars_coordinates[Hellboy::level_name], single_start_farm_window, star_point.current);
	draw_teleport_list(goto_spots_list);
	if (disabled)
		ImGui::EndDisabled();
}