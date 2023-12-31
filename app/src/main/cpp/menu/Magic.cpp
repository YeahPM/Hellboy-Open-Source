#include "menu.h"
#include "../hellboy/spell_buff.h"

void draw_magic_window()
{
	static Types type = Body;
	static float size = 60 * ImGui::GetIO().DisplaySize.y / 1080;

	if (ImGui::BeginTable(OBFUSCATE("Inventory"), 2))
	{
		float category_width = size + (ImGui::GetStyle().FramePadding.x * 2);
		ImGui::TableSetupColumn(OBFUSCATE("Category"), ImGuiTableColumnFlags_WidthFixed, category_width);
		ImGui::TableSetupColumn(OBFUSCATE("Spell"), ImGuiTableColumnFlags_WidthStretch);
		ImGui::TableNextRow();

		ImGui::TableSetColumnIndex(0);

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Body));
		if (IconLoader::iconButton(icons.UiOutfitBodyClassicPants, size))
			type = Body;

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Mask));
		if (IconLoader::iconButton(icons.UiOutfitMaskBasic, size))
			type = Mask;

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Hair));
		if (IconLoader::iconButton(icons.UiOutfitHairBraidSideSmall, size))
			type = Hair;

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Cape));
		if (IconLoader::iconButton(icons.UiOutfitCape, size))
			type = Cape;

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Prop));
		if (IconLoader::iconButton(icons.UiOutfitPropHarp, size))
			type = Prop;

		ImGui::PushStyleColor(ImGuiCol_Button, HellWidget::IsButtonOn(type == Misc));
		if (IconLoader::iconButton(icons.UiOutfitPropDOL23CrabFireworks, size))
			type = Misc;

		ImGui::PopStyleColor(6);

		ImGui::TableSetColumnIndex(1);
		ImGui::BeginChild(OBFUSCATE("spells"));

		ImGui::PushStyleColor(ImGuiCol_Button, {0, 0, 0, 0});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0, 0, 0, 0});
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0, 0, 0, 0});

		static std::string name;
		static std::string icon;
		if (IconLoader::iconButton(icons.UiMenuNoSymbol, size))
			Hellboy::SetSpell(0, type + 1, false);
		ImGui::SameLine();
		IconLoader::icon(icon, size);

		ImGui::PopStyleColor(3);

		for (auto& it : spell_buffs.items())
		{
			nlohmann::json& info = it.value();
			if (info[OBFUSCATE("type")].get<Types>() != type)
				continue;

			bool is_selected = *Hellboy::GetSpell(type + 1) == info[OBFUSCATE("id")].get<int>();
			name = info[OBFUSCATE("name")].get<std::string>();
			icon = info[OBFUSCATE("icons")].get<std::string>();
			if (HellWidget::SwitchingIcon(name.c_str(), icon.c_str(), &is_selected, size))
				Hellboy::SetSpell(info[OBFUSCATE("id")].get<int>(), type + 1, true);
		}

		ImGui::EndChild();
		ImGui::EndTable();
	}
}




