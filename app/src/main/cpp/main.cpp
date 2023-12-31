#include "main.h"
#include "menu/menu.h"


#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif
bool init_is_done;








/*void drawPlayerLabel(Avatar* avatar)
{
	vec3 pos = *avatar->GetPos();
	Vec3 point = {pos.x, pos.y, pos.z};
	Vec4 test = Renderer::project3D(point);
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	ImVec2 text_size = ImGui::CalcTextSize(avatar->IsBot() ? "Spirit" : "Player");
	draw_list->AddRectFilled({test.x, test.y}, ImVec2(test.x + text_size.x, test.y + text_size.y), IM_COL32(0, 0, 0, 100));
	draw_list->AddText({test.x, test.y}, 0xFFFFFFFF, avatar->IsBot() ? "Spirit" : "Player");
}*/






[[noreturn]] void* update_imgui(void*)
{
	while (true)
	{
		usleep(10000);
		static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
		{
			// green border effect
			static int sign = 1;
			static double current_color = 0;
			if (current_color <= 0)
			{
				sign = 1;
				usleep(2000000);
			}
			else if (current_color >= 0.9)
				sign = -1;
			current_color += 0.001 * sign;
			HellboyStyle.Colors[ImGuiCol_Border].y = (float)current_color;
		}
	}
}

ImTextureID hellboy_logo;

void load_window(const char* text, MenuItem& menuItem)
{
	if(*menuItem.state())
	{
		if (configs.ui_AutoResize)
			ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 4, ImGui::GetIO().DisplaySize.y / 2));

		char buffer[50] = "";
		char title[50] = "";
		strncpy(buffer, text, Hellboy::StringFind(text, OBFUSCATE("Menu")));
		sprintf(title, "%s##hell_window", buffer);

		ImGui::Begin(title, menuItem.state());
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 4, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Once);
		static ImFont* font = ImGui::GetFont();
		//if (font->FontSize > 24)
		//	ImGui::SetWindowFontScale(24 / font->FontSize);
		ImGui::SetWindowFontScale(configs.kFontScale / font->FontSize);
		menuItem.menu();
		HellWidget::DockWindowToScreen();
		ImGui::End();
	}
}

void draw_menu_icon(const char* text, MenuItem& menuItem)
{
	static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0, 0, 0, 0});
	static ImVec4* colors =  HellboyStyle.Colors;
	ImGui::PushID(text);

	if (IconLoader::iconButton(menuItem.icon(), size, *menuItem.state() ? colors[ImGuiCol_ButtonHovered] : colors[ImGuiCol_Text]))
		*menuItem.state() = !*menuItem.state();
	if (configs.ui_ShowHellMenuText)
	{
		ImGui::TableSetColumnIndex(1);
		ImGui::Spacing();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20 * ImGui::GetIO().DisplaySize.y / 1080);
		ImGui::Text("%s", text);
	}

	ImGui::PopID();
	ImGui::PopStyleColor(3);
}




#include "include/imgui/imgui_internal.h"
void LoadingSpinner(const char* label, ImVec2 pos, float radius, ImVec4 color) {
	ImGuiContext& g = *GImGui;
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	//draw_list->PushClipRectFullScreen();

	const float PULSE_SPEED = 5.0f;
	const float SPIN_SPEED = 3.0f;
	float pulse = (sinf(g.Time * PULSE_SPEED) + 1) * 0.4 + 0.2;
	float _radius = radius / 3;
	float angle = -g.Time * (SPIN_SPEED);
	radius = radius * pulse;
	for (int i = 0; i < 4; i++) {
		float _angle = (M_PI / 2) * (float)(i) + angle;
		draw_list->AddCircleFilled(ImVec2(sinf(_angle) * radius + pos.x, cosf(_angle) * radius + pos.y), _radius, ImGui::GetColorU32(color));
	}

	//draw_list->PopClipRect();
}






void draw_closet_menu()
{
	uintptr_t game_ptr_cd = *(skyRoots->game_ptr.as_ptr() + 0xCD);
	if (!game_ptr_cd)
		return;
	uintptr_t closet_ptr = *(uintptr_t*)(game_ptr_cd + 0x108);
	if (!closet_ptr)
		return;

	int* closet = (int*)(closet_ptr + 0x54);
	bool* is_opened = (bool*)(closet - 0xF);
	//ImGui::SetNextWindowPos(ImVec2(width, ImGui::GetIO().DisplaySize.y / onLoadConfigs.fClosetBarHeight), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	ImGui::SetNextWindowPos(configs.wp_closet, ImGuiCond_Once);

	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
									ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_AlwaysAutoResize |
									ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Closet Bar", nullptr, flags);

	configs.wp_closet = HellWidget::DockWindowToScreen();
	static ImVec4 active = HellboyStyle.Colors[ImGuiCol_ButtonHovered];
	static ImVec4 inactive = HellboyStyle.Colors[ImGuiCol_Text];

	static float size = 60 * ImGui::GetIO().DisplaySize.y / 1080;

	ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0, 0, 0, 0});
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0, 0, 0, 0});

	if (IconLoader::iconButton(icons.UiOutfitBodyClassicPants, size, *closet == 0 && *is_opened ? active : inactive))
		Hellboy::OpenCloset(0);
	ImGui::SameLine();

	if (IconLoader::iconButton(icons.UiOutfitMaskBasic, size, *closet == 3 && *is_opened ? active : inactive))
		Hellboy::OpenCloset(3);
	ImGui::SameLine();

	if (IconLoader::iconButton(icons.UiOutfitHairBraidSideSmall, size, *closet == 2 && *is_opened ? active : inactive))
		Hellboy::OpenCloset(2);
	ImGui::SameLine();

	if (IconLoader::iconButton(icons.UiOutfitCape, size, *closet == 1 && *is_opened ? active : inactive))
		Hellboy::OpenCloset(1);
	ImGui::SameLine();

	if (IconLoader::iconButton(icons.UiOutfitPropHarp, size, *closet == 8 && *is_opened ? active : inactive))
		Hellboy::OpenCloset(8);

	ImGui::PopStyleColor(3);

	ImGui::End();
}

void draw_hell_menu()
{
	static ImGuiWindowFlags flags =  ImGuiWindowFlags_NoTitleBar |
									ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_NoBackground |
									ImGuiWindowFlags_NoBringToFrontOnFocus |
									ImGuiWindowFlags_AlwaysAutoResize |
									ImGuiWindowFlags_NoScrollbar;

	ImGui::Begin(OBFUSCATE("HellMenu"), nullptr, flags);

	ImGui::Text(OBFUSCATE("Level: %s"), Hellboy::level_name);

	static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
	if (ImGui::ImageButton(hellboy_logo, ImVec2(size, size)))
		g_hell_menu_collapsed = !g_hell_menu_collapsed;

	ImGui::SameLine();	ImGui::Text("%s", OBFUSCATE("Hi ren"));

	if (ImGui::BeginTable(OBFUSCATE("###hell_menu"), configs.ui_ShowHellMenuText ? 2 : 1))
	{
		ImGui::TableSetupColumn(OBFUSCATE("texts"), ImGuiTableColumnFlags_WidthFixed, size * 2);
		if (configs.ui_ShowHellMenuText)
			ImGui::TableSetupColumn(OBFUSCATE("buttons"), ImGuiTableColumnFlags_WidthStretch);


		if (g_hell_menu_collapsed || !init_is_done)
		{
			ImGui::EndTable();
			return ImGui::End();
		}


		for (auto& menu : hell_menus)
			if (*menu.second.is_public() && *menu.second.is_allowed())
				draw_menu_icon(menu.first.c_str(), menu.second);



		ImGui::EndTable();
	}

	ImGui::End();
	draw_closet_menu();
}



bool Init_Menu()
{
	Hellboy::setColors(&ImGui::GetStyle(), true);
	memcpy(&HellboyStyle, &ImGui::GetStyle(), sizeof(ImGuiStyle));
	g_Colors = HellboyStyle.Colors;
	INCLUDE_IMG(logo_png)
	hellboy_logo = getTextureID(&logo_png);
	pthread_t update_thread;
	pthread_create(&update_thread, nullptr, update_imgui, nullptr);
	pthread_detach(update_thread);
	return true;
}

void Main()
{
	static bool init_menu = Init_Menu();
	memcpy(&ImGui::GetStyle(), &HellboyStyle, sizeof(ImGuiStyle));
	draw_hell_menu();

	if (!init_is_done)
		return;

	for (auto& menu : hell_menus)
		if (*menu.second.is_public() && *menu.second.is_allowed() && init_is_done)
			load_window(menu.first.c_str(), menu.second);

	Hellboy::setColors(&ImGui::GetStyle(), false);
}

[[noreturn]] void* Update(void*)
{
	while (true)
	{
		if (!init_is_done)
			continue;

		Hellboy::GetLevel();
		//Hellboy::GetUserAuth();

		ChatBox::ScanUserMessage(g_UserMessage);
		Hellboy::SpeedUpAndDelay(1000000, trigger.change_level);

		if (allocations->screenshot_resolution)
		{
			*(allocations->screenshot_resolution.as_float() + 0x3) = (float)(*(allocations->screenshot_resolution.as_float() + 0x0) * 0.16544028);
			*(allocations->screenshot_resolution.as_float() + 0x4) = (float)(*(allocations->screenshot_resolution.as_float() + 0x1) * 0.34618056);
		}

		//	player movement restriction from [Live v0.20.1 (210508)] offset: 0x85ACE0
		if (configs.ol_alwaysMove)
			*(float*)(*(long*)(skyRoots->game_ptr.get_address() + 0x300) + 0xAC9C) = 1.0;

		Hellboy::IterationFarming(*g_farming_coordinates, g_farming_interval);

		for (auto& p : patch)
			p.second.update();

		usleep(100);
		HellboyIO::SaveConfigs();
	}
}



func (*start_ptr)() = Start;
void* Init(void*)
{
	LOGI(TAG_HELLBOY, "----< Sky %s Started >----", Cipher::isGameBeta() ? "Beta" : "Live");
	LOGI(TAG_HELLBOY, "started init thread");

	//init_elf_segments(libBootloader_Segments, OBFUSCATE("libBootloader.so"));

	HellboyIO::GetModPath();
	HellboyIO::LoadConfigs();
	HellboyIO::SaveConfigs();

	if (!configs.ws_settings)
	{
		configs.ol_show_commands = true;
		configs.ol_use_commands = true;
	}

	patch[OBFUSCATE("fast_home")].switchPatch(configs.ol_fast_home);


	hell_menus.emplace(OBFUSCATE("Avatars Menu"), MenuItem(draw_avatar_window, icons.UiEmoteStanceDefault, false, &configs.ws_avatar, true));
	hell_menus.emplace(OBFUSCATE("Change Level Menu"), MenuItem(draw_change_level_window, icons.UiMenuGate, false, &configs.ws_changeLevel, true));
	hell_menus.emplace(OBFUSCATE("Inventory Menu"), MenuItem(draw_inventory_window, icons.UiMenuTabInventoryProps, false, &configs.ws_inventory, true));
	hell_menus.emplace(OBFUSCATE("Farming Menu"), MenuItem(draw_farming_window, icons.UiEmoteSocialScandle, false, &configs.ws_farming, true));
	hell_menus.emplace(OBFUSCATE("Command Menu"), MenuItem(draw_command_window, icons.UiHudShieldSplit1, false, &configs.ws_command, true));
	hell_menus.emplace(OBFUSCATE("Music Menu"), MenuItem(draw_music_window, icons.UiMenuSheetMusic004, false, &configs.ws_music, true));
	hell_menus.emplace(OBFUSCATE("Settings Menu"), MenuItem(draw_settings_window, icons.UiMenuCog, false, &configs.ws_settings, true));
	hell_menus.emplace(OBFUSCATE("Magic Menu"), MenuItem(draw_magic_window, icons.UiMenuBuffPotionShop, false, &configs.ws_magic, true));
	hell_menus.emplace(OBFUSCATE("Styles Menu"), MenuItem(draw_styles_window, icons.UiSocialChatLog, false, &configs.ws_style, true));
	hell_menus.emplace(OBFUSCATE("Debug Menu"), MenuItem(draw_debug_window, icons.UiMenuShieldCrack, false, &configs.ws_debug, true));

	skyRoots = new SkyRoots;


	Hellboy::bootloader = Cipher::get_libBase();
	checkpointBarn = new CheckpointBarn;

	pthread_t sky_hooks_thread;
	pthread_create(&sky_hooks_thread, nullptr, get_functions, nullptr);
	pthread_detach(sky_hooks_thread);

	pthread_t sky_consts_thread;
	pthread_create(&sky_consts_thread, nullptr, get_bool_constants, nullptr);
	pthread_detach(sky_consts_thread);

	pthread_t sky_patches_thread;
	pthread_create(&sky_patches_thread, nullptr, get_patches, nullptr);
	pthread_detach(sky_patches_thread);

	do {
		level_name_ptr = get_from_memory(OBFUSCATE(R"( "LevelObjects" )"), OBFUSCATE("xxxxxxxxxxxxxxxx"), ANON_BSS, 0x11);
		if (level_name_ptr)
			LOGI(OBFUSCATE(TAG_MEMSCAN), OBFUSCATE("Level pointer is initialised to 0x%p"), level_name_ptr.as_ptr());
	} while (!level_name_ptr);
	get_pointers();



	get_allocations_from_memory();

	pthread_t update_thread;
	pthread_create(&update_thread, nullptr, Update, nullptr);
	pthread_detach(update_thread);

	SkySong::Init();

	init_is_done = true;
	LOGI(OBFUSCATE(TAG_HELLBOY), OBFUSCATE("init thread is done"), 0);
	return nullptr;
}