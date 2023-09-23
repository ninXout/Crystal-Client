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
#define STB_RECT_PACK_IMPLEMENTATION
#include <imstb_rectpack.h>
#define IMGUI_DEFINE_MATH_OPERATORS

using namespace geode::prelude;
using namespace AmethystReplay;

const char* displaySelection[4] = {"Top Right", "Top Left", "Bottom Right", "Bottom Left"};
size_t sortIndex = 0;
constexpr int sortPadding = 3;
std::vector<stbrp_rect> sortRects;

void windowPreBegin(size_t& sortIndex) {
	if (getVar<bool>("manual_positioning")) return;
    if (getTempVar<int>("should-sort-windows") == 1) {
        auto rect = sortRects[sortIndex++];
        ImGui::SetNextWindowPos({
            (float)rect.x + sortPadding,
            (float)rect.y + sortPadding
        });
    }
	//ImGui::SetNextWindowSize({-1.f, -1.f});
}
void windowPreEnd() {
	if (getVar<bool>("manual_positioning")) return;
    ImVec2 size = ImGui::GetWindowSize();
    if (getTempVar<int>("should-sort-windows") == 2) {
        sortRects.push_back({
            0,
            (int)size.x + sortPadding,
            (int)size.y + sortPadding
        });
    }
}

$execute {
	loadConfigFromFile();
	Shortcuts::get()->refreshKeybinds(false);
    ImGuiCocos::get().setup([] {
        CrystalClient::get()->addTheme(true);
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
	if (!getVar<bool>("manual_positioning")) window_flags = ImGuiWindowFlags_AlwaysAutoResize;

    windowPreBegin(sortIndex);
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
	CrystalClient::ImToggleable("No Death Effect", setVar<bool>("no_death_effect"), "Removes the player's death effect");
	//CrystalClient::ImToggleable("Instant Death Respawn", setVar<bool>("instant_death_respawn"));
	CrystalClient::ImExtendedToggleable("Auto Reset", setVar<bool>("auto_reset"), "Resets the player at a certain percentage");
	if (ImGui::BeginPopupModal("Auto Reset", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Auto Reset Percentage", setVar<float>("auto_reset_num"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	CrystalClient::ImToggleable("Respawn Bug Fix", setVar<bool>("respawn_fix"), "Removes the lag when respawning");
	CrystalClient::ImToggleable("Practice Bug Fix", setVar<bool>("practice_fix"), "Fixes the Practice Mode bug that allows you to hit an orb twice");
	CrystalClient::ImToggleable("No Rotation", setVar<bool>("no_rotation"), "Stops the player from rotating");
	CrystalClient::ImToggleable("No Trail", setVar<bool>("no_trail"), "Removes the regular trail");
	CrystalClient::ImToggleable("Trail Always On", setVar<bool>("always_trail"), "Does the regular trail always visible");
	CrystalClient::ImExtendedToggleable("No Wave Pulse", setVar<bool>("no_wave_pulse"), "Stops the wave trail on a player from pulsing");
	if (ImGui::BeginPopupModal("No Wave Pulse", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Wave Trail Size", setVar<float>("wave_size"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Solid Wave Trail", setVar<bool>("solid_wave"), "Removes the blending from the wave trail");
	CrystalClient::ImToggleable("Solid Regular Trail", setVar<bool>("solid_trail"), "Removes the blending from the regular trail");
	CrystalClient::ImToggleable("Invisible Player", setVar<bool>("invis_player"), "Makes the player icon invisible");
	windowPreEnd();
	ImGui::End();

	windowPreBegin(sortIndex);
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
	CrystalClient::ImToggleable("Solid Glow Color", setVar<bool>("solid_glow"), "Removes the blending from the icon glow");
	windowPreEnd();
	ImGui::End();

	windowPreBegin(sortIndex);
	ImGui::Begin("Level", NULL, window_flags);
	CrystalClient::ImExtendedToggleable("Hitbox Viewer", setVar<bool>("hitboxes"), "Shows the hitboxes of every object in a level");
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
	CrystalClient::ImToggleable("No Progress Bar", setVar<bool>("no_progress_bar"), "Removes the progress bar, and centers the percentage text");
	CrystalClient::ImExtendedToggleable("Accurate Percentage", setVar<bool>("acc_percentage"), "Adds decimals to the percentage text");
	if (ImGui::BeginPopupModal("Accurate Percentage", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputInt("Percentage Decimal Points", setVar<int>("acc_percentage_decimals"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Hide Attempts Label", setVar<bool>("hide_attempts"), "Hides the Attempt label at the beginning of a level");
	if (ImGui::BeginPopupModal("Hide Attempts Label", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide in Normal Mode", setVar<bool>("hide_attempts_normal"));
		CrystalClient::ImToggleable("Hide in Practice Mode", setVar<bool>("hide_attempts_practice"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Practice Music Hack", setVar<bool>("practice_music"), "Plays the normal music in practice mode");
	CrystalClient::ImToggleable("Freeze Attempts", setVar<bool>("freeze_attempts"), "The attempts doesn't update");
	CrystalClient::ImToggleable("Hide Pause Menu", setVar<bool>("hide_pause"), "Hides the pause menu when pausing the game");
	CrystalClient::ImToggleable("Hide Pause Button", setVar<bool>("hide_pause_button"), "Hides the pause button when playing");
	CrystalClient::ImToggleable("Ignore ESC", setVar<bool>("ignore_esc"), "Stops quitting the level when pressing ESC");
	CrystalClient::ImToggleable("Confirm Quit", setVar<bool>("confirm_quit"), "Displays a popup to confirm before quitting a level");
	CrystalClient::ImToggleable("Auto LDM", setVar<bool>("auto_ldm"), "Immediately turns on LDM on all levels (if there is one)");
	CrystalClient::ImToggleable("Auto Song Downloader", setVar<bool>("auto_song_download"), "Immediately downloads the song for every level");
	CrystalClient::ImToggleable("Play Song on Level Page", setVar<bool>("play_song_level_page"), "Adds a button so you can listen the level's song without entering on it");
	CrystalClient::ImToggleable("Flipped Dual Controls", setVar<bool>("flipped_dual"), "Flips the 2 player inputs");
	CrystalClient::ImToggleable("Mirrored Dual Controls", setVar<bool>("mirrored_dual"), "Mirrors the 2 player inputs");
	CrystalClient::ImToggleable("Smart StartPos [BETA]", setVar<bool>("smart_startpos"), "Automatically sets up all StartPoses in a level");
	CrystalClient::ImToggleable("StartPos Switcher", setVar<bool>("startpos_switch"), "Allows you to switch between StartPoses while in a level");
	CrystalClient::ImToggleable("Frame Stepper", setVar<bool>("framestep"), "Allows you to play a level frame by frame (Requires the Framestep keybind to be binded)");
	CrystalClient::ImToggleable("Load from Last Checkpoint", setVar<bool>("load_from_last_CP"), "At the end of a practice mode run, restart from the last checkpoint when you click its button");
	CrystalClient::ImToggleable("No Glow", setVar<bool>("no_glow"), "Removes all glow from objects in a level");
	CrystalClient::ImToggleable("No Particles", setVar<bool>("no_particles"), "Removes all the particles");
	CrystalClient::ImToggleable("No Portal Flash", setVar<bool>("no_portal_flash"), "Removes the flash that happens when you enter a portal");
	CrystalClient::ImToggleable("No Ghost Trail", setVar<bool>("no_ghost"), "Removes the trail that one trigger gives you");
	CrystalClient::ImToggleable("No Mirror Effect", setVar<bool>("no_mirror"), "Disables all Mirror portals from working");
	CrystalClient::ImToggleable("Layout Mode", setVar<bool>("layout_mode"), "Shows the layout of a level");
	CrystalClient::ImExtendedToggleable("AutoClicker", setVar<bool>("autoclicker"), "Automatically clicks at a fixed interval");
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
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
	ImGui::Begin("Display", NULL, window_flags);
	CrystalClient::ImToggleable("Testmode Label", setVar<bool>("testmode_label"));
	ImGui::PushItemWidth(100);
	ImGui::InputFloat("Display Scale", setVar<float>("display_scale"));
	ImGui::InputFloat("Display Opacity", setVar<float>("display_opacity"));
	ImGui::InputFloat("Display Spacing", setVar<float>("display_space"));
	ImGui::PopItemWidth();
	CrystalClient::ImExtendedToggleable("Cheat Indicator", setVar<bool>("cheat_indicator"), "Displays whether you are cheating or not");
	if (ImGui::BeginPopupModal("Cheat Indicator", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-0"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Custom Message", setVar<bool>("custom_message"), "Displays a custom message");
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImTextbox("Message", setVar<std::string>("message"));
		ImGui::Combo("Position", setVar<int>("label_pos-1"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("CPS display", setVar<bool>("cps_display"), "Displays your clicks per second");
	if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		//CrystalClient::ImToggleable("Green Pulse On Click", &Crystal::profile.tclicks);
		ImGui::Combo("Position", setVar<int>("label_pos-2"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", setVar<bool>("fps_display"), "Displays your frames per second");
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-3"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Last Death", setVar<bool>("last_death"), "Displays the last death percentage");
	if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-4"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Attempts", setVar<bool>("attempts"), "Displays your attempt count");
	if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Attempts", setVar<bool>("total_attempts"));
		ImGui::Combo("Position", setVar<int>("label_pos-5"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", setVar<bool>("jumps"), "Displays your jumps");
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Jumps", setVar<bool>("total_jumps"));
		ImGui::Combo("Position", setVar<int>("label_pos-6"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Run From", setVar<bool>("run_from"), "Displays the percentage you started from");
	if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-7"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Best Run", setVar<bool>("best_run"), "Displays your best run on a level");
	if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-8"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", setVar<bool>("noclip_accuracy"), "Displays how accurately you can noclip through a percentage");
	if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_accuracy"));
		ImGui::Combo("Position", setVar<int>("label_pos-9"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Deaths", setVar<bool>("noclip_deaths"), "Displays how accurately you can noclip through a death counter");
	if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", setVar<bool>("red_on_death"));
		ImGui::Combo("Position", setVar<int>("label_pos-10"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Level Name and ID", setVar<bool>("level_info"), "Displays the level's information");
	if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide ID", setVar<bool>("hide_ID"));
		CrystalClient::ImToggleable("Show Author", setVar<bool>("level_info_author"));
		ImGui::Combo("Position", setVar<int>("label_pos-11"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Macro Status", setVar<bool>("macro_status"), "Displays information about the currently loaded macro");
	if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-12"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clock", setVar<bool>("clock"), "Displays the current time in your timezone");
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", setVar<int>("label_pos-13"), displaySelection, IM_ARRAYSIZE(displaySelection));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
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
	CrystalClient::ImToggleable("Force Manual Positioning", setVar<bool>("manual_positioning"), "Stops rearranging the windows whenever you open the game");
	if (ImGui::Button("Rearrange Windows")) *setTempVar<int>("should-sort-windows") = 3;
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
	ImGui::Begin("Bypasses", NULL, window_flags);
	CrystalClient::ImToggleable("Anticheat Bypass", setVar<bool>("anticheat"), "Disables the game's Anticheat system");
	CrystalClient::ImToggleable("Unlock All", setVar<bool>("unlock_all"), "Unlock all icons in the game");
	CrystalClient::ImToggleable("Scale Hack", setVar<bool>("scalehack"), "Bypass the scaling limit for objects");
	CrystalClient::ImToggleable("Object Limit Bypass", setVar<bool>("obj_limit"), "Bypass the object limit for levels");
	CrystalClient::ImToggleable("Custom Object Object Limit Bypass", setVar<bool>("custom_obj_limit"), "Bypass the object limit for custom objects");
	CrystalClient::ImToggleable("Verify Bypass", setVar<bool>("verify"), "Automatically sets levels as Verified");
	CrystalClient::ImToggleable("Copy Bypass", setVar<bool>("copy_hack"), "Allows you to copy any level");
	CrystalClient::ImToggleable("Editor Zoom Bypass", setVar<bool>("editor_zoom"), "Bypass the limits on the zoom in the editor");
	CrystalClient::ImToggleable("Level Edit Bypass", setVar<bool>("level_edit"), "Allows you to edit any level");
	CrystalClient::ImToggleable("Load Failed Bypass", setVar<bool>("load_failed"), "Bypasses the LOAD FAILED error in levels");
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
	ImGui::Begin("Global", NULL, window_flags);
	ImGui::PushItemWidth(100);
    ImGui::InputFloat("##FPS Bypass", setVar<float>("FPS"));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("FPS Bypass", setVar<bool>("FPS_bypass"));
	ImGui::PushItemWidth(100);
    ImGui::InputFloat("##Speedhack", setVar<float>("speed"));
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("Speedhack", setVar<bool>("speedhack"));
	if (getVar<float>("speed") != 0 && getVar<bool>("speedhack")) CCDirector::sharedDirector()->getScheduler()->setTimeScale(getVar<float>("speed"));
	else CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0);
	CrystalClient::ImExtendedToggleable("Safe Mode", setVar<bool>("safe_mode"), "Stops progress on levels to prevent accidental cheating");
	if (ImGui::BeginPopupModal("Safe Mode", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Auto Safe Mode", setVar<bool>("auto_safe_mode"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Lock Cursor", setVar<bool>("lock_cursor"), "Locks your cursor to the game window");
	CrystalClient::ImToggleable("No Pause on Unfocus", setVar<bool>("no_pause_unfocus"), "Keeps the game running when you are tabbed out");
	CrystalClient::ImToggleable("Mute on Unfocus", setVar<bool>("mute_unfocus"), "Mutes the game when you are tabbed out");
	CrystalClient::ImToggleable("No Transition", setVar<bool>("no_transition"), "Removes the fade transition when switching menus");
	CrystalClient::ImToggleable("Transparent BG", setVar<bool>("transparent_BG"), "Removes the blue tint on the gradient background");
	CrystalClient::ImToggleable("Transparent Lists", setVar<bool>("transparent_lists"), "Removes the hardcoded brown on lists");
	CrystalClient::ImToggleable("Better BG", setVar<bool>("better_BG"), "Adds an image to the background of the main menu");
	CrystalClient::ImToggleable("Demon List Button", setVar<bool>("demonlist_button"), "Adds a demon list button to the Search Menu");
	CrystalClient::ImToggleable("Challenge List Button", setVar<bool>("challengelist_button"), "Adds a challenge list button to the Search Menu");
	CrystalClient::ImToggleable("Copy Song ID", setVar<bool>("copy_songID"), "Allows you to copy a song ID by clicking on it");
	CrystalClient::ImToggleable("Copy Level ID Everywhere", setVar<bool>("copy_levelID"), "Allows you to copy a level ID by clicking on it in the editor");
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
	ImGui::Begin("Amethyst [BETA]", NULL, window_flags);
    CrystalClient::ImToggleable("Record", setVar<bool>("AT_record"), "Record a macro");
	ImGui::SameLine();
    CrystalClient::ImToggleable("Replay", setVar<bool>("AT_replay"), "Replay a macro");
	CrystalClient::ImToggleable("ClickBot", setVar<bool>("clickbot"), "Plays fake clicks for a macro");
	ImGui::SameLine();
	CrystalClient::ImToggleable("Delta Lock", setVar<bool>("delta_lock"), "Locks the time to the framerate");
	ImGui::PushItemWidth(150);
	ImGui::InputFloat("ClickBot Volume", setVar<float>("clickbot_volume"));
	CrystalClient::ImTextbox("Macro Name", setVar<std::string>("AT_macro_name"));
	ImGui::PopItemWidth();
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
    windowPreEnd();
	ImGui::End();
    windowPreBegin(sortIndex);
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
	ImGui::PushItemWidth(150);
    ImGui::Combo("Keybind", &Shortcuts::get()->currentKey, Shortcuts::get()->keybindings, IM_ARRAYSIZE(Shortcuts::get()->keybindings));
    ImGui::Combo("Mod to Switch", &Shortcuts::get()->currentMod, Shortcuts::get()->modbindings, IM_ARRAYSIZE(Shortcuts::get()->modbindings));
	ImGui::PopItemWidth();
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
    windowPreEnd();
	ImGui::End();
	windowPreBegin(sortIndex);
	ImGui::Begin("Variable Changer", NULL, window_flags);
	ImGui::PushItemWidth(150);
    ImGui::Combo("Variable", &Shortcuts::get()->currentVar, Shortcuts::get()->playerVars, IM_ARRAYSIZE(Shortcuts::get()->playerVars));
	ImGui::InputFloat("Value", &Shortcuts::get()->currentValue);
	ImGui::PopItemWidth();
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
    windowPreEnd();
	ImGui::End();
	windowPreBegin(sortIndex);
	ImGui::Begin("Internal Renderer", NULL, window_flags);
	CrystalClient::ImToggleable("Render Recording", setVar<bool>("AT_render"));
	CrystalClient::ImToggleable("Include Displays", setVar<bool>("include_displays"));
	ImGui::PushItemWidth(150);
	CrystalClient::ImTextbox("Video Name", setVar<std::string>("video_name"));
	ImGui::InputInt("Width", setVar<int>("target_width"));
	ImGui::InputInt("Height", setVar<int>("target_height"));
	ImGui::InputInt("FPS", setVar<int>("target_FPS"));
	ImGui::PopItemWidth();
	windowPreEnd();
	ImGui::End();
	windowPreBegin(sortIndex);
	ImGui::Begin("Screenshots", NULL, window_flags);
	//CrystalClient::ImToggleable("Include Players", setVar<bool>("SS_players"));
	CrystalClient::ImToggleable("Include Displays", setVar<bool>("SS_displays"), "Include Display texts in your Screenshot");
	windowPreEnd();
	ImGui::End();

	if (getTempVar<int>("should-sort-windows") == 2) {
		ImGuiIO& io = ImGui::GetIO();
		stbrp_context ctx;
		auto nodeCount = static_cast<int>(io.DisplaySize.x * 2.f);
		auto* nodes = new stbrp_node[nodeCount];
		memset(nodes, 0, sizeof(stbrp_node) * nodeCount);

		stbrp_init_target(&ctx, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y), nodes, nodeCount);
		stbrp_pack_rects(&ctx, sortRects.data(), static_cast<int>(sortRects.size()));

		delete[] nodes;
	}
	else if(getTempVar<int>("should-sort-windows") == 1) {
		sortRects.clear();
	}

	if (getTempVar<int>("should-sort-windows") > 0)
		*setTempVar<int>("should-sort-windows") -= 1;
}

void CrystalClient::addTheme(bool first) {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colors = ImGui::GetStyle().Colors;

	if (first) setupFonts((Mod::get()->getResourcesDir() / "Lexend.ttf").c_str(), 14.0f);
	if (first) *setTempVar<int>("should-sort-windows") = 3;

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
	bool versionMatch() {
		return (getVar<int>("ver-major") == Mod::get()->getVersion().getMajor() && getVar<int>("ver-minor") == Mod::get()->getVersion().getMinor() && getVar<int>("ver-patch") == Mod::get()->getVersion().getPatch());
	}

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

		if (!versionMatch()) {
			modsMapB = {
				{"noclip_P1", true},
				{"noclip_P2", true}
			};
			modsMapI = {
				{"AC_pushFrame", 1},
				{"AC_releaseFrame", 1},
				{"acc_percentage_decimals", 2}
			};
			modsMapF = {
				{"wave_size", 2.1},
				{"FPS", 60.0},
				{"FPS_unfocused", 15.0},
				{"display_scale", 1.0},
				{"display_opacity", 200.0},
				{"display_space", 20.0},
				{"speed", 1.0},
				{"BGcolor-red", 0.12f},
				{"BGcolor-blue", 0.12f},
				{"BGcolor-green", 0.12f},
				{"BGcolor-alpha", 1.0f},
				{"lightColor-red", 0.262715f},
				{"lightColor-blue", 0.624691f},
				{"lightColor-green", 0.818605f},
				{"lightColor-alpha", 1.0f},
				{"clickbot_volume", 100.0f}
			};
			modsMapS = {};
			saveConfigToFile();
			FLAlertLayer* mismatch = FLAlertLayer::create(
				"Version Mismatch",
				"Your Crystal save file's version didn't match your current one, so your save file has been cleared. Thank you for using Crystal Client!",
				"OK"
			);
			mismatch->m_scene = this;
			mismatch->show();
			*setVar<int>("ver-major") = Mod::get()->getVersion().getMajor();
			*setVar<int>("ver-minor") = Mod::get()->getVersion().getMinor();
			*setVar<int>("ver-patch") = Mod::get()->getVersion().getPatch();
		}

		return true;
	}
};
while (true) {
	if () {
modsMapF = {
    {"wave_size", 2.1},
    {"opacity_wave_trail", 255},
    {"FPS", 60.0},
    {"FPS_unfocused", 15.0},
    {"display_scale", 1.0},
    {"display_opacity", 200.0},
    {"display_space", 20.0},
    {"speed", 1.0},
    {"BGcolor-red", 0.12f},
    {"BGcolor-blue", 0.12f},
    {"BGcolor-green", 0.12f},
    {"BGcolor-alpha", 1.0f},
    {"lightColor-red", 0.262715f},
    {"lightColor-blue", 0.624691f},
    {"lightColor-green", 0.818605f},
    {"lightColor-alpha", 1.0f},
    {"clickbot_volume", 100.0f}
};
	}
}



//inline std::map<std::string, float> modsMapF = {
//    {"wave_size", 2.1},
//    {"opacity_wave_trail", 255},
//    {"FPS", 60.0},
//    {"FPS_unfocused", 15.0},
//    {"display_scale", 1.0},
//    {"display_opacity", 200.0},
//    {"display_space", 20.0},
//    {"speed", 1.0},
//    {"BGcolor-red", 0.12f},
//    {"BGcolor-blue", 0.12f},
//    {"BGcolor-green", 0.12f},
//    {"BGcolor-alpha", 1.0f},
//    {"lightColor-red", 0.262715f},
//    {"lightColor-blue", 0.624691f},
//    {"lightColor-green", 0.818605f},
//    {"lightColor-alpha", 1.0f},
//    {"clickbot_volume", 100.0f}
//};
