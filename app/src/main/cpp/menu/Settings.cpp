#include "menu.h" 

void draw_settings_window()
{
	static float size = 65 * ImGui::GetIO().DisplaySize.y / 1080;
	ImGui::Checkbox(OBFUSCATE("Window Auto Resize"), &configs.ui_AutoResize);
	ImGui::Checkbox(OBFUSCATE("Show Hell Menu Text"), &configs.ui_ShowHellMenuText);
	if (ImGui::Button("Reset Configs"))
		HellboyIO::reset_configs();
	ImGui::SliderFloat("Font Scale Constant", &configs.kFontScale, 20, 30, "%.0f");

	if (ImGui::CollapsingHeader(OBFUSCATE("Allowed Windows")))
		for (auto& menu : hell_menus)
			if (*menu.second.is_public() && menu.first != OBFUSCATE("Settings Menu"))
				HellWidget::SwitchingIcon(menu.first.c_str(), menu.second.icon(), menu.second.is_allowed(), size);

}