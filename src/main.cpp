#include <imgui.h>
#include "./CrystalClient/CrystalClient.hpp"
#include "Hacks.hpp"
#include "./Icon/Icon.hpp"
#include <random>
#include "./ImGui/ImGui.hpp"
#include "Shortcuts.hpp"
#include "CrystalProfile.hpp"
#include <Geode/Geode.hpp>
#include "Renderer/Renderer.hpp"
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;
using namespace AmethystReplay;

const char* displaySelection[4] = {"Top Right", "Top Left", "Bottom Right", "Bottom Left"};

$execute {
	loadConfigFromFile();
	Shortcuts::get()->refreshKeybinds(false);
    ImGuiCocos::get().setup([] {
        CrystalClient::get()->addTheme();
    }).draw([] {
        CrystalClient::get()->drawGUI();
    });
    ImGuiCocos::get().toggle();

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

void CrystalClient::drawGUI() {
	ImGuiWindowFlags window_flags = 0;

    ImGui::Begin("Player", NULL, window_flags);
	CrystalClient::ImExtendedToggleable("Noclip", setVar<bool>("noclip"), "Allows the player to be invincible");
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
		CrystalClient::ImIconEffect("Player Color 1", "P1C1");
		CrystalClient::ImIconEffect("Player Color 2", "P1C2");
		CrystalClient::ImIconEffect("Icon Glow", "P1G");
		CrystalClient::ImIconEffect("Regular Trail", "P1R");
		CrystalClient::ImIconEffect("Wave Trail", "P1W");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Player 2")) {
		CrystalClient::ImIconEffect("Player Color 1", "P2C1");
		CrystalClient::ImIconEffect("Player Color 2", "P2C2");
		CrystalClient::ImIconEffect("Icon Glow", "P2G");
		CrystalClient::ImIconEffect("Regular Trail", "P2R");
		CrystalClient::ImIconEffect("Wave Trail", "P2W");
		ImGui::EndMenu();
	}
	CrystalClient::ImToggleable("Solid Glow Color", setVar<bool>("solid_glow"));
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
		ImGui::Combo("Position", setVar<int>("label_pos-0"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Custom Message", setVar<bool>("custom_message"));
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImTextbox("Message", setVar<std::string>("message"));
		ImGui::Combo("Position", setVar<int>("label_pos-1"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("CPS display", setVar<bool>("cps_display"));
	if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		//CrystalClient::ImToggleable("Green Pulse On Click", &Crystal::profile.tclicks);
		ImGui::Combo("Position", setVar<int>("label_pos-2"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", setVar<bool>("fps_display"));
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-3"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Last Death", setVar<bool>("last_death"));
	if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-4"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Attempts", setVar<bool>("attempts"));
	if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Attempts", setVar<bool>("total_attempts"));
		ImGui::Combo("Position", setVar<int>("label_pos-5"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", setVar<bool>("jumps"));
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Jumps", setVar<bool>("total_jumps"));
		ImGui::Combo("Position", setVar<int>("label_pos-6"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Run From", setVar<bool>("run_from"));
	if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-7"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Best Run", setVar<bool>("best_run"));
	if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-8"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", setVar<bool>("noclip_accuracy"));
	if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_accuracy"));
		ImGui::Combo("Position", setVar<int>("label_pos-9"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Deaths", setVar<bool>("noclip_deaths"));
	if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_death"));
		ImGui::Combo("Position", setVar<int>("label_pos-10"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Level Name and ID", setVar<bool>("level_info"));
	if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide ID", setVar<bool>("hide_ID"));
		CrystalClient::ImToggleable("Show Author", setVar<bool>("level_info_author"));
		ImGui::Combo("Position", setVar<int>("label_pos-11"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Macro Status", setVar<bool>("macro_status"));
	if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-12"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clock", setVar<bool>("clock"));
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-13"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Customization", NULL, window_flags);
	CrystalClient::Im4FloatColor("Accent Color", "lightColor");
	CrystalClient::Im4FloatColor("Base Color", "BGcolor");
	CrystalClient::ImExtendedToggleable("Different Titlebar Color", setVar<bool>("diff_title"));
	if (ImGui::BeginPopupModal("Different Titlebar Color", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::Im4FloatColor("Titlebar Color", "diff_title");
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Window Borders", setVar<bool>("border"));
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
	ImGui::PushItemWidth(100);
	ImGui::InputFloat("##Unfocused FPS", setVar<float>("FPS_unfocused"));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("Unfocused FPS", setVar<bool>("Unfocused_FPS"));
	ImGui::PushItemWidth(100);
    ImGui::InputFloat("Speedhack", setVar<float>("speed"));
	ImGui::PopItemWidth();
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
	CrystalClient::ImToggleable("No Transition", setVar<bool>("no_transition"));
	CrystalClient::ImToggleable("Transparent BG", setVar<bool>("transparent_BG"));
	CrystalClient::ImToggleable("Transparent Lists", setVar<bool>("transparent_lists"));
	CrystalClient::ImToggleable("Better BG", setVar<bool>("better_BG"));
	CrystalClient::ImToggleable("Demon List Button", setVar<bool>("demonlist_button"));
	CrystalClient::ImToggleable("Challenge List Button", setVar<bool>("challengelist_button"));
	CrystalClient::ImToggleable("Copy Song ID", setVar<bool>("copy_songID"));
	CrystalClient::ImToggleable("Copy Level ID Everywhere", setVar<bool>("copy_levelID"));
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
	CrystalClient::ImTextbox("Macro Name", setVar<std::string>("AT_macro_name"));
    if (ImGui::Button("Save Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + getVar<std::string>("AT_macro_name") + ".thyst";
		currentMacro.saveToFile(filename.c_str());
	}
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + getVar<std::string>("AT_macro_name") + ".thyst";
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
	CrystalClient::ImToggleable("Render Recording", setVar<bool>("AT_render"));
	CrystalClient::ImToggleable("Include Displays", setVar<bool>("include_displays"));
	CrystalClient::ImTextbox("Video Name", setVar<std::string>("video_name"));
	ImGui::InputInt("Width", setVar<int>("target_width"));
	ImGui::InputInt("Height", setVar<int>("target_height"));
	ImGui::InputInt("FPS", setVar<int>("target_FPS"));
	ImGui::End();
}

void CrystalClient::addTheme() {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;

	setupFonts((Mod::get()->getResourcesDir() / "Lexend.ttf").c_str(), 14.0f);

    *setVar<float>("darkColor-red") = (getVar<float>("lightColor-red") * 0.5f);
    *setVar<float>("darkColor-green") = (getVar<float>("lightColor-green") * 0.5f);
    *setVar<float>("darkColor-blue") = (getVar<float>("lightColor-blue") * 0.5f);
    *setVar<float>("darkColor-alpha") = getVar<float>("lightColor-alpha");
    *setVar<float>("veryLightColor-red") = (getVar<float>("lightColor-red") * 1.5f);
    *setVar<float>("veryLightColor-green") = (getVar<float>("lightColor-green") * 1.5f);
    *setVar<float>("veryLightColor-blue") = (getVar<float>("lightColor-blue") * 1.5f);
    *setVar<float>("veryLightColor-alpha") = getVar<float>("lightColor-alpha");

    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    style->Alpha = 1.f;
    style->WindowRounding = 0;
    style->FrameRounding = 4.f;
    style->ScrollbarSize = 12;
    style->ScrollbarRounding = 12;
    style->PopupRounding = 0;
    style->WindowBorderSize = 1.5f;
    colors[ImGuiCol_TitleBg] = VarToIV4(getVar<bool>("diff_title") ? "diff_title" : "BGcolor");
    colors[ImGuiCol_TitleBgActive] = VarToIV4(getVar<bool>("diff_title") ? "diff_title" : "BGcolor");
    colors[ImGuiCol_WindowBg] = VarToIV4("BGcolor");
    colors[ImGuiCol_Border] = VarToIV4(getVar<bool>("border") ? "lightColor" : "BGcolor");
    colors[ImGuiCol_FrameBg] = VarToIV4("darkColor");
    colors[ImGuiCol_FrameBgHovered] = VarToIV4("darkColor");
    colors[ImGuiCol_FrameBgActive] = VarToIV4("lightColor");
    colors[ImGuiCol_PlotHistogram] = VarToIV4("lightColor");
    colors[ImGuiCol_Button] = VarToIV4("lightColor");
    colors[ImGuiCol_ButtonHovered] = VarToIV4("veryLightColor");
    colors[ImGuiCol_Header] = VarToIV4("darkColor");
    colors[ImGuiCol_HeaderHovered] = VarToIV4("lightColor");
    colors[ImGuiCol_HeaderActive] = VarToIV4("veryLightColor");
    colors[ImGuiCol_SliderGrab] = VarToIV4("lightColor");
    colors[ImGuiCol_SliderGrabActive] = VarToIV4("veryLightColor");
    colors[ImGuiCol_CheckMark] = VarToIV4("veryLightColor");
}

class $modify(MenuLayer) {
	bool init() {
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

		if (!MenuLayer::init()) return false;

		std::fstream input(geode::Mod::get()->getConfigDir().append("Config").append("GH_config-01.json"));

		if (!input) CrystalClient::get()->firstLoad(this);

		return true;
	}
};