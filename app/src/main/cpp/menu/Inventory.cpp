#include "menu.h" 

static float size;
static float icon_size;

void avatar_mods()
{
	HellWidget::SwitchingIcon(OBFUSCATE("Always Walk"), icons.UiSocialFollow, &configs.ol_alwaysMove, icon_size);
	if (HellWidget::SwitchingIcon(OBFUSCATE("Lock Coordinates"), icons.UiEmoteFloat, &patch[OBFUSCATE("lock_coordinates")].state, icon_size))
		patch[OBFUSCATE("lock_coordinates")].switchPatch();

	if (HellWidget::SwitchingIcon(OBFUSCATE("Iphone Headphones"), icons.UiOutfitHornRainbowHeadphones, &patch[OBFUSCATE("iphone_headphones")].state, icon_size))
		patch[OBFUSCATE("iphone_headphones")].switchPatch();

	if (HellWidget::SwitchingIcon(OBFUSCATE("Simulate Scooter"), icons.UiMenuInboxReply, &patch[OBFUSCATE("simulate_scooter")].state, icon_size))
		patch[OBFUSCATE("simulate_scooter")].switchPatch();

	HellWidget::SwitchingIcon(k->ShoutAutoRelease.name.c_str(), icons.UiEmoteCallDefault, k->ShoutAutoRelease.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->Disable_Avatar.name.c_str(), icons.UiEmoteAP01Respect, k->Disable_Avatar.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->FlameInHand.name.c_str(), icons.UiMenuFlame, k->FlameInHand.get<bool>(), icon_size);
	ImGui::SliderFloat(OBFUSCATE("Cape Opacity"), (float*)(*(uintptr_t*)(avatars[OBFUSCATE("avatar_1")].GetAvatar() + 40) + 0x74), 0, 1, "%0.1f");
}

void ui_mods()
{
	if (HellWidget::SwitchingIcon(OBFUSCATE("Fast Home"), icons.UiMenuGate, &configs.ol_fast_home, icon_size))
		patch[OBFUSCATE("fast_home")].switchPatch(configs.ol_fast_home);

	HellWidget::SwitchingIcon(k->Invincibility.name.c_str(), icons.UiEmoteAP08ChestPound, k->Invincibility.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(OBFUSCATE("Unlock Closet"), icons.UiOutfitPropAP10Bookshelf, &g_has_unlock, icon_size);

	if (HellWidget::SwitchingIcon(OBFUSCATE("Upgrade Emotes"), icons.UiMenuReactionLike, &patch[OBFUSCATE("upgrade_emote")].state, icon_size))
	{
		patch[OBFUSCATE("upgrade_emote")].switchPatch(patch[OBFUSCATE("upgrade_emote")].state);
		patch[OBFUSCATE("allow_upgrade_emote")].switchPatch(patch[OBFUSCATE("upgrade_emote")].state);
	}

	if (HellWidget::SwitchingIcon(OBFUSCATE("Outfits Reveal"), icons.UiMenuStageLightsOn, &patch[OBFUSCATE("outfits_reveal")].state, icon_size))
		patch[OBFUSCATE("outfits_reveal")].switchPatch(patch[OBFUSCATE("outfits_reveal")].state);

	HellWidget::SwitchingIcon(k->EnableAllRelationshipAbilities.name.c_str(), icons.UiMenuPetCat, k->EnableAllRelationshipAbilities.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->KeepCornerButtonsVisible.name.c_str(), icons.UiMenuPhone, k->KeepCornerButtonsVisible.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->AllNpcsHaveRadar.name.c_str(), icons.UiMiscHide, k->AllNpcsHaveRadar.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->ForceReactionMenu.name.c_str(), icons.UiMenuReactionOpen, k->ForceReactionMenu.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->EnableQuickMenu.name.c_str(), icons.UiMenuMoveHandle, k->EnableQuickMenu.get<bool>(), icon_size);
}

void camera_mods()
{
	if (allocations->screenshot_resolution)
	{
		ImGui::Text("%s", OBFUSCATE("Screenshot Resolution"));
		ImGui::SliderFloat(OBFUSCATE(" :Width"), (allocations->screenshot_resolution.as_float() + 0x0), 1000, 15000, "%.f");
		ImGui::SliderFloat(OBFUSCATE(" :Height"), (allocations->screenshot_resolution.as_float() + 0x1), 1000, 10500, "%.f");
		static int res_mul = 1;

		if (ImGui::SliderInt(OBFUSCATE(" :Multiply"), &res_mul, 1, 5))
		{
			*(allocations->screenshot_resolution.as_float() + 0x0) = ImGui::GetIO().DisplaySize.x * res_mul;
			*(allocations->screenshot_resolution.as_float() + 0x1) = ImGui::GetIO().DisplaySize.y * res_mul;
		}
		if (ImGui::Button(OBFUSCATE("Reset Resolution"), ImVec2(-1.0f, 0.0f)))
		{
			*(allocations->screenshot_resolution.as_float() + 0x0) = ImGui::GetIO().DisplaySize.x;
			*(allocations->screenshot_resolution.as_float() + 0x1) = ImGui::GetIO().DisplaySize.y;
		}
	}
	HellWidget::SwitchingIcon(k->ForceNativeRes.name.c_str(), icons.UiMenuGraphics60fps, k->ForceNativeRes.get<bool>(), icon_size);
	HellWidget::SwitchingIcon(k->BlackWhite.name.c_str(), icons.UiMenuStageBackdrop, k->BlackWhite.get<bool>(), icon_size);
	if (HellWidget::SwitchingIcon(OBFUSCATE("Unlock Zoom"), icons.UiMenuStageLightsOn, &patch[OBFUSCATE("unlock_zoom")].state, icon_size))
		patch[OBFUSCATE("unlock_zoom")].switchPatch(patch[OBFUSCATE("unlock_zoom")].state);
}

void environment_mods()
{
	if (HellWidget::SwitchingIcon(OBFUSCATE("Remove Winds"), icons.UiMenuStageFallingFlower, &patch[OBFUSCATE("remove_winds")].state, icon_size))
		patch[OBFUSCATE("remove_winds")].switchPatch(patch[OBFUSCATE("remove_winds")].state);
	ImGui::DragFloat(k->FlameToCandleScale.name.c_str(), k->FlameToCandleScale.get<float>(), 1.0f, 0.0f, 0.0f, "%.1f");
}

void creators_mods()
{
	if (HellWidget::SwitchingIcon(OBFUSCATE("Krill Paralyse"), icons.UiMenuBuffCatCurse, &patch[OBFUSCATE("krill_paralyse")].state, icon_size))
		patch[OBFUSCATE("krill_paralyse")].switchPatch();

	HellWidget::SwitchingIcon(k->FishSchoolDebug.name.c_str(), icons.UiOutfitPropAP17Manta, k->FishSchoolDebug.get<bool>(), icon_size);
}

void draw_inventory_window()
{
	enum CATEGORY { AVATAR = 0, UI, CAMERA, ENVIRONMENT, CREATURES };
	static CATEGORY category = AVATAR;
	size = 60 * ImGui::GetIO().DisplaySize.y / 1080;
	icon_size = 50 * ImGui::GetIO().DisplaySize.y / 1080;

	if (ImGui::BeginTable(OBFUSCATE("Inventory"), 2))
	{
		float category_width = size + (ImGui::GetStyle().FramePadding.x * 2);
		ImGui::TableSetupColumn(OBFUSCATE("Category"), ImGuiTableColumnFlags_WidthFixed, category_width);
		ImGui::TableSetupColumn(OBFUSCATE("Mods"), ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);

		ImGui::PushStyleColor(ImGuiCol_Button , category == AVATAR ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (IconLoader::iconButton(icons.UiEmoteStanceHero, size))
			category = AVATAR;

		ImGui::PushStyleColor(ImGuiCol_Button , category == UI ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (IconLoader::iconButton(icons.UiMenuFullscreen, size))
			category = UI;

		ImGui::PushStyleColor(ImGuiCol_Button , category == CAMERA ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (IconLoader::iconButton(icons.UiMenuCamera, size))
			category = CAMERA;

		ImGui::PushStyleColor(ImGuiCol_Button , category == ENVIRONMENT ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (IconLoader::iconButton(icons.UiOutfitPropAP17Chimes, size))
			category = ENVIRONMENT;

		ImGui::PushStyleColor(ImGuiCol_Button , category == CREATURES ? g_Colors[ImGuiCol_ButtonHovered] : ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (IconLoader::iconButton(icons.UIMenuBuffCrabDuck, size))
			category = CREATURES;

		ImGui::PopStyleColor(5);

		ImGui::TableSetColumnIndex(1);
		ImGui::BeginChild(OBFUSCATE("inv"));
		switch (category)
		{
			case AVATAR:
				avatar_mods();
				break;
			case UI:
				ui_mods();
				break;
			case CAMERA:
				camera_mods();
				break;
			case ENVIRONMENT:
				environment_mods();
				break;
			case CREATURES:
				creators_mods();
				break;
		}
		ImGui::EndChild();
		ImGui::EndTable();
	}
}