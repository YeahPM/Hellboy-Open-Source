#include "menu.h"


#include "../include/misc/fileselector.h"

#include <fstream>
#define TAG_MUSIC "HB-MUSIC"



void draw_debug_window()
{

	if (ImGui::Button("Get Auth"))
		Hellboy::get_auth = true;

	static uintptr_t g_uiBarn = *(uintptr_t*)(Hellboy::bootloader + 0x1986E00);
	static uintptr_t dummyEmitter = *(uintptr_t*)(Hellboy::bootloader + 0x16D1008);


	if (ImGui::Button("Import"))
		SkySong::ImportSheet();

	if (ImGui::Button("Play"))
		SkySong::Play();
	ImGui::SameLine();
	if (ImGui::Button("Pause"))
		SkySong::Pause();
	if (ImGui::Button("Stop"))
		SkySong::Stop();
	ImGui::SameLine();

	static std::string sheet_label = "none";// = SkySong::SheetList[0]["name"].get<std::string>();
	ImGui::Text("Sheets %lu", SkySong::SheetList.size());
	if (ImGui::BeginCombo(OBFUSCATE("Select Sheet"), sheet_label.c_str()))
	{
		for (std::size_t i = 0; i < SkySong::SheetList.size(); ++i)
		{
			if (ImGui::Selectable(SkySong::SheetList[i][0]["name"].get<std::string>().c_str()))
			{
				SkySong::selected_sheet = i;
				sheet_label = SkySong::SheetList[i][0]["name"].get<std::string>();
			}
		}
		ImGui::EndCombo();
	}


}