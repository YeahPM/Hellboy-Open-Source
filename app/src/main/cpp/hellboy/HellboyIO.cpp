#include "HellboyIO.h"



Configs configs;


char HellboyIO::mod_path[128];
char HellboyIO::configs_dir[128];
char HellboyIO::styles_dir[128];

void HellboyIO::LoadConfigs()
{
	FILE* p_config_file = fopen(HellboyIO::configs_dir,"r");
	if(p_config_file == nullptr)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("loading configs error: %s"), strerror(errno));
		HellboyIO::SaveConfigs();
		return;
	}

	fseek(p_config_file, 0L, SEEK_END);
	uint32_t configs_size = ftell(p_config_file);
	fseek(p_config_file, 0L, SEEK_SET);
	if (sizeof(configs) != configs_size)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("configs outdated!"));
		fclose(p_config_file);
		return;
	}
	fread(&configs, 1, configs_size, p_config_file);
	LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("configs loaded!"));
	fclose(p_config_file);
}

void HellboyIO::SaveConfigs()
{
	char buff[280] = "";
	sprintf(buff, "%s/" , HellboyIO::mod_path);

	if (access(buff, F_OK) == -1)
	{
		if (mkdir(buff, S_IRWXU) == -1)
		{
			LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("Making directory failed: %s"), strerror(errno));
			return;
		}
	}

	FILE* p_config_file = fopen(HellboyIO::configs_dir,"w");
	if (p_config_file == nullptr)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("saving configs error: %s"), strerror(errno));
		return;
	}
	fwrite(&configs, 1, sizeof(configs), p_config_file);
	LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("configs saved!"));
	fclose(p_config_file);
}

void HellboyIO::load_style()
{
	FILE* p_config_file = fopen(HellboyIO::styles_dir,"r");
	if(p_config_file == nullptr)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("loading styles error: %s"), strerror(errno));
		HellboyIO::SaveConfigs();
		return;
	}

	fseek(p_config_file, 0L, SEEK_END);
	uint32_t configs_size = ftell(p_config_file);
	fseek(p_config_file, 0L, SEEK_SET);
	if (sizeof(HellboyStyle) != configs_size)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("styles outdated!"));
		fclose(p_config_file);
		return;
	}
	fread(&HellboyStyle, 1, configs_size, p_config_file);
	LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("styles loaded!"));
	fclose(p_config_file);
}

void HellboyIO::save_style()
{
	char buff[280] = "";
	sprintf(buff, "%s/" , HellboyIO::mod_path);

	if (access(buff, F_OK) == -1)
	{
		if (mkdir(buff, S_IRWXU) == -1)
		{
			LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("Making directory failed: %s"), strerror(errno));
			return;
		}
	}

	FILE* p_config_file = fopen(HellboyIO::styles_dir,"w");
	if (p_config_file == nullptr)
	{
		LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("saving configs error: %s"), strerror(errno));
		return;
	}
	fwrite(&HellboyStyle, 1, sizeof(HellboyStyle), p_config_file);
	LOGE(OBFUSCATE(TAG_HBIO), OBFUSCATE("configs saved!"));
	fclose(p_config_file);
}

void HellboyIO::reset_configs()
{
	configs.ui_AutoResize = true;
	configs.ui_ShowHellMenuText = true;

	// window state
	configs.ws_avatar = true;
	configs.ws_changeLevel = true;
	configs.ws_settings = true;
	configs.ws_music = true;
	configs.ws_style = false;
	configs.ws_demo = false;
	configs.ws_debug = false;
	configs.ws_farming = true;
	configs.ws_inventory = true;
	configs.ws_command = false;
	configs.ws_magic = false;

	// window position
	configs.wp_closet = {0, 0};

	// on load
	configs.ol_alwaysMove = false;
	configs.ol_show_commands = true;
	configs.ol_use_commands = true;

	configs.dummy_config = true;

	configs.kFontScale = 24;

	HellboyIO::SaveConfigs();
}

void HellboyIO::GetModPath()
{
	Dl_info info;
	char buff[1000];
	dladdr((void*)start_ptr, &info);
	strlcpy(buff, info.dli_fname, strlen(info.dli_fname) - 12);
	sprintf(HellboyIO::mod_path, OBFUSCATE("%sHellboy_files"), buff);
	sprintf(HellboyIO::configs_dir, OBFUSCATE("%s/HellConfigs.cfg"), HellboyIO::mod_path);
	sprintf(HellboyIO::styles_dir, OBFUSCATE("%s/HellStyles.cfg"), HellboyIO::mod_path);
	LOGI(OBFUSCATE(TAG_HBIO), OBFUSCATE("mod's path obtained \"%s\""), HellboyIO::mod_path);
	LOGI(OBFUSCATE(TAG_HBIO), OBFUSCATE("configs path \"%s\""), HellboyIO::configs_dir);
}
