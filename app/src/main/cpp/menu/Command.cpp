#include "menu.h" 


void draw_command_window()
{
	static float size = 60 * ImGui::GetIO().DisplaySize.y / 1080;
	ImGui::Text(OBFUSCATE("User Command: %s"), g_UserMessage.c_str());
	HellWidget::SwitchingIcon(OBFUSCATE("Use Chat Commands"), icons.UiSocialChatUnlock, &configs.ol_use_commands, size);
	HellWidget::SwitchingIcon(OBFUSCATE("Allow Message With Prefix"), icons.UiMenuReactionClap, &configs.ol_show_commands, size);
}
