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

using namespace geode::prelude;
using namespace Crystal;
using namespace AmethystReplay;
using namespace Icon;

$on_mod(Loaded) {
    profile = Crystal::loadMods();
	loadConfigFromFile();
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
	if (profile.invisBG) window_flags |= ImGuiWindowFlags_NoBackground;
	if (profile.titlebar) window_flags |= ImGuiWindowFlags_NoTitleBar;

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
		ImGui::Combo("Position", (int *)&profile.displayPositions[0], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Custom Message", setVar<bool>("custom_message"));
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[1], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("CPS display", setVar<bool>("cps_display"));
	if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		//CrystalClient::ImToggleable("Green Pulse On Click", &Crystal::profile.tclicks);
		ImGui::Combo("Position", (int *)&profile.displayPositions[2], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", setVar<bool>("fps_display"));
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[3], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Last Death", setVar<bool>("last_death"));
	if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[4], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Attempts", setVar<bool>("attempts"));
	if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Attempts", setVar<bool>("total_attempts"));
		ImGui::Combo("Position", (int *)&profile.displayPositions[5], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", setVar<bool>("jumps"));
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Jumps", setVar<bool>("total_jumps"));
		ImGui::Combo("Position", (int *)&profile.displayPositions[6], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Run From", setVar<bool>("run_from"));
	if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[7], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Best Run", setVar<bool>("best_run"));
	if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[8], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", setVar<bool>("noclip_accuracy"));
	if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_accuracy"));
		ImGui::Combo("Position", (int *)&profile.displayPositions[9], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Deaths", setVar<bool>("noclip_deaths"));
	if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_death"));
		ImGui::Combo("Position", (int *)&profile.displayPositions[10], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Level Name and ID", setVar<bool>("level_info"));
	if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide ID", setVar<bool>("hide_ID"));
		CrystalClient::ImToggleable("Show Author", setVar<bool>("level_info_author"));
		ImGui::Combo("Position", (int *)&profile.displayPositions[11], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Macro Status", setVar<bool>("macro_status"));
	if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[12], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clock", setVar<bool>("clock"));
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[13], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Customization", NULL, window_flags);
    ImGui::ColorEdit4("Accent Color", profile.LightColour, ImGuiColorEditFlags_NoInputs);
    ImGui::ColorEdit4("Base Color", profile.BGColour, ImGuiColorEditFlags_NoInputs);
    CrystalClient::ImToggleable("RGB Accent Color", &profile.RGBAccent);
    CrystalClient::ImToggleable("Borders", &profile.borders);
    CrystalClient::ImToggleable("Rounded Windows", &profile.rounded);
	CrystalClient::ImToggleable("No Title Bar", &profile.titlebar);
	CrystalClient::ImToggleable("Invisible BG", &profile.invisBG);
	CrystalClient::ImExtendedToggleable("Different Titlebar Color", &profile.diffTitleBar);
	if (ImGui::BeginPopupModal("Different Titlebar Color", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::ColorEdit4("Titlebar Color", profile.TitleColour, ImGuiColorEditFlags_NoInputs);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::InputFloat("Border Rounding", &profile.borderRounding);
	ImGui::InputFloat("Scrollbar Size", &profile.scrollbarSize);
	ImGui::InputFloat("Scrollbar Rounding", &profile.scrollbarRounding);
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
    ImGui::InputFloat("##FPS Bypass", &profile.FPS);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("FPS Bypass", &profile.FPSbypass);
	ImGui::PushItemWidth(100);
	ImGui::InputFloat("##TPS Bypass", &profile.TPS);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("TPS Bypass", &profile.TPSbypass);
    ImGui::InputFloat("Speedhack", setVar<float>("speed"));
    if (getVar<bool>("speed") != 0) CCDirector::sharedDirector()->getScheduler()->setTimeScale(getVar<float>("speed"));
	CrystalClient::ImExtendedToggleable("Safe Mode", setVar<bool>("safe_mode"));
	if (ImGui::BeginPopupModal("Safe Mode", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Auto Safe Mode", setVar<bool>("auto_safe_mode"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Lock Cursor", setVar<bool>("lock_cursor"));
	CrystalClient::ImToggleable("Transparent BG", setVar<bool>("transparent_BG"));
	CrystalClient::ImToggleable("Transparent Lists", setVar<bool>("transparent_lists"));
	//CrystalClient::ImToggleable("Better BG", &profile.betterbg);
	CrystalClient::ImToggleable("Demon List Button", setVar<bool>("demonlist_button"));
	CrystalClient::ImToggleable("Challenge List Button", setVar<bool>("challengelist_button"));
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

		if (Crystal::profile.betterbg) {
			image = geode::Mod::get()->getConfigDir().append("BetterBG").append("background.jpg");

			if (ghc::filesystem::exists(image)) {
				auto ml = GameManager::sharedState()->m_menuLayer;
				auto winSize = CCDirector::sharedDirector()->getWinSize();
				auto sprite = CCSprite::create(image.c_str());

				sprite->setScaleY(winSize.height / sprite->getContentSize().height);
				sprite->setScaleX(winSize.width / sprite->getContentSize().width);
				sprite->setPositionX(winSize.width / 2);
				sprite->setPositionY(winSize.height / 2);

				auto node = ((CCNode*)ml->getChildren()->objectAtIndex(0));

				node->setZOrder(-2);
				ml->addChild(sprite, -1);
			} else {
				CrystalClient::get()->noImage(this);
			}
		}

		return true;
	}
};

class $modify(CCScheduler) {
	void update(float f3) {
		if (PlayLayer::get() && (rendering)) {
			auto dir = CCDirector::sharedDirector();

			float spf = (float)dir->getAnimationInterval();
			float tScale = dir->getScheduler()->getTimeScale();

			f3 = spf * tScale;
		}

		if (PlayLayer::get() && (profile.TPSbypass || profile.FPSbypass || profile.deltaLock || profile.replay || profile.record || profile.renderer)) {
			auto dir = CCDirector::sharedDirector();

			//CGSSetDebugOptions(327680);

			float spf = (float)dir->getAnimationInterval() * (60 / profile.TPS);
			auto nspeedhack = CCDirector::sharedDirector()->getScheduler()->getTimeScale();

			const float newdt = 1.f / profile.TPS / nspeedhack;
			const float otherdt = 1.f / profile.FPS / nspeedhack;
			float totaldt = 1.f / (profile.FPS * (profile.TPS / 60)) / nspeedhack;

			if (profile.renderer) renderTime += totaldt;
			if (profile.deltaLock || profile.renderer) return CCScheduler::update(totaldt);

			g_disable_render = true;

			if (profile.FPSbypass) cocos2d::CCApplication::sharedApplication()->setAnimationInterval(otherdt);
			else cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.f / 60.f);

			const int totaltimes = std::min(static_cast<int>((f3 + t_left_over) / totaldt), 100); // limit it to 100x just in case
			for (int i = 0; i < totaltimes; ++i) {
				if (i == totaltimes - 1)
					g_disable_render = false;
				CCScheduler::update(totaldt);
				auto io = ImGui::GetIO();
				if (io.DeltaTime <= 0.0f) io.DeltaTime = 0.00001f;
			}
			t_left_over += f3 - totaldt * totaltimes;
		} else {
			CCScheduler::update(f3);
		}
	}
};

class $modify(CheckpointObject) {
	static CheckpointObject* create() {
		auto cpo = CheckpointObject::create();

		if (Crystal::profile.checkpointswitch) { // bro ninx how you forgot to add the if (it crashed without it lmao)
			g_checkpoints.push_back({cpo, static_cast<CCNode*>(cpo)->getPosition()});
			g_checkpointIndex += 1;
			auto label = std::to_string(g_checkpointIndex + 1) + "/" + std::to_string(g_checkpoints.size());
			//g_startPosText->setString(label.c_str());
		}

		return cpo;
	}
};

class $modify(Main, PlayLayer) {
	void loadFromCheckpoint(CheckpointObject* cpo) {
		if (Crystal::profile.checkpointswitch) {
			if (cpo && g_checkpointIndex != -1) {
				cpo = g_checkpoints[g_checkpointIndex].first; 
			} 
		}
		PlayLayer::loadFromCheckpoint(cpo);
	}

    void updateVisibility() {
		if (!g_disable_render) PlayLayer::updateVisibility();
	}

    void update(float f4) {
		Icon::update();

	if (cycle >= 1.0) cycle = 0;
    Icon::cycle += 0.1;
    auto pl = PlayLayer::get();
    if (profile.P1Color1) {
        if (Crystal::profile.iconEffects[0]) {
            pl->m_player1->setColor(getEffectColor(Static, P1Color1));
        }
        if (Crystal::profile.iconEffects[1]) {
            pl->m_player1->setColor(getEffectColor(Fade, P1Color1));
        }
        if (Crystal::profile.iconEffects[2]) {
            pl->m_player1->setColor(getEffectColor(Rainbow, P1Color1));
        }
    }
    if (profile.P1Color2) {
        if (Crystal::profile.iconEffects[3]) {
            pl->m_player1->setSecondColor(getEffectColor(Static, P1Color2));
        }
        if (Crystal::profile.iconEffects[4]) {
            pl->m_player1->setSecondColor(getEffectColor(Fade, P1Color2));
        }
        if (Crystal::profile.iconEffects[5]) {
            pl->m_player1->setSecondColor(getEffectColor(Rainbow, P1Color2));
        }
    }
    if (profile.P1Glow) {
        if (Crystal::profile.iconEffects[6]) {
            pl->m_player1->setGlowColor(getEffectColor(Static, P1Glow));
        }
        if (Crystal::profile.iconEffects[7]) {
            pl->m_player1->setGlowColor(getEffectColor(Fade, P1Glow));
        }
        if (Crystal::profile.iconEffects[8]) {
            pl->m_player1->setGlowColor(getEffectColor(Rainbow, P1Glow));
        }
    }
    if (profile.P1Regular) {
        if (Crystal::profile.iconEffects[9]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Static, P1RegularTrail));
        }
        if (Crystal::profile.iconEffects[10]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Fade, P1RegularTrail));
        }
        if (Crystal::profile.iconEffects[11]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Rainbow, P1RegularTrail));
        }
    }
    if (profile.P1Wave) {
        if (Crystal::profile.iconEffects[12]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Static, P1WaveTrail));
        }
        if (Crystal::profile.iconEffects[13]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Fade, P1WaveTrail));
        }
        if (Crystal::profile.iconEffects[14]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Rainbow, P1WaveTrail));
        }
    }
    if (profile.P2Color1) {
        if (Crystal::profile.iconEffects[15]) {
            pl->m_player2->setColor(getEffectColor(Static, P2Color1));
        }
        if (Crystal::profile.iconEffects[16]) {
            pl->m_player2->setColor(getEffectColor(Fade, P2Color1));
        }
        if (Crystal::profile.iconEffects[17]) {
            pl->m_player2->setColor(getEffectColor(Rainbow, P2Color1));
        }
    }
    if (profile.P2Color2) {
        if (Crystal::profile.iconEffects[18]) {
            pl->m_player2->setSecondColor(getEffectColor(Static, P2Color2));
        }
        if (Crystal::profile.iconEffects[19]) {
            pl->m_player2->setSecondColor(getEffectColor(Fade, P2Color2));
        }
        if (Crystal::profile.iconEffects[20]) {
            pl->m_player2->setSecondColor(getEffectColor(Rainbow, P2Color2));
        }
    }
    if (profile.P2Glow) {
        if (Crystal::profile.iconEffects[21]) {
            pl->m_player2->setGlowColor(getEffectColor(Static, P2Glow));
        }
        if (Crystal::profile.iconEffects[22]) {
            pl->m_player2->setGlowColor(getEffectColor(Fade, P2Glow));
        }
        if (Crystal::profile.iconEffects[23]) {
            pl->m_player2->setGlowColor(getEffectColor(Rainbow, P2Glow));
        }
    }
    if (profile.P2Regular) {
        if (Crystal::profile.iconEffects[24]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Static, P2RegularTrail));
        }
        if (Crystal::profile.iconEffects[25]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Fade, P2RegularTrail));
        }
        if (Crystal::profile.iconEffects[26]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Rainbow, P2RegularTrail));
        }
    }
    if (profile.P2Wave) {
        if (Crystal::profile.iconEffects[27]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Static, P2WaveTrail));
        }
        if (Crystal::profile.iconEffects[28]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Fade, P2WaveTrail));
        }
        if (Crystal::profile.iconEffects[29]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Rainbow, P2WaveTrail));
        }
    }


		fixa += f4;
		timee += f4;

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

		//if (profile.trajectory) drawer->createPlayersForTrajectory();

		currentFrame = 0;
		return true;
	}
};

template<>
struct json::Serialize<CrystalProfile> {
    static json::Value to_json(CrystalProfile const& value) {
        auto ret = json::Object();
		std::string ver = std::to_string(Mod::get()->getVersion().getMajor()) + "." + std::to_string(Mod::get()->getVersion().getMinor()) + "." + std::to_string(Mod::get()->getVersion().getPatch());
		ret["CrystalVer"] = ver;
        ret["noclip"] = Crystal::profile.noclip;
        ret["noclipP1"] = Crystal::profile.noclipP1;
        ret["noclipP2"] = Crystal::profile.noclipP2;
		ret["resetOnAccuracy"] = Crystal::profile.resetOnAccuracy;
		ret["resetOnDeath"] = Crystal::profile.resetOnDeath;
		ret["resetAcc"] = Crystal::profile.resetAcc;
		ret["resetDeath"] = Crystal::profile.resetDeath;
        ret["tintOnDeath"] = Crystal::profile.tintOnDeath;
        ret["deathEffect"] = Crystal::profile.deathEffect;
        ret["instantdeath"] = Crystal::profile.instantdeath;
        ret["autoreset"] = Crystal::profile.autoreset;
        ret["autoresetnum"] = Crystal::profile.autoresetnum;
        ret["respawnfix"] = Crystal::profile.respawnfix;
        ret["practiceorbfix"] = Crystal::profile.practiceorbfix;
        ret["nopulse"] = Crystal::profile.nopulse;
        ret["trailsize"] = Crystal::profile.trailsize;
        ret["solidwave"] = Crystal::profile.solidwave;
        ret["invisibleplayer"] = Crystal::profile.invisibleplayer;
        ret["customPlayerColor"] = Crystal::profile.customPlayerColor;
        ret["customWaveColor"] = Crystal::profile.customWaveColor;
        ret["rainbowIcon"] = Crystal::profile.rainbowIcon;
        ret["rainbowP1"] = Crystal::profile.rainbowP1;
        ret["rainbowP2"] = Crystal::profile.rainbowP2;
        ret["rainbowP1wave"] = Crystal::profile.rainbowP1wave;
        ret["rainbowP2wave"] = Crystal::profile.rainbowP2wave;
        ret["rainbowspeed"] = Crystal::profile.rainbowspeed;
        ret["samedual"] = Crystal::profile.samedual;
        ret["hitboxes"] = Crystal::profile.hitboxes;
        ret["onDeath"] = Crystal::profile.onDeath;
        ret["drawTrail"] = Crystal::profile.drawTrail;
        ret["inEditor"] = Crystal::profile.inEditor;
        ret["particles"] = Crystal::profile.particles;
        ret["progressBar"] = Crystal::profile.progressBar;
        ret["accpercentage"] = Crystal::profile.accpercentage;
        ret["hideatts"] = Crystal::profile.hideatts;
        ret["hidenormalatts"] = Crystal::profile.hidenormalatts;
        ret["hidepracticeatts"] = Crystal::profile.hidepracticeatts;
        ret["pracmusic"] = Crystal::profile.pracmusic;
        ret["ignoreESC"] = Crystal::profile.ignoreESC;
        ret["confirmQuit"] = Crystal::profile.confirmQuit;
		ret["hidepause"] = Crystal::profile.hidepause;
        ret["autoldm"] = Crystal::profile.autoldm;
		ret["autoSong"] = Crystal::profile.autoSong;
        ret["flippedcontrol"] = Crystal::profile.flippedcontrol;
        ret["mirrorcontrol"] = Crystal::profile.mirrorcontrol;
        ret["startpos"] = Crystal::profile.startpos;
        ret["checkpointswitch"] = Crystal::profile.checkpointswitch;
        ret["framestep"] = Crystal::profile.framestep;
        ret["lastCheckpoint"] = Crystal::profile.lastCheckpoint;
        ret["noglow"] = Crystal::profile.noglow;
        ret["nospike"] = Crystal::profile.nospike;
        ret["mirror"] = Crystal::profile.mirror;
        ret["layout"] = Crystal::profile.layout;
        ret["autoclick"] = Crystal::profile.autoclick;
        ret["ACpushframe"] = Crystal::profile.ACpushframe;
        ret["ACrelframe"] = Crystal::profile.ACrelframe;
		ret["testmode"] = Crystal::profile.testmode;
		ret["customMessage"] = Crystal::profile.customMessage;
		ret["fps"] = Crystal::profile.fps;
		ret["cps"] = Crystal::profile.cps;
		ret["jumps"] = Crystal::profile.jumps;
		ret["cheatIndicate"] = Crystal::profile.cheatIndicate;
		ret["attempts"] = Crystal::profile.attempts;
		ret["bestRun"] = Crystal::profile.bestRun;
		ret["runFrom"] = Crystal::profile.runFrom;
		ret["noclipAcc"] = Crystal::profile.noclipAcc;
		ret["noclipDeath"] = Crystal::profile.noclipDeath;
		ret["totalAtt"] = Crystal::profile.totalAtt;
		ret["lvlData"] = Crystal::profile.lvlData;
		ret["macroStatus"] = Crystal::profile.macroStatus;
		ret["clock"] = Crystal::profile.clock;
		ret["message"] = Crystal::profile.message;
		ret["tclicks"] = Crystal::profile.tclicks;
		ret["sclicks"] = Crystal::profile.sclicks;
		ret["oclicks"] = Crystal::profile.oclicks;
		ret["rclicks"] = Crystal::profile.rclicks;
		ret["ajumps"] = Crystal::profile.ajumps;
		ret["tjumps"] = Crystal::profile.tjumps;
		ret["tattoo"] = Crystal::profile.tattoo;
		ret["redDying"] = Crystal::profile.redDying;
		ret["redDeath"] = Crystal::profile.redDeath;
		ret["hideID"] = Crystal::profile.hideID;
		ret["author"] = Crystal::profile.author;
		ret["iat"] = Crystal::profile.iat;
		ret["ilt"] = Crystal::profile.ilt;
		ret["igt"] = Crystal::profile.igt;
		ret["ipm"] = Crystal::profile.ipm;
		ret["safeMode"] = Crystal::profile.safeMode;
		ret["autoSafeMode"] = Crystal::profile.autoSafeMode;
		ret["BGColour-Red"] = Crystal::profile.BGColour[0];
        ret["BGColour-Green"] = Crystal::profile.BGColour[1];
        ret["BGColour-Blue"] = Crystal::profile.BGColour[2];
        ret["BGColour-Alpha"] = Crystal::profile.BGColour[3];
        ret["LightColour-Red"] = Crystal::profile.LightColour[0];
        ret["LightColour-Green"] = Crystal::profile.LightColour[1];
        ret["LightColour-Blue"] = Crystal::profile.LightColour[2];
        ret["LightColour-Alpha"] = Crystal::profile.LightColour[3];
        ret["TitleColour-Red"] = Crystal::profile.TitleColour[0];
        ret["TitleColour-Green"] = Crystal::profile.TitleColour[1];
        ret["TitleColour-Blue"] = Crystal::profile.TitleColour[2];
        ret["TitleColour-Alpha"] = Crystal::profile.TitleColour[3];
        ret["borderRounding"] = Crystal::profile.borderRounding;
        ret["scrollbarSize"] = Crystal::profile.scrollbarSize;
        ret["scrollbarRounding"] = Crystal::profile.scrollbarRounding;
        ret["RGBAccent"] = Crystal::profile.RGBAccent;
        ret["borders"] = Crystal::profile.borders;
        ret["rounded"] = Crystal::profile.rounded;
        ret["titlebar"] = Crystal::profile.titlebar;
        ret["invisBG"] = Crystal::profile.invisBG;
        ret["diffTitleBar"] = Crystal::profile.diffTitleBar;
		ret["anticheat"] = Crystal::profile.anticheat;
		ret["unlockAll"] = Crystal::profile.unlockAll;
		ret["scalehack"] = Crystal::profile.scalehack;
		ret["objlimit"] = Crystal::profile.objlimit;
		ret["customobjlimit"] = Crystal::profile.customobjlimit;
		ret["verify"] = Crystal::profile.verify;
		ret["copy"] = Crystal::profile.copy;
		ret["editorZoom"] = Crystal::profile.editorZoom;
		ret["levelEdit"] = Crystal::profile.levelEdit;
		ret["loadfail"] = Crystal::profile.loadfail;
		ret["FPS"] = Crystal::profile.FPS;
		ret["FPSbypass"] = Crystal::profile.FPSbypass;
		ret["TPS"] = Crystal::profile.TPS;
		ret["TPSbypass"] = Crystal::profile.TPSbypass;
		ret["lockCursor"] = Crystal::profile.lockCursor;
		ret["transparentBG"] = Crystal::profile.transparentBG;
		ret["translists"] = Crystal::profile.translists;
		ret["betterbg"] = Crystal::profile.betterbg;
		ret["buttonDL"] = Crystal::profile.buttonDL;
		ret["buttonCL"] = Crystal::profile.buttonCL;
		std::vector<bool> displaysVec(value.displays.begin(), value.displays.end());
		json::Array displaysArray;
 		for(const auto& display : displaysVec) {
    		displaysArray.push_back(json::Value(display));
		}
		ret["displays"] = std::move(displaysArray);
        std::vector<int> positionsVec(value.displayPositions.begin(), value.displayPositions.end());
		json::Array positionsArray;
 		for(const auto& position : positionsVec) {
    		positionsArray.push_back(position);
		}
		ret["positions"] = std::move(positionsArray);
		std::vector<float> opacitiesVec(value.displayOpacity.begin(), value.displayOpacity.end());
		json::Array opacitiesArray;
 		for(const auto& opaciti : opacitiesVec) {
    		opacitiesArray.push_back(json::Value(opaciti));
		}
		ret["opacities"] = std::move(opacitiesArray);
        std::vector<float> scalesVec(value.displayScale.begin(), value.displayScale.end());
		json::Array scalesArray;
 		for(const auto& skale : scalesVec) {
    		scalesArray.push_back(skale);
		}
		ret["scales"] = std::move(scalesArray);
		//ret["keybindsSize"] = keybinds.size();
		//for (int i = 0; i < keybinds.size(); i++) {
			//ret[std::to_string(i).c_str()]["key"] = keybinds[i].activeKey;
			//ret[std::to_string(i).c_str()]["mod"] = keybinds[i].activeMod;
		//}
        return ret;
    }
};

void Crystal::saveMods(CrystalProfile const& data) {
    std::fstream jsonOutFile;
	jsonOutFile.open(geode::Mod::get()->getConfigDir().append("Config").append("GH_config.json"), std::ios::out);
	jsonOutFile << json::Serialize<CrystalProfile>::to_json(profile).dump();
	jsonOutFile.close();
}

CrystalProfile Crystal::loadMods() {
    std::fstream input(geode::Mod::get()->getConfigDir().append("Config").append("GH_config.json"));

    if (input && !input.eof()) {
		auto json = json2::parse(input);
		std::string ver = std::to_string(Mod::get()->getVersion().getMajor()) + "." + std::to_string(Mod::get()->getVersion().getMinor()) + "." + std::to_string(Mod::get()->getVersion().getPatch());
		if (ver == json["CrystalVer"]) {
			//keybinds.clear();
			//for (int i = 0; i < json["keybindsSize"]; i++) {
				//keybinds.push_back({json[std::to_string(i).c_str()]["key"], json[std::to_string(i).c_str()]["mod"]});
			//}
			const auto& displaysJson = json["displays"];
            auto& displaysArray = profile.displays;
            for (std::size_t i = 0; i < std::min(displaysJson.size(), displaysArray.size()); ++i) {
                displaysArray[i] = displaysJson[i];
                    
            }
			const auto& positionsJson = json["positions"];
			auto& positionsArray = profile.displayPositions;
            for (std::size_t i = 0; i < std::min(positionsJson.size(), positionsArray.size()); ++i) {
            	if (positionsJson[i].is_number_integer()) {
                	positionsArray[i] = static_cast<LabelPos>(positionsJson[i]);
                }
            }
			const auto& opacitiesJson = json["opacities"];
            auto& opacitiesArray = profile.displayOpacity;
            for (std::size_t i = 0; i < std::min(opacitiesJson.size(), opacitiesArray.size()); ++i) {
            	opacitiesArray[i] = opacitiesJson[i]; 
            }
			const auto& scalesJson = json["scales"];
			auto& scalesArray = profile.displayScale;
            for (std::size_t i = 0; i < std::min(scalesJson.size(), scalesArray.size()); ++i) {
            	scalesArray[i] = scalesJson[i]; 
            }

			for (auto& [key, value] : json.items()) {
				if (!value.is_null()) { // just in case
					return CrystalProfile {
						.message = json["message"],
						.tclicks = json["tclicks"],
						.sclicks = json["sclicks"],
						.oclicks = json["oclicks"],
						.rclicks = json["rclicks"],
						.ajumps = json["ajumps"],
						.tjumps = json["tjumps"],
						.tattoo = json["tattoo"],
						.redDying = json["redDying"],
						.redDeath = json["redDeath"],
						.hideID = json["hideID"],
						.author = json["author"], 
						.iat = json["iat"],
						.ipm = json["ipm"],
						.ilt = json["ilt"],
						.igt = json["igt"],
						//.noclip = json["noclip"],
						//.noclipP1 = json["noclipP1"],
						//.noclipP2 = json["noclipP2"],
						.tintOnDeath = json["tintOnDeath"],
						.resetOnAccuracy = json["resetOnAccuracy"],
						.resetOnDeath = json["resetOnDeath"],
						.resetAcc = json["resetAcc"],
						.resetDeath = json["resetDeath"],
						.deathEffect = json["deathEffect"],
						.instantdeath = json["instantdeath"],
						.autoreset = json["autoreset"],
						.autoresetnum = json["autoresetnum"],
						.respawnfix = json["respawnfix"],
						.practiceorbfix = json["practiceorbfix"],
						.nopulse = json["nopulse"],
						.trailsize = json["trailsize"],
						.solidwave = json["solidwave"],
						.invisibleplayer = json["invisibleplayer"],
						.customPlayerColor = json["customPlayerColor"],
						.customWaveColor = json["customWaveColor"],
						.rainbowIcon = json["rainbowIcon"],
						.rainbowP1 = json["rainbowP1"],
						.rainbowP2 = json["rainbowP2"],
						.rainbowP1wave = json["rainbowP1wave"],
						.rainbowP2wave = json["rainbowP2wave"],
						.rainbowspeed = json["rainbowspeed"],
						.samedual = json["samedual"],
						.hitboxes = json["hitboxes"],
						.onDeath = json["onDeath"],
						.drawTrail = json["drawTrail"],
						.inEditor = json["inEditor"],
						.particles = json["particles"],
						.progressBar = json["progressBar"],
						.accpercentage = json["accpercentage"],
						.hideatts = json["hideatts"],
						.hidenormalatts = json["hidenormalatts"],
						.hidepracticeatts = json["hidepracticeatts"],
						.pracmusic = json["pracmusic"],
						.ignoreESC = json["ignoreESC"],
						.confirmQuit = json["confirmQuit"],
						.hidepause = json["hidepause"],
						.autoldm = json["autoldm"],
						.autoSong = json["autoSong"],
						.flippedcontrol = json["flippedcontrol"],
						.mirrorcontrol = json["mirrorcontrol"],
						.startpos = json["startpos"],
						.checkpointswitch = json["checkpointswitch"],
						.framestep = json["framestep"],
						.lastCheckpoint = json["lastCheckpoint"],
						.noglow = json["noglow"],
						.nospike = json["nospike"],
						.mirror = json["mirror"],
						.layout = json["layout"],
						.autoclick = json["autoclick"],
						.ACpushframe = json["ACpushframe"],
						.ACrelframe = json["ACrelframe"],
						.testmode = json["testmode"],
						.safeMode = json["safeMode"], 
						.autoSafeMode = json["autoSafeMode"],
						.BGColour = { json["BGColour-Red"], json["BGColour-Green"], json["BGColour-Blue"], json["BGColour-Alpha"] },
						.LightColour = { json["LightColour-Red"], json["LightColour-Green"], json["LightColour-Blue"], json["LightColour-Alpha"] },
						.TitleColour = { json["TitleColour-Red"], json["TitleColour-Green"], json["TitleColour-Blue"], json["TitleColour-Alpha"] },
						.borderRounding = json["borderRounding"],
						.scrollbarSize = json["scrollbarSize"],
						.scrollbarRounding = json["scrollbarRounding"],
						.RGBAccent = json["RGBAccent"],
						.borders = json["borders"],
						.rounded = json["rounded"],
						.titlebar = json["titlebar"],
						.invisBG = json["invisBG"],
						.diffTitleBar = json["diffTitleBar"],
						.anticheat = json["anticheat"],
						.unlockAll = json["unlockAll"],
						.scalehack = json["scalehack"],
						.objlimit = json["objlimit"],
						.customobjlimit = json["customobjlimit"],
						.verify = json["verify"],
						.copy = json["copy"],
						.editorZoom = json["editorZoom"],
						.levelEdit = json["levelEdit"],
						.loadfail = json["loadfail"],
						.FPS = json["FPS"],
						.FPSbypass = json["FPSbypass"],
						.TPS = json["TPS"],
						.TPSbypass = json["TPSbypass"],
						.lockCursor = json["lockCursor"],
						.transparentBG = json["transparentBG"],
						.translists = json["translists"],
						.betterbg = json["betterbg"],
						.buttonDL = json["buttonDL"],
						.buttonCL = json["buttonCL"],
						.displays = json["displays"],
						.displayPositions = json["positions"],
						.displayOpacity = json["opacities"],
						.displayScale = json["scales"],
					};
				}
			}
		} else {
			ghc::filesystem::remove(Mod::get()->getConfigDir() / "Config" / "GH_config.json");
			auto errorAlert = FLAlertLayer::create(
				"Version Difference",
				"Your Crystal Client save file was used for a different version of Crystal, so your save file has been cleared. Thank you for using Crystal!",
				"OK"
			);
			//errorAlert->m_scene = layer;
			errorAlert->show();
		}
    }
    return Crystal::profile;
}