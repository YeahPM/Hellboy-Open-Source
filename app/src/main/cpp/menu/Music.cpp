#include "menu.h"

void draw_music_window()
{
	if (!functions->PianoButton_SimulateTap || !functions->PianoButton_OnStart)
		return;

	static float button_size = 60 * ImGui::GetIO().DisplaySize.y / 1080;
	char buff[100] = "";
	sprintf(buff, OBFUSCATE("Current Instrument: %s"), instruments[g_instrument_type].name);
	HellWidget::SwitchingIcon(buff, instruments[g_instrument_type].icon, &g_sound_selector, button_size);

	HellWidget::SwitchingIcon(OBFUSCATE("Enable instrument Selector"), icons.UiMatchNfc, &g_sound_selector, button_size);
	HellWidget::SwitchingIcon(OBFUSCATE("Enable Karaoke Mode"), icons.UiSocialFavorite, &g_karaoke_mode, button_size);

	ImGui::BeginChild(OBFUSCATE("##Instruments"));
	ImVec2 content_available = ImGui::GetContentRegionAvail();
	int max_buttons_in_row = (int)(content_available.x / (button_size + HellboyStyle.FramePadding.x * 2));

	int button_count = 1;
	for (int i = 0; i < IM_ARRAYSIZE(instruments); ++i)
	{
		bool is_selected = !(strcmp(instruments[i].name, instruments[g_instrument_type].name));
		ImVec4 color = is_selected ? ImVec4(0.000f, 0.840f, 0.102f, 1.000f) : g_Colors[ImGuiCol_ButtonHovered];

		ImGui::PushID(instruments[i].name);
		if (IconLoader::iconButton(instruments[i].icon, button_size, color))
			g_instrument_type = i;
		ImGui::PopID();
		if (button_count++ < max_buttons_in_row - 1)
			ImGui::SameLine();
		else
			button_count = 1;
	}
	ImGui::EndChild();
}
