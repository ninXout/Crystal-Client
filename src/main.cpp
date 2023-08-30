#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <imgui.h>
#include "./CrystalClient/CrystalClient.hpp"
#include "Includes.hpp"
#include "Hacks.hpp"
#include "./Icon/Icon.hpp"
#include <random>
#include "./ImGui/ImGui.hpp"
#include "Shortcuts.hpp"

using namespace geode::prelude;
using namespace Crystal;
using namespace AmethystReplay;

$on_mod(Loaded) {
    //profile = Crystal::loadMods();
	loadConfigFromFile();
	Shortcuts::get()->refreshKeybinds(false);
    ImGuiCocos::get().setup([] {
        CrystalClient::get()->addTheme();
    }).draw([] {
        CrystalClient::get()->drawGUI();
    });
    ImGuiCocos::get().toggle();
}

int strpos(const char *haystack, const char *needle, int nth) {
    const char *res = haystack;
    for(int i = 1; i <= nth; i++)
    {
        res = strstr(res, needle);
        if (!res)
            return -1;
        else if(i != nth)
            res++;
    }
    return res - haystack;
}

void CrystalClient::drawGUI() {
	ImGuiWindowFlags window_flags = 0;

    ImGui::Begin("Player", NULL, window_flags);
	CrystalClient::ImExtendedToggleable("Noclip", setVar<bool>("noclip"));
	if (ImGui::BeginPopupModal("Noclip", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Noclip Player 1", setVar<bool>("noclip_P1"));
		CrystalClient::ImToggleable("Noclip Player 2", setVar<bool>("noclip_P2"));
		CrystalClient::ImToggleable("Tint Screen on Death", setVar<bool>("noclip_tint"));
		ImGui::PushItemWidth(100);
		ImGui::InputFloat("##Noclip Accuracy Limit", setVar<float>("accuracy_limit_num"));
		ImGui::PopItemWidth();
		ImGui::SameLine();
		CrystalClient::ImToggleable("Noclip Accuracy Limit", setVar<bool>("accuracy_limit"));
		ImGui::PushItemWidth(100);
		ImGui::InputInt("##Noclip Deaths Limit", setVar<int>("death_limit_num"));
		ImGui::PopItemWidth();
		ImGui::SameLine();
		CrystalClient::ImToggleable("Noclip Deaths Limit", setVar<bool>("death_limit"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("No Death Effect", setVar<bool>("no_death_effect"));
	//CrystalClient::ImToggleable("Instant Death Respawn", setVar<bool>("instant_death_respawn"));
	CrystalClient::ImExtendedToggleable("Auto Reset", setVar<bool>("auto_reset"));
	if (ImGui::BeginPopupModal("Auto Reset", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Auto Reset Percentage", setVar<float>("auto_reset_num"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Respawn Bug Fix", setVar<bool>("respawn_fix"));
	CrystalClient::ImToggleable("Practice Bug Fix", setVar<bool>("practice_fix"));
	CrystalClient::ImExtendedToggleable("No Wave Pulse", setVar<bool>("no_wave_pulse"));
	if (ImGui::BeginPopupModal("No Wave Pulse", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Wave Trail Size", setVar<float>("wave_size"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Solid Wave Trail", setVar<bool>("solid_wave"));
	CrystalClient::ImToggleable("Invisible Player", setVar<bool>("invis_player"));
	ImGui::End();

	ImGui::Begin("Icon", NULL, window_flags);
	if (ImGui::BeginMenu("Player 1")) {
		CrystalClient::ImIconEffect(&profile.P1Color1, &profile.iconEffects[0], &profile.iconEffects[1], &profile.iconEffects[2], profile.StaticP1C1, profile.FadeP1C1E1, profile.FadeP1C1E2, "Player Color 1");
		CrystalClient::ImIconEffect(&profile.P1Color2, &profile.iconEffects[3], &profile.iconEffects[4], &profile.iconEffects[5], profile.StaticP1C2, profile.FadeP1C2E1, profile.FadeP1C2E2, "Player Color 2");
		CrystalClient::ImIconEffect(&profile.P1Glow, &profile.iconEffects[6], &profile.iconEffects[7], &profile.iconEffects[8], profile.StaticP1CG, profile.FadeP1GE1, profile.FadeP1GE2, "Icon Glow");
		CrystalClient::ImIconEffect(&profile.P1Regular, &profile.iconEffects[9], &profile.iconEffects[10], &profile.iconEffects[11], profile.StaticP1CR, profile.FadeP1RE1, profile.FadeP1RE2, "Regular Trail");
		CrystalClient::ImIconEffect(&profile.P1Wave, &profile.iconEffects[12], &profile.iconEffects[13], &profile.iconEffects[14], profile.StaticP1CW, profile.FadeP1WE1, profile.FadeP1WE2, "Wave Trail");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Player 2")) {
		CrystalClient::ImIconEffect(&profile.P2Color1, &profile.iconEffects[15], &profile.iconEffects[16], &profile.iconEffects[17], profile.StaticP2C1, profile.FadeP2C1E1, profile.FadeP2C1E2, "Player Color 1");
		CrystalClient::ImIconEffect(&profile.P2Color2, &profile.iconEffects[18], &profile.iconEffects[19], &profile.iconEffects[20], profile.StaticP2C2, profile.FadeP2C2E1, profile.FadeP2C2E2, "Player Color 2");
		CrystalClient::ImIconEffect(&profile.P2Glow, &profile.iconEffects[21], &profile.iconEffects[22], &profile.iconEffects[23], profile.StaticP2CG, profile.FadeP2GE1, profile.FadeP2GE2, "Icon Glow");
		CrystalClient::ImIconEffect(&profile.P2Regular, &profile.iconEffects[24], &profile.iconEffects[25], &profile.iconEffects[26], profile.StaticP2CR, profile.FadeP2RE1, profile.FadeP2RE2, "Regular Trail");
		CrystalClient::ImIconEffect(&profile.P2Wave, &profile.iconEffects[27], &profile.iconEffects[28], &profile.iconEffects[29], profile.StaticP2CW, profile.FadeP2WE1, profile.FadeP2WE2, "Wave Trail");
		ImGui::EndMenu();
	}
	CrystalClient::ImExtendedToggleable("Rainbow Icon", &Crystal::profile.rainbowIcon);
	if (ImGui::BeginPopupModal("Rainbow Icon", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Rainbow Player Color 1", &Crystal::profile.rainbowP1);
		CrystalClient::ImToggleable("Rainbow Player Color 2", &Crystal::profile.rainbowP2);
		CrystalClient::ImToggleable("Rainbow Wave Trail Player 1", &Crystal::profile.rainbowP1wave);
		CrystalClient::ImToggleable("Rainbow Wave Trail Player 2", &Crystal::profile.rainbowP2wave);
		CrystalClient::ImToggleable("Rainbow Glow Player 1", &Crystal::profile.rainbowGlowP1);
		CrystalClient::ImToggleable("Rainbow Glow Player 2", &Crystal::profile.rainbowGlowP2);
		ImGui::InputFloat("Rainbow Speed", &Crystal::profile.rainbowspeed);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Solid Glow Color", &Crystal::profile.solidGlow);
	ImGui::End();

	ImGui::Begin("Level", NULL, window_flags);
	CrystalClient::ImExtendedToggleable("Hitbox Viewer", setVar<bool>("hitboxes"));
	if (ImGui::BeginPopupModal("Hitbox Viewer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Show Hitboxes on Death", setVar<bool>("hitbox_on_death"));
		CrystalClient::ImToggleable("Show Hitbox Trail", setVar<bool>("hitbox_trail"));
		CrystalClient::ImToggleable("Show Hitboxes in Editor", setVar<bool>("hitboxes_in_editor"));
		CrystalClient::ImToggleable("Coin Tracker", setVar<bool>("coin_tracker"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("No Progress Bar", setVar<bool>("no_progress_bar"));
	CrystalClient::ImExtendedToggleable("Accurate Percentage", setVar<bool>("acc_percentage"));
	if (ImGui::BeginPopupModal("Accurate Percentage", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputInt("Percentage Decimal Points", setVar<int>("acc_percentage_decimals"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Hide Attempts Label", setVar<bool>("hide_attempts"));
	if (ImGui::BeginPopupModal("Hide Attempts Label", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide in Normal Mode", setVar<bool>("hide_attempts_normal"));
		CrystalClient::ImToggleable("Hide in Practice Mode", setVar<bool>("hide_attempts_practice"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Practice Music Hack", setVar<bool>("practice_music"));
	CrystalClient::ImToggleable("Hide Pause Menu", setVar<bool>("hide_pause"));
	CrystalClient::ImToggleable("Ignore ESC", setVar<bool>("ignore_esc"));
	CrystalClient::ImToggleable("Confirm Quit", setVar<bool>("confirm_quit"));
	CrystalClient::ImToggleable("Auto LDM", setVar<bool>("auto_ldm"));
	CrystalClient::ImToggleable("Auto Song Downloader", setVar<bool>("auto_song_download"));
	CrystalClient::ImToggleable("Flipped Dual Controls", setVar<bool>("flipped_dual"));
	CrystalClient::ImToggleable("Mirrored Dual Controls", setVar<bool>("mirrored_dual"));
	CrystalClient::ImToggleable("Smart StartPos", setVar<bool>("smart_startpos"));
	CrystalClient::ImToggleable("StartPos Switcher", setVar<bool>("startpos_switch"));
	CrystalClient::ImToggleable("Frame Stepper", setVar<bool>("framestep"));
	CrystalClient::ImToggleable("Load from Last Checkpoint", setVar<bool>("load_from_last_CP"));
	CrystalClient::ImToggleable("No Glow", setVar<bool>("no_glow"));
	CrystalClient::ImToggleable("No Mirror Effect", setVar<bool>("no_mirror"));
	CrystalClient::ImToggleable("Layout Mode", setVar<bool>("layout_mode"));
	CrystalClient::ImExtendedToggleable("AutoClicker", setVar<bool>("autoclicker"));
	if (ImGui::BeginPopupModal("AutoClicker", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Autoclick Player 1", setVar<bool>("AC_player1"));
		CrystalClient::ImToggleable("Autoclick Player 2", setVar<bool>("AC_player2"));
		ImGui::InputInt("Push on Frame", setVar<int>("AC_pushFrame"));
		ImGui::InputInt("Release on Frame", setVar<int>("AC_releaseFrame"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Display", NULL, window_flags);
	CrystalClient::ImToggleable("Testmode Label", setVar<bool>("testmode_label"));
	ImGui::InputFloat("Display Scale", setVar<float>("display_scale"));
	ImGui::InputFloat("Display Opacity", setVar<float>("display_opacity"));
	ImGui::InputFloat("Display Spacing", setVar<float>("display_space"));
	CrystalClient::ImExtendedToggleable("Cheat Indicator", setVar<bool>("cheat_indicator"));
	if (ImGui::BeginPopupModal("Cheat Indicator", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-0"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Custom Message", setVar<bool>("custom_message"));
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-1"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("CPS display", setVar<bool>("cps_display"));
	if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		//CrystalClient::ImToggleable("Green Pulse On Click", &Crystal::profile.tclicks);
		ImGui::Combo("Position", setVar<int>("label_pos-2"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", setVar<bool>("fps_display"));
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-3"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Last Death", setVar<bool>("last_death"));
	if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-4"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Attempts", setVar<bool>("attempts"));
	if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Attempts", setVar<bool>("total_attempts"));
		ImGui::Combo("Position", setVar<int>("label_pos-5"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", setVar<bool>("jumps"));
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Jumps", setVar<bool>("total_jumps"));
		ImGui::Combo("Position", setVar<int>("label_pos-6"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Run From", setVar<bool>("run_from"));
	if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-7"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Best Run", setVar<bool>("best_run"));
	if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-8"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", setVar<bool>("noclip_accuracy"));
	if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_accuracy"));
		ImGui::Combo("Position", setVar<int>("label_pos-9"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Deaths", setVar<bool>("noclip_deaths"));
	if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_death"));
		ImGui::Combo("Position", setVar<int>("label_pos-10"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Level Name and ID", setVar<bool>("level_info"));
	if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide ID", setVar<bool>("hide_ID"));
		CrystalClient::ImToggleable("Show Author", setVar<bool>("level_info_author"));
		ImGui::Combo("Position", setVar<int>("label_pos-11"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Macro Status", setVar<bool>("macro_status"));
	if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-12"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clock", setVar<bool>("clock"));
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-13"), profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Customization", NULL, window_flags);
    ImGui::ColorEdit4("Accent Color", profile.LightColour, ImGuiColorEditFlags_NoInputs);
    ImGui::ColorEdit4("Base Color", profile.BGColour, ImGuiColorEditFlags_NoInputs);
	CrystalClient::ImExtendedToggleable("Different Titlebar Color", &profile.diffTitleBar);
	if (ImGui::BeginPopupModal("Different Titlebar Color", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::ColorEdit4("Titlebar Color", profile.TitleColour, ImGuiColorEditFlags_NoInputs);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Bypasses", NULL, window_flags);
	CrystalClient::ImToggleable("Anticheat Bypass", setVar<bool>("anticheat"));
	CrystalClient::ImToggleable("Unlock All", setVar<bool>("unlock_all"));
	CrystalClient::ImToggleable("Scale Hack", setVar<bool>("scalehack"));
	CrystalClient::ImToggleable("Object Limit Bypass", setVar<bool>("obj_limit"));
	CrystalClient::ImToggleable("Custom Object Object Limit Bypass", setVar<bool>("custom_obj_limit"));
	CrystalClient::ImToggleable("Verify Bypass", setVar<bool>("verify"));
	CrystalClient::ImToggleable("Copy Bypass", setVar<bool>("copy_hack"));
	CrystalClient::ImToggleable("Editor Zoom Bypass", setVar<bool>("editor_zoom"));
	CrystalClient::ImToggleable("Level Edit Bypass", setVar<bool>("level_edit"));
	CrystalClient::ImToggleable("Load Failed Bypass", setVar<bool>("load_failed"));
    ImGui::End();
    ImGui::Begin("Global", NULL, window_flags);
	ImGui::PushItemWidth(100);
    ImGui::InputFloat("##FPS Bypass", setVar<float>("FPS"));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("FPS Bypass", setVar<bool>("FPS_bypass"));
	ImGui::InputFloat("##Unfocused FPS", setVar<float>("FPS_unfocused"));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("Unfocused FPS", setVar<bool>("Unfocused_FPS"));
    ImGui::InputFloat("Speedhack", setVar<float>("speed"));
	if (getVar<float>("speed") != 0) CCDirector::sharedDirector()->getScheduler()->setTimeScale(getVar<float>("speed"));
	CrystalClient::ImExtendedToggleable("Safe Mode", setVar<bool>("safe_mode"));
	if (ImGui::BeginPopupModal("Safe Mode", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Auto Safe Mode", setVar<bool>("auto_safe_mode"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Lock Cursor", setVar<bool>("lock_cursor"));
	CrystalClient::ImToggleable("No Pause on Unfocus", setVar<bool>("no_pause_unfocus"));
	CrystalClient::ImToggleable("Mute on Unfocus", setVar<bool>("mute_unfocus"));
	CrystalClient::ImToggleable("Transparent BG", setVar<bool>("transparent_BG"));
	CrystalClient::ImToggleable("Transparent Lists", setVar<bool>("transparent_lists"));
	CrystalClient::ImToggleable("Better BG", setVar<bool>("better_BG"));
	CrystalClient::ImToggleable("Demon List Button", setVar<bool>("demonlist_button"));
	CrystalClient::ImToggleable("Challenge List Button", setVar<bool>("challengelist_button"));
	CrystalClient::ImToggleable("Copy SongID", setVar<bool>("copy_songID"));
	CrystalClient::ImToggleable("Copy LevelID Everywhere", setVar<bool>("copy_levelID"));
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]", NULL, window_flags);
    CrystalClient::ImToggleable("Record", setVar<bool>("AT_record"));
	ImGui::SameLine();
    CrystalClient::ImToggleable("Replay", setVar<bool>("AT_replay"));
	CrystalClient::ImToggleable("ClickBot", setVar<bool>("clickbot"));
	ImGui::SameLine();
	CrystalClient::ImToggleable("Delta Lock", setVar<bool>("delta_lock"));
	ImGui::InputFloat("ClickBot Volume", setVar<float>("clickbot_volume"));
    //ImGui::Combo("Macro Type", (int*)&currentMacro.type, macroTypes, IM_ARRAYSIZE(macroTypes));
    ImGui::InputTextWithHint("Macro Name", "Macro Name", profile.macroname, IM_ARRAYSIZE(profile.macroname));
    if (ImGui::Button("Save Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + (std::string)profile.macroname + ".thyst";
		currentMacro.saveToFile(filename.c_str());
	}
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + (std::string)profile.macroname + ".thyst";
		currentMacro = AmethystMacro::createFromFile(filename.c_str(), false);
	}
    ImGui::SameLine();
    if (ImGui::Button("Clear Macro")) {
        currentMacro.clearData();
    }
    ImGui::End();
    ImGui::Begin("Shortcuts", NULL, window_flags);
    if (ImGui::Button("Open Songs Folder")) {
        system("open ~/Library/Caches");
    }
    if (ImGui::Button("Open Crystal Folder")) {
        //system(conf.c_str());
    }
    if (ImGui::Button("Open Resources Folder")) {
        system("open Resources");
    }
    if (ImGui::Button("Open GD Settings")) {
        OptionsLayer::addToCurrentScene(false);
    }
    ImGui::Separator();
    ImGui::Combo("Keybind", &Shortcuts::get()->currentKey, Shortcuts::get()->keybindings, IM_ARRAYSIZE(Shortcuts::get()->keybindings));
    ImGui::Combo("Mod to Switch", &Shortcuts::get()->currentMod, Shortcuts::get()->modbindings, IM_ARRAYSIZE(Shortcuts::get()->modbindings));
    if (ImGui::Button("Add Keybind")) {
        Shortcuts::get()->keybinds.push_back({Shortcuts::get()->currentKey, Shortcuts::get()->currentMod});
    }
	for (size_t i = 0; i < Shortcuts::get()->keybinds.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text("%s", Shortcuts::get()->modbindings[Shortcuts::get()->keybinds[i].activeMod]);
		ImGui::SameLine();
		ImGui::Text("%s", Shortcuts::get()->keybindings[Shortcuts::get()->keybinds[i].activeKey]);
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			Shortcuts::get()->keybinds.erase(Shortcuts::get()->keybinds.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
	ImGui::Begin("Variable Changer", NULL, window_flags);
    ImGui::Combo("Variable", &Shortcuts::get()->currentVar, Shortcuts::get()->playerVars, IM_ARRAYSIZE(Shortcuts::get()->playerVars));
	ImGui::InputFloat("Value", &Shortcuts::get()->currentValue);
    if (ImGui::Button("Add Change")) {
        Shortcuts::get()->variables.push_back({Shortcuts::get()->currentVar, Shortcuts::get()->currentValue});
    }
	for (size_t i = 0; i < Shortcuts::get()->variables.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text("%s", Shortcuts::get()->playerVars[Shortcuts::get()->variables[i].activeVar]);
		ImGui::SameLine();
		ImGui::Text("%s", std::to_string(Shortcuts::get()->variables[i].activeValue).c_str());
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			Shortcuts::get()->variables.erase(Shortcuts::get()->variables.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
	ImGui::Begin("Internal Renderer", NULL, window_flags);
	CrystalClient::ImToggleable("Render Recording", &profile.renderer);
	CrystalClient::ImToggleable("Include Sound", &profile.includeAudio);
	CrystalClient::ImToggleable("Include Displays", &profile.includeDisplays);
	ImGui::InputTextWithHint("Video Name", "Video Name", profile.rendername, IM_ARRAYSIZE(profile.rendername));
	ImGui::Combo("Render Quality", &currentPreset, renderPresets, IM_ARRAYSIZE(renderPresets));
	record.init_quality();
	ImGui::InputInt("Width", &profile.targetWidth);
	ImGui::InputInt("Height", &profile.targetHeight);
	ImGui::InputInt("FPS", &profile.targetFPS);
	ImGui::End();
}

void CrystalClient::addTheme() {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colours = ImGui::GetStyle().Colors;

	//io.IniFilename = (Mod::get()->getSaveDir() / "imgui.ini").c_str();
	setupFonts((Mod::get()->getResourcesDir() / "Lexend.ttf").c_str(), 14.0f);

    if (profile.RGBAccent) {
        profile.LightColour[0] = profile.LightColour[0] + profile.rDir;
        profile.LightColour[1] = profile.LightColour[1] + profile.gDir;
        profile.LightColour[2] = profile.LightColour[2] + profile.bDir;

        if (profile.LightColour[0] >= 1 || profile.LightColour[0] <= 0) { profile.rDir = profile.rDir * -1; }
        if (profile.LightColour[1] >= 1 || profile.LightColour[1] <= 0) { profile.gDir = profile.gDir * -1; }
        if (profile.LightColour[2] >= 1 || profile.LightColour[2] <= 0) { profile.bDir = profile.bDir * -1; }
    }

    profile.DarkColour[0] = (profile.LightColour[0] * 0.5f);
    profile.DarkColour[1] = (profile.LightColour[1] * 0.5f);
    profile.DarkColour[2] = (profile.LightColour[2] * 0.5f);
    profile.DarkColour[3] = profile.LightColour[3];
    profile.VeryLightColour[0] = (profile.LightColour[0] * 1.5f);
    profile.VeryLightColour[1] = (profile.LightColour[1] * 1.5f);
    profile.VeryLightColour[2] = (profile.LightColour[2] * 1.5f);
    profile.VeryLightColour[3] = profile.LightColour[3];

    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    style->Alpha = 1.f;
    style->WindowRounding = profile.borderRounding;
    style->FrameRounding = 4.f;
    style->ScrollbarSize = profile.scrollbarSize;
    style->ScrollbarRounding = profile.scrollbarRounding;
    style->PopupRounding = profile.borderRounding;
    style->WindowBorderSize = 1.5f;
    colours[ImGuiCol_TitleBg] = CrystalProfile::RGBAtoIV4(profile.diffTitleBar ? profile.TitleColour : profile.BGColour);
    colours[ImGuiCol_TitleBgActive] = CrystalProfile::RGBAtoIV4(profile.diffTitleBar ? profile.TitleColour : profile.BGColour);
    colours[ImGuiCol_WindowBg] = CrystalProfile::RGBAtoIV4(profile.BGColour);
    colours[ImGuiCol_Border] = CrystalProfile::RGBAtoIV4(profile.borders ? profile.LightColour : profile.BGColour);
    colours[ImGuiCol_FrameBg] = CrystalProfile::RGBAtoIV4(profile.DarkColour);
    colours[ImGuiCol_FrameBgHovered] = CrystalProfile::RGBAtoIV4(profile.DarkColour);
    colours[ImGuiCol_FrameBgActive] = CrystalProfile::RGBAtoIV4(profile.LightColour);
    colours[ImGuiCol_PlotHistogram] = CrystalProfile::RGBAtoIV4(profile.LightColour);
    colours[ImGuiCol_Button] = CrystalProfile::RGBAtoIV4(profile.LightColour);
    colours[ImGuiCol_ButtonHovered] = CrystalProfile::RGBAtoIV4(profile.VeryLightColour);
    colours[ImGuiCol_Header] = CrystalProfile::RGBAtoIV4(profile.DarkColour);
    colours[ImGuiCol_HeaderHovered] = CrystalProfile::RGBAtoIV4(profile.LightColour);
    colours[ImGuiCol_HeaderActive] = CrystalProfile::RGBAtoIV4(profile.VeryLightColour);
    colours[ImGuiCol_SliderGrab] = CrystalProfile::RGBAtoIV4(profile.LightColour);
    colours[ImGuiCol_SliderGrabActive] = CrystalProfile::RGBAtoIV4(profile.VeryLightColour);
    colours[ImGuiCol_CheckMark] = CrystalProfile::RGBAtoIV4(profile.VeryLightColour);
}

$execute {
	CrystalClient::get()->initPatches();

	new EventListener(+[](const char* pluginName) {
        CrystalClient::get()->plugins.push_back(pluginName);
        return ListenerResult::Propagate;
    }, geode::DispatchFilter<const char*>("ninxout.crystalclient/addPluginName"));

    new EventListener(+[](bool* theAction) {
        CrystalClient::get()->pluginBools.push_back(theAction);
        return ListenerResult::Propagate;
    }, geode::DispatchFilter<bool*>("ninxout.crystalclient/addPluginBool"));
}

class $modify(MenuLayer) {
	bool init() {
		if (!ghc::filesystem::exists(framesFol)) {
			ghc::filesystem::create_directories(framesFol);
		}
		if (!ghc::filesystem::exists(macros)) {
			ghc::filesystem::create_directories(macros);
		}
		if (!ghc::filesystem::exists(cb)) {
			ghc::filesystem::create_directory(cb);
		}
		if (!ghc::filesystem::exists(conf)) {
			ghc::filesystem::create_directory(conf);
		}
		if (!ghc::filesystem::exists(betterBG)) {
			ghc::filesystem::create_directory(betterBG);
		}

		std::string renderInit = "chmod +x " + std::string(geode::Mod::get()->getConfigDir() / "Amethyst" / "Renderer" / "ffmpeg");
		system(renderInit.c_str());
		std::string pathInit = "export PATH='" + std::string(Mod::get()->getConfigDir() / "Amethyst" / "Renderer") + ":${PATH}'";
		system(pathInit.c_str());

		MenuLayer::init();

		std::fstream input(geode::Mod::get()->getConfigDir().append("Config").append("GH_config.json"));

		if (!input) {
			CrystalClient::get()->firstLoad(this);
		} 

		if (!isTiemOn) {
			tiem = std::chrono::high_resolution_clock::now();
			isTiemOn = true;
		}

		return true;
	}
};

class $modify(Main, PlayLayer) {
    void update(float f4) {
		if (profile.rainbowIcon) {
			if (m_player1) {
				if (Crystal::profile.rainbowP1) m_player1->setColor(col);
				if (Crystal::profile.rainbowP2) m_player1->setSecondColor(colInverse);
				if (profile.rainbowGlowP1) {
					m_player1->m_iconGlow->setColor(col);
					m_player1->m_vehicleGlow->setChildColor(col);
					m_player1->m_iconGlow->setBlendFunc(m_player1->m_iconGlow->getBlendFunc());
					m_player1->m_vehicleGlow->setBlendFunc(m_player1->m_vehicleGlow->getBlendFunc());
				}
				if (m_player1->m_waveTrail)
					if (Crystal::profile.rainbowP1wave) m_player1->m_waveTrail->setColor(col);
			}

			if (m_player2) {
				if (Crystal::profile.rainbowP2) m_player2->setColor(colInverse);
				if (Crystal::profile.rainbowP1) m_player2->setSecondColor(col);
				if (profile.rainbowGlowP2) {
					m_player2->m_iconGlow->setColor(colInverse);
					m_player2->m_vehicleGlow->setChildColor(colInverse);
				}
				if (m_player2->m_waveTrail)
					if (Crystal::profile.rainbowP2wave) m_player2->m_waveTrail->setColor(colInverse);
			}
		}

		percent = (m_player1->getPositionX() / m_levelLength) * 100;

		PlayLayer::update(f4);
		if (profile.renderer) record.handle_recording(this, f4);
	}

    void onQuit() {
		//if (profile.trajectory) drawer->onQuitTrajectory();
		std::string renderprocess;
		//FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		std::string basicNAME = (std::string)renderer + "/new.mp4";
		if (profile.renderer) {
			record.stop();
		}
		PlayLayer::onQuit();
	}

	bool init(GJGameLevel* gl) {
		//leftDisplay = 0;
		timee = 0.0f;
        

		ss = 0;
		clickscount = 0;
		click_count = 0;
		renderTime = 0;

		if (!ghc::filesystem::exists(framesFol)) {
			ghc::filesystem::create_directories(framesFol);
		} else {
			ghc::filesystem::remove_all(framesFol);
			ghc::filesystem::create_directory(framesFol);
		}

		PlayLayer::init(gl);

		if (profile.renderer) {
			std::string filePATH = std::string(renderer) + "/" + (const char*)profile.rendername + ".mp4";
			std::string tempPATH = std::string(renderer) + "/temp.mp4";
			record.start(filePATH, tempPATH);
		}

		currentFrame = 0;
		return true;
	}
};