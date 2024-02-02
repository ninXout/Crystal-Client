#include "CrystalUI.hpp"
#include "../CrystalClient/CrystalClient.hpp"
#include "Fonts.hpp"
#include "ImGuiHelper.hpp"
//#include "../Mods/Keybind/Keybind.hpp"
#include <iostream>
#include <cmath>

using namespace CrystalClient;

ImVec4 operator+(const ImVec4& a, const ImVec4& b) {
	ImVec4 vec;
	vec.w = a.w + b.w;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return vec;
}

ImVec4 operator-(const ImVec4& a, const ImVec4& b) {
	ImVec4 vec;
	vec.w = a.w - b.w;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return vec;
}

ImVec4 operator*(const ImVec4& a, float b) {
	ImVec4 vec;
	vec.w = a.w;
	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return vec;
}

ImVec4 operator/(const ImVec4& a, float b) {
	ImVec4 vec;
	vec.w = a.w;
	vec.x = a.x / b;
	vec.y = a.y / b;
	vec.z = a.z / b;
	return vec;
}

void CrystalUI::setupFonts() {
    ImGuiIO& io = ImGui::GetIO();

	io.Fonts->Clear();

	ImFontConfig cfg;
	cfg.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 18, &cfg);

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig iconCFG;
	iconCFG.MergeMode = true;
	iconCFG.PixelSnapH = true;
	iconCFG.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 18, &iconCFG, icons_ranges);

	ImFontConfig bigFontCfg;
	bigFontCfg.FontDataOwnedByAtlas = false;
	font = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 24, &bigFontCfg);
	io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 18, &iconCFG, icons_ranges);
    io.Fonts->Build();
}

void CrystalUI::setupTheme() {
	ImGuiStyle * style = &ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;

	CrystalClient::IV4toVar(CrystalClient::VarToIV4("BGcolor") - ImVec4((15.f / 255.f), (15.f / 255.f), (15.f / 255.f), 0.f), "darkColor");
	CrystalClient::IV4toVar(CrystalClient::VarToIV4("lightColor") + ImVec4(0.f, (10.f / 255.f), (10.f / 255.f), 0.f), "veryLightColor");

	style->FrameRounding = 2.0f;
	style->GrabRounding = 2.0f;
	style->Alpha = 1.f;
	style->WindowRounding = 0;
	style->FrameRounding = 2.f;
	style->ScrollbarSize = 12;
	style->ScrollbarRounding = 12;
	style->PopupRounding = 0;
	style->WindowBorderSize = 1.5f;
	colors[ImGuiCol_TitleBg] = CrystalClient::VarToIV4(getSavedVar<bool>("diff_title") ? "diff_title" : "BGcolor");
	colors[ImGuiCol_TitleBgActive] = CrystalClient::VarToIV4(getSavedVar<bool>("diff_title") ? "diff_title" : "BGcolor");
	colors[ImGuiCol_WindowBg] = CrystalClient::VarToIV4("BGcolor");
	colors[ImGuiCol_Border] = CrystalClient::VarToIV4(getSavedVar<bool>("border") ? "lightColor" : "BGcolor");
	colors[ImGuiCol_FrameBg] = CrystalClient::VarToIV4("darkColor");
	colors[ImGuiCol_FrameBgHovered] = CrystalClient::VarToIV4("darkColor");
	colors[ImGuiCol_FrameBgActive] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_PlotHistogram] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_Button] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_ButtonActive] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_Header] = CrystalClient::VarToIV4("darkColor");
	colors[ImGuiCol_HeaderHovered] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_HeaderActive] = CrystalClient::VarToIV4("veryLightColor");
	colors[ImGuiCol_SliderGrab] = CrystalClient::VarToIV4("lightColor");
	colors[ImGuiCol_SliderGrabActive] = CrystalClient::VarToIV4("veryLightColor");
	colors[ImGuiCol_CheckMark] = CrystalClient::VarToIV4("veryLightColor");
}

void CrystalUI::renderLogo() {
	ImGui::BeginGroup(); {
		ImGui::BeginChild("Logo", ImVec2(188, 50), true);

		ImGui::PushFont(font);
		ImGui::SameLine();

		ImGui::SetCursorPosY(11);
		ImGui::TextUnformatted("Crystal Client");
		ImGui::PopFont();

		ImGui::EndChild();

		if (ImGui::IsItemClicked(1)) {}

		ImGui::EndGroup();
	}
}

void CrystalUI::renderUser() {
	ImGuiStyle * style = &ImGui::GetStyle();
	ImGui::Dummy(ImVec2(0.0f, ImGui::GetContentRegionAvail().y - 80 - style->ItemSpacing.y));
	ImGui::BeginChild("User", ImVec2(188, 80), true);

	ImGui::EndChild();
}

void CrystalUI::renderTabs() {
	ImGuiStyle * style = &ImGui::GetStyle();
	ImGui::PushStyleColor(ImGuiCol_ChildBg, {0,0,0,0});
	ImGui::BeginChild("tabs", ImVec2(186, 480), true);
	ImGui::PopStyleColor();

	ImGui::PushItemWidth(160.f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
	textbox((std::string(" ") + ICON_FA_SEARCH" Search").c_str(), setSavedVar<std::string>("search"));
	ImGui::PopStyleVar();
	ImGui::PopItemWidth();
	ImGui::Spacing();

	ImVec4 col(0.152941f, 0.152941f, 0.250980f, 1.f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
	std::string tabNames[] = { std::string(ICON_FA_CUBE "  Player"), std::string(ICON_FA_PAINT_BRUSH "  Icon"), std::string(ICON_FA_LAYER_GROUP "  Level"), std::string(ICON_FA_FONT "  Displays"), std::string(ICON_FA_EYE_DROPPER "  Customize"), std::string(ICON_FA_LOCK_OPEN "  Bypasses"), std::string(ICON_FA_GLOBE "  Global"), std::string(ICON_FA_WINDOW_RESTORE "  UI"), std::string(ICON_FA_MOUSE_POINTER "  Amethyst"), std::string(ICON_FA_KEYBOARD "  Keybinds") };
	for (int i = 0; i < sizeof(tabNames) / sizeof(tabNames[0]); i++) {
		std::string it = std::string("  ") + tabNames[i];
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0, 0.5));
		ImGui::PushStyleColor(ImGuiCol_Button, selectedTab == i ? col : ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_Text, style->Colors[ImGuiCol_Text]);
		if (ImGui::Button(it.c_str(), ImVec2(160, 40))) {
			ImGui::GetIO().WantCaptureKeyboard = false;
			ImGui::SetWindowFocus(NULL);
			selectedTab = i;
		}
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(2);
	}
	ImGui::PopStyleVar();

	ImGui::EndChild();
}

void CrystalUI::renderRightColumn() {
	{
		ImGui::NextColumn();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
		ImGui::BeginChild("modules-wrapper", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
		ImGui::PopStyleColor();

		switch (selectedTab) {
			case 0: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("playertab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
				CrystalUI::toggleWithMenu("Noclip", setSavedVar<bool>("noclip"), "Allows the player to be invincible");
				/*
				if (ImGui::BeginPopupModal("Noclip", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Noclip Player 1", setSavedVar<bool>("noclip_P1"));
					CrystalUI::subToggle("Noclip Player 2", setSavedVar<bool>("noclip_P2"));
					CrystalUI::subToggle("Tint Screen on Death", setSavedVar<bool>("noclip_tint"));
					CrystalUI::colorPicker("Tint Color", "noclipColor");
					ImGui::PushItemWidth(100);
					CrystalUI::inputFloat("##Noclip Accuracy Limit", setSavedVar<float>("accuracy_limit_num"));
					ImGui::PopItemWidth();
					ImGui::SameLine();
					CrystalUI::subToggle("Noclip Accuracy Limit", setSavedVar<bool>("accuracy_limit"));
					ImGui::PushItemWidth(100);
					CrystalUI::inputInt("##Noclip Deaths Limit", setSavedVar<int>("death_limit_num"));
					ImGui::PopItemWidth();
					ImGui::SameLine();
					CrystalUI::subToggle("Noclip Deaths Limit", setSavedVar<bool>("death_limit"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggle("No Death Effect", setSavedVar<bool>("no_death_effect"), "Removes the player's death effect");
				CrystalUI::toggleWithMenu("Auto Kill", setSavedVar<bool>("auto_reset"), "Kills the player at a certain percentage");
				if (ImGui::BeginPopupModal("Auto Kill", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::PushItemWidth(100.f);
					CrystalUI::inputFloat("Auto Kill Percentage", setSavedVar<float>("auto_reset_num"));
					CrystalUI::toggle("Reset Level instead", setSavedVar<bool>("reset_instead"));
					ImGui::PopItemWidth();
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggle("No Rotation", setSavedVar<bool>("no_rotation"), "Stops the player from rotating");
				CrystalUI::toggle("Practice Bug Fix", setSavedVar<bool>("practice_fix"), "Fixes issues with Practice Mode");
				CrystalUI::toggle("Trail Always Off", setSavedVar<bool>("no_trail"), "Removes the regular trail");
				CrystalUI::toggle("Trail Always On", setSavedVar<bool>("always_trail"), "Makes the regular trail visible at all times");
				CrystalUI::toggleWithMenu("No Wave Pulse", setSavedVar<bool>("no_wave_pulse"), "Stops the wave trail on a player from pulsing");
				if (ImGui::BeginPopupModal("No Wave Pulse", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::PushItemWidth(100.f);
					CrystalUI::inputFloat("Wave Trail Size", setSavedVar<float>("wave_size"));
					ImGui::PopItemWidth();
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggle("Solid Wave Trail", setSavedVar<bool>("solid_wave"), "Removes the blending from the wave trail");
				CrystalUI::toggle("Invisible Player", setSavedVar<bool>("invis_player"), "Makes the player icon invisible");
				CrystalUI::toggle("Flipped Dual Controls", setSavedVar<bool>("flipped_dual"), "Flips the 2 player inputs");
				CrystalUI::toggle("Mirrored Dual Controls", setSavedVar<bool>("mirrored_dual"), "Mirrors the 2 player inputs");
				CrystalUI::toggle("StartPos Switcher", setSavedVar<bool>("startpos_switch"), "Allows you to switch between StartPoses while in a level");
				//CrystalUI::toggle("Frame Stepper", setSavedVar<bool>("framestep"), "Allows you to play a level frame by frame (Requires the Framestep keybind to be binded)");
				CrystalUI::toggleWithMenu("AutoClicker", setSavedVar<bool>("autoclicker"), "Automatically clicks at a fixed interval");
				if (ImGui::BeginPopupModal("AutoClicker", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Autoclick Player 1", setSavedVar<bool>("AC_player1"));
					CrystalUI::subToggle("Autoclick Player 2", setSavedVar<bool>("AC_player2")); // TODO: make this only on 2player mode
					ImGui::PushItemWidth(100.f);
					CrystalUI::inputInt("Push on Frame", setSavedVar<int>("AC_pushFrame"));
					CrystalUI::inputInt("Release on Frame", setSavedVar<int>("AC_releaseFrame"));
					ImGui::PopItemWidth();
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				*/
				ImGui::EndChild();

				break;
			}
			case 1: {
				ImGui::Columns(1, nullptr, false);

				std::vector<std::string> arr = {std::string("Player 1"), std::string("Player 2")};
				ImGuiHelper::drawTabHorizontally(std::string("iconsubtab"), ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab);
				ImGui::Spacing();

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("icontab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				/*
				switch (selectedSubTab) {
					case 0: {
						CrystalUI::iconEffect("Player Color 1", "P1C1");
						CrystalUI::iconEffect("Player Color 2", "P1C2");
						CrystalUI::iconEffect("Icon Glow", "P1G");
						CrystalUI::iconEffect("Regular Trail", "P1R");
						CrystalUI::iconEffect("Wave Trail", "P1W");
						break;
					}
					case 1: {
						CrystalUI::iconEffect("Player Color 1", "P2C1");
						CrystalUI::iconEffect("Player Color 2", "P2C2");
						CrystalUI::iconEffect("Icon Glow", "P2G");
						CrystalUI::iconEffect("Regular Trail", "P2R");
						CrystalUI::iconEffect("Wave Trail", "P2W");
						break;
					}
				}*/

				ImGui::EndChild();

				break;
			}
			case 2: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("leveltab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				/*CrystalUI::toggleWithMenu("Hitbox Viewer", setSavedVar<bool>("hitboxes"), "Shows the hitboxes of every object in a level");
				if (ImGui::BeginPopupModal("Hitbox Viewer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Show Hitboxes on Death", setSavedVar<bool>("hitbox_on_death"));
					CrystalUI::subToggle("Show Hitbox Trail", setSavedVar<bool>("hitbox_trail"));
					CrystalUI::subToggle("Show Hitboxes in Editor", setSavedVar<bool>("hitboxes_in_editor"));
					CrystalUI::subToggle("Coin Tracker", setSavedVar<bool>("coin_tracker"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggle("No Progress Bar", setSavedVar<bool>("no_progress_bar"), "Removes the progress bar, and centers the percentage text");
				CrystalUI::toggleWithMenu("Accurate Percentage", setSavedVar<bool>("acc_percentage"), "Adds decimals to the percentage text");
				if (ImGui::BeginPopupModal("Accurate Percentage", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::inputInt("Percentage Decimal Points", setSavedVar<int>("acc_percentage_decimals"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Hide Attempts Label", setSavedVar<bool>("hide_attempts"), "Hides the Attempt label at the beginning of a level");
				if (ImGui::BeginPopupModal("Hide Attempts Label", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Hide in Normal Mode", setSavedVar<bool>("hide_attempts_normal"));
					CrystalUI::subToggle("Hide in Practice Mode", setSavedVar<bool>("hide_attempts_practice"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}*/
				CrystalUI::toggle("Practice Music Hack", setSavedVar<bool>("practice_music"), "Plays the normal music in practice mode");
				/*
				CrystalUI::toggle("Freeze Attempts", setSavedVar<bool>("freeze_attempts"), "The attempts doesn't update");
				CrystalUI::toggle("Hide Pause Menu", setSavedVar<bool>("hide_pause"), "Hides the pause menu when pausing the game");
				//CrystalUI::toggle("Hide Pause Button", setSavedVar<bool>("hide_pause_button"), "Hides the pause button when playing");
				CrystalUI::toggle("Ignore ESC", setSavedVar<bool>("ignore_esc"), "Stops quitting the level when pressing ESC");
				CrystalUI::toggle("Confirm Quit", setSavedVar<bool>("confirm_quit"), "Displays a popup to confirm before quitting a level");
				CrystalUI::toggle("Auto LDM", setSavedVar<bool>("auto_ldm"), "Immediately turns on LDM on all levels (if there is one)");
				CrystalUI::toggle("Auto Song Downloader", setSavedVar<bool>("auto_song_download"), "Immediately downloads the song for every level");
				//CrystalUI::toggle("Play Song on Level Page", setSavedVar<bool>("play_song_level_page"), "Adds a button so you can listen the level's song without entering on it");
				CrystalUI::toggle("Load from Last Checkpoint", setSavedVar<bool>("load_from_last_CP"), "At the end of a practice mode run, restart from the last checkpoint when you click its button");
				CrystalUI::toggle("No Glow", setSavedVar<bool>("no_glow"), "Removes all glow from objects in a level");
				CrystalUI::toggle("No Particles", setSavedVar<bool>("no_particles"), "Removes all the particles");
				CrystalUI::toggle("No Portal Flash", setSavedVar<bool>("no_portal_flash"), "Removes the flash that happens when you enter a portal");
				CrystalUI::toggle("No Ghost Trail", setSavedVar<bool>("no_ghost"), "Removes the trail that one trigger gives you");
				CrystalUI::toggle("No Mirror Effect", setSavedVar<bool>("no_mirror"), "Disables all Mirror portals from working");
				CrystalUI::toggle("Layout Mode", setSavedVar<bool>("layout_mode"), "Shows the layout of a level");
				*/

				ImGui::EndChild();

				break;
			}
			case 3: {
				const char* displaySelection[4] = {"Top Right", "Top Left", "Bottom Right", "Bottom Left"};

				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("leveltab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
				
				//CrystalUI::toggle("Testmode Label", setSavedVar<bool>("testmode_label"));
				/*
				ImGui::PushItemWidth(100);
				CrystalUI::inputFloat("Display Scale", setSavedVar<float>("display_scale"));
				CrystalUI::inputFloat("Display Opacity", setSavedVar<float>("display_opacity"));
				CrystalUI::inputFloat("Display Spacing", setSavedVar<float>("display_space"));
				ImGui::PopItemWidth();
				CrystalUI::toggleWithMenu("Cheat Indicator", setSavedVar<bool>("cheat_indicator"), "Displays whether you are cheating or not");
				if (ImGui::BeginPopupModal("Cheat Indicator", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-0"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Custom Message", setSavedVar<bool>("custom_message"), "Displays a custom message");
				if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::textbox("Message", setSavedVar<std::string>("message"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-1"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("CPS display", setSavedVar<bool>("cps_display"), "Displays your clicks per second");
				if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					//CrystalUI::toggle("Green Pulse On Click", &Crystal::profile.tclicks);
					ImGui::Combo("Position", setSavedVar<int>("label_pos-2"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("FPS Display", setSavedVar<bool>("fps_display"), "Displays your frames per second");
				if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-3"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Last Death", setSavedVar<bool>("last_death"), "Displays the last death percentage");
				if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-4"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Attempts", setSavedVar<bool>("attempts"), "Displays your attempt count");
				if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Total Attempts", setSavedVar<bool>("total_attempts"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-5"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Jumps", setSavedVar<bool>("jumps"), "Displays your jumps");
				if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Total Jumps", setSavedVar<bool>("total_jumps"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-6"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Run From", setSavedVar<bool>("run_from"), "Displays the percentage you started from");
				if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-7"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Best Run", setSavedVar<bool>("best_run"), "Displays your best run on a level");
				if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-8"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Noclip Accuracy", setSavedVar<bool>("noclip_accuracy"), "Displays how accurately you can noclip through a percentage");
				if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Red Pulse on Death", setSavedVar<bool>("red_on_accuracy"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-9"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Noclip Deaths", setSavedVar<bool>("noclip_deaths"), "Displays how accurately you can noclip through a death counter");
				if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Red Pulse on Death", setSavedVar<bool>("red_on_death"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-10"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Level Name and ID", setSavedVar<bool>("level_info"), "Displays the level's information");
				if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Hide ID", setSavedVar<bool>("hide_ID"));
					CrystalUI::subToggle("Show Author", setSavedVar<bool>("level_info_author"));
					ImGui::Combo("Position", setSavedVar<int>("label_pos-11"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Macro Status", setSavedVar<bool>("macro_status"), "Displays information about the currently loaded macro");
				if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-12"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("Clock", setSavedVar<bool>("clock"), "Displays the current time in your timezone");
				if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::Combo("Position", setSavedVar<int>("label_pos-13"), displaySelection, IM_ARRAYSIZE(displaySelection));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}*/

				ImGui::EndChild();

				break;
			}
			case 4: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("customizetab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				ImGui::EndChild();
			}
			case 5: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("bypasstab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				CrystalUI::toggle("Unlock All", setSavedVar<bool>("iconhack"), "Unlocks all icons and colors");
				CrystalUI::toggle("Instant Complete", setSavedVar<bool>("instant_complete"), "Instantly complete a level with all coins upon entering");
				/*
				CrystalUI::toggle("Scale Hack", setSavedVar<bool>("scalehack"), "Bypass the scaling limit for objects");
				CrystalUI::toggle("Verify Bypass", setSavedVar<bool>("verify"), "Automatically sets levels as Verified");
				CrystalUI::toggle("Copy Bypass", setSavedVar<bool>("copy_hack"), "Allows you to copy any level");
				CrystalUI::toggle("Editor Zoom Bypass", setSavedVar<bool>("editor_zoom"), "Bypass the limits on the zoom in the editor");
				CrystalUI::toggle("Level Edit Bypass", setSavedVar<bool>("level_edit"), "Allows you to edit any level");
				CrystalUI::toggle("Load Failed Bypass", setSavedVar<bool>("load_failed"), "Bypasses the LOAD FAILED error in levels");
				*/
				ImGui::EndChild();
				break;
			}
			case 6: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("globaltab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				CrystalUI::toggleWithMenu("Speedhack", setSavedVar<bool>("speedhack"));
				if (ImGui::BeginPopupModal("Speedhack", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					ImGui::SliderFloat("Speed", setSavedVar<float>("speed"), 0.001, 10.000); // CHANGE TO TEXT INPUT
					//CrystalUI::subToggle("Change Audio Speed", setSavedVar<bool>("speedhack_audio"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

/*
				CrystalUI::toggleWithMenu("FPS Bypass", setSavedVar<bool>("FPS_bypass"));
				if (ImGui::BeginPopupModal("FPS Bypass", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::inputFloat("FPS", setSavedVar<float>("FPS"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggleWithMenu("TPS Bypass", setSavedVar<bool>("TPS_bypass"));
				if (ImGui::BeginPopupModal("TPS Bypass", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::inputFloat("TPS", setSavedVar<float>("TPS"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				if (ImGui::BeginPopupModal("Safe Mode", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
					CrystalUI::subToggle("Auto Safe Mode", setSavedVar<bool>("auto_safe_mode"));
					if (ImGui::Button("Close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				CrystalUI::toggle("Lock Cursor", setSavedVar<bool>("lock_cursor"), "Locks your cursor to the game window", true);
				//CrystalUI::toggle("No Transition", setSavedVar<bool>("no_transition"), "Removes the fade transition when switching menus", true);
				CrystalUI::toggle("Transparent BG", setSavedVar<bool>("transparent_BG"), "Removes the blue tint on the gradient background");
				//CrystalUI::toggle("Transparent Lists", setSavedVar<bool>("transparent_lists"), "Removes the hardcoded brown on lists");
				CrystalUI::toggle("Discord Rich Presence", setSavedVar<bool>("discord_rpc"), "Displays your current activity on your Discord profile");
*/
				ImGui::EndChild();

				break;
			}
			case 8: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("amethysttab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				CrystalUI::toggle("Record", setSavedVar<bool>("AT-record"));
				CrystalUI::toggle("Replay", setSavedVar<bool>("AT-replay"));

				ImGui::EndChild();
			}
			case 9: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("keybindtab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				// KEYBINDS FOR LATER

/*
				if (Keybinds::waitingForKeybind) { ImGui::Button("Waiting for keypress..."); }
				else { if (ImGui::Button(Keybinds::keyToString(Keybinds::currentKey).c_str(), ImVec2(80, 40))) { Keybinds::waitingForKeybind = true; } }
				ImGui::PushItemWidth(150);
				ImGui::Combo("Mod to Toggle", &Keybinds::currentMod, Keybinds::modbindings, IM_ARRAYSIZE(Keybinds::modbindings));
				ImGui::PopItemWidth();
				if (ImGui::Button("Add Keybind")) {
					Keybinds::pushKeybind();
					CrystalClient::modsMapKEY[(int)Keybinds::keybind.back().first] = Keybinds::keybind.back().second;
				}
				for (size_t i = 0; i < Keybinds::keybind.size(); i++) {
					ImGui::AlignTextToFramePadding();
					ImGui::Text("%s", Keybinds::modbindings[Keybinds::keybind[i].second]);
					ImGui::SameLine();
					ImGui::Text("%s", Keybinds::keyToString(Keybinds::keybind[i].first).c_str());
					ImGui::SameLine();
					if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
						CrystalClient::modsMapKEY.erase((int)Keybinds::keybind[i].first);
						Keybinds::keybind.erase(Keybinds::keybind.begin() + i);
					}
					ImGui::Separator();
				}
*/
				ImGui::EndChild();

				break;
			}
			case 10: {
				ImGui::Columns(1, nullptr, false);

				ImGui::PushStyleColor(ImGuiCol_ChildBg, CrystalClient::VarToIV4("BGcolor") - ImVec4(0.05, 0.05, 0.05, 0.f));
				ImGui::PushStyleVar(7, 15.f);
				ImGui::BeginChild("leveltab", ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
				ImGui::PopStyleVar();
				ImGui::PopStyleColor();

				for (auto [k, v] : modsMapB) {
					if (k.find(getSavedVar<std::string>("search")) != std::string::npos) {
						CrystalUI::toggle(k.c_str(), &v);
					}
				}

				ImGui::EndChild();

				break;
			}
		}
		ImGui::EndChild();
	}
}

void CrystalUI::internalToggle(const char* str_id, bool* v, bool no_win) {
	ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

	#ifdef GEODE_IS_MACOS
		no_win = false;
	#endif

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.475f;

	if (ImGui::InvisibleButton(str_id, ImVec2(width, height)))
		*v = !*v;

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), *v ? ImGui::ColorConvertFloat4ToU32(CrystalClient::VarToIV4("lightColor")) : ImGui::ColorConvertFloat4ToU32(((CrystalClient::VarToIV4("BGcolor") * 2.f) + CrystalClient::VarToIV4("lightColor")) / 3.f), height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, ImGui::ColorConvertFloat4ToU32(CrystalClient::VarToIV4("BGcolor")));
}

void CrystalUI::subToggle(const char* str_id, bool* v) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	CrystalUI::internalToggle(str_id, v);
	ImGui::SameLine();
	ImGui::TextColored(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", str_id);
	if (ImGui::IsItemClicked()) *v = !*v;
}

void CrystalUI::subToggleWithMenu(const char* str_id, bool* v) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	CrystalUI::internalToggle(str_id, v);
	ImGui::SameLine();
	ImGui::TextColored(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", str_id);
	if (ImGui::IsItemClicked()) *v = !*v;

	ImGui::SameLine();
	//ImGui::SetCursorScreenPos(ImVec2(p.x + 450, p.y + 12.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.02f, 0.02f, 0.02f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.02f, 0.02f, 0.02f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Text, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.368627f, 0.368627f, 0.368627f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50);
	ImGui::Button(ICON_FA_COG, ImVec2(30,30));
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(4);

	if (ImGui::IsItemClicked()) ImGui::OpenPopup(str_id);
}

void CrystalUI::toggle(const char* str_id, bool* v, std::string tooltip, bool no_win) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	#ifdef GEODE_IS_MACOS
		no_win = false;
	#endif

	ImVec4 regularColor;
	ImVec4 activeColor;
	if (no_win) {
		regularColor = ImVec4(0.85f, 0.85f, 0.85f, 0.25f);
		activeColor = ImVec4(0.85f, 0.85f, 0.85f, 0.25f);
		tooltip = "This mod is not available for Windows";
	} else {
		regularColor = *v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 0.0f);
		activeColor = *v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f);
	}

	float height = ImGui::GetFrameHeight() - 5;
	float width = height * 1.55f;
	float radius = height * 0.50f;
	float rounding = 0.25;

	draw_list->AddRectFilled(ImVec2(p.x, p.y + 5), ImVec2(p.x + ImGuiHelper::getWidth() - 10, p.y + (height * 2)), ImGui::GetColorU32(colors[ImGuiCol_WindowBg]), height * rounding);

	ImGui::InvisibleButton(str_id, ImVec2(width + 7, height));
	ImGui::SetItemAllowOverlap();
	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 15, p.y + 15));
	ImGui::TextColored(no_win ? ImVec4(1.0f, 1.0f, 1.0f, 0.5f) : (*v ? colors[ImGuiCol_ButtonActive] : ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), "%s", str_id);

	if (ImGui::IsItemClicked() && !no_win) *v = !*v;
	if (ImGui::IsItemHovered() && tooltip != "N/A") ImGui::SetTooltip("%s", tooltip.c_str());

	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 500, p.y + 12.5));
	CrystalUI::internalToggle((std::string(str_id) + "_toggle").c_str(), v, no_win);

	p = ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos(ImVec2(p.x, p.y + 10));
}

void CrystalUI::toggleWithMenu(const char* str_id, bool* v, std::string tooltip, bool no_win) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	#ifdef GEODE_IS_MACOS
		no_win = false;
	#endif

	ImVec4 regularColor;
	ImVec4 activeColor;
	if (no_win) {
		regularColor = ImVec4(0.85f, 0.85f, 0.85f, 0.25f);
		activeColor = ImVec4(0.85f, 0.85f, 0.85f, 0.25f);
		tooltip = "This mod is not available for Windows";
	} else {
		regularColor = *v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 0.0f);
		activeColor = *v ? colors[ImGuiCol_ButtonActive] : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	float height = ImGui::GetFrameHeight() - 5;
	float width = height * 1.55f;
	float radius = height * 0.50f;
	float rounding = 0.25;

	draw_list->AddRectFilled(ImVec2(p.x, p.y + 5), ImVec2(p.x + ImGuiHelper::getWidth() - 10, p.y + (height * 2)), ImGui::GetColorU32(colors[ImGuiCol_WindowBg]), height * rounding);

	ImGui::InvisibleButton(str_id, ImVec2(width + 7, height));
	ImGui::SetItemAllowOverlap();
	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 15, p.y + 15));
	ImGui::TextColored(activeColor, "%s", str_id);

	if (ImGui::IsItemClicked() && !no_win) *v = !*v;
	if (ImGui::IsItemHovered() && tooltip != "N/A") ImGui::SetTooltip("%s", tooltip.c_str());

	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 450, p.y + 12.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.02f, 0.02f, 0.02f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.02f, 0.02f, 0.02f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_Text, CrystalClient::VarToIV4("BGcolor") + ImVec4(0.368627f, 0.368627f, 0.368627f, 0.f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50);
	ImGui::Button(ICON_FA_COG, ImVec2(30,30));
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(4);

	if (ImGui::IsItemClicked() && !no_win) ImGui::OpenPopup(str_id);

	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 500, p.y + 12.5));
	CrystalUI::internalToggle((std::string(str_id) + "_toggle").c_str(), v);

	p = ImGui::GetCursorScreenPos();
	ImGui::SetCursorScreenPos(ImVec2(p.x, p.y + 10));
}

inline std::string decToHexa(float n) {
    char hexaDeciNum[2];

    int real = n;
 
    int i = 0;
    while (real != 0) {
        int temp = 0;
        temp = real % 16;
 
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        } else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
 
        real = real / 16;
    }
 
    std::string hexCode = "";
    if (i == 2) {
        hexCode.push_back(hexaDeciNum[0]);
        hexCode.push_back(hexaDeciNum[1]);
    } else if (i == 1) {
        hexCode = "0";
        hexCode.push_back(hexaDeciNum[0]);
    } else if (i == 0) {
        hexCode = "00";
    }  
 
    return hexCode;
}

void CrystalUI::colorPicker(const char* label, std::string name) {
	float col[4];
	std::sscanf(getSavedVar<std::string>(name).c_str(), "%2f%2f%2f", &col[0], &col[1], &col[2]);
	col[3] = 1.f; // alpha but we dont even store it so whatever

	ImGui::ColorEdit4(label, col, ImGuiColorEditFlags_NoInputs);

	std::string hexCode = "";
	hexCode += decToHexa(col[0]);
	hexCode += decToHexa(col[1]);
	hexCode += decToHexa(col[2]);

	*setSavedVar<std::string>(name) = hexCode;
}

void CrystalUI::textbox(const char* name, std::string* str) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	std::string newName = std::string("###") + name;
	char buf[255]{};
	strncpy(buf, str->c_str(), sizeof(buf) - 1);
	ImGui::PushStyleColor(7, ImVec4(0,0,0,0.25));
	ImGui::PushStyleVar(12, 0.f);
    ImGui::InputTextWithHint(newName.c_str(), name, buf, sizeof(buf));
	ImVec2 p = ImGui::GetCursorScreenPos();
	draw_list->AddRectFilled(ImVec2(p.x + 1, p.y - 3.f), ImVec2(p.x + ImGui::CalcItemWidth(), p.y - 5.f), ImGui::GetColorU32(CrystalClient::VarToIV4("lightColor")), 6);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
    *str = buf;
}

void CrystalUI::inputInt(const char* name, int* num) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImGui::PushStyleColor(7, ImVec4(0,0,0,0.25));
	ImGui::PushStyleVar(12, 0.f);
	ImGui::InputInt(name, num, 0);
	ImVec2 p = ImGui::GetCursorScreenPos();
	draw_list->AddRectFilled(ImVec2(p.x + 1, p.y - 3.f), ImVec2(p.x + ImGui::CalcItemWidth(), p.y - 5.f), ImGui::GetColorU32(CrystalClient::VarToIV4("lightColor")), 6);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void CrystalUI::inputFloat(const char* name, float* num) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImGui::PushStyleColor(7, ImVec4(0,0,0,0.25));
	ImGui::PushStyleVar(12, 0.f);
	ImGui::InputFloat(name, num, 0);
	ImVec2 p = ImGui::GetCursorScreenPos();
	draw_list->AddRectFilled(ImVec2(p.x + 1, p.y - 3.f), ImVec2(p.x + ImGui::CalcItemWidth(), p.y - 5.f), ImGui::GetColorU32(CrystalClient::VarToIV4("lightColor")), 6);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void CrystalUI::iconEffect(const char* categoryName, std::string saveName) {
	CrystalUI::toggleWithMenu(categoryName, setSavedVar<bool>(saveName));
	if (ImGui::BeginPopupModal(categoryName, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalUI::subToggleWithMenu("Static", setSavedVar<bool>(saveName + "_static"));
		if (ImGui::BeginPopupModal("Static", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			colorPicker("Static Color", saveName + "_static");
			if (ImGui::Button("Close")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		CrystalUI::subToggleWithMenu("Fade", setSavedVar<bool>(saveName + "_fade"));
		if (ImGui::BeginPopupModal("Fade", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			colorPicker("Fade Color 1", saveName + "_fade1");
			colorPicker("Fade Color 2", saveName + "_fade2");
			if (ImGui::Button("Close")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		CrystalUI::subToggle("Rainbow", setSavedVar<bool>(saveName + "_rainbow"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void CrystalUI::hotkey(const char* label) {
	ImGui::Text(label);
	ImGui::SameLine();
	if (waitingForKey) { ImGui::Button("Waiting for keypress..."); }
	//else { if (ImGui::Button(CCKeyboardDispatcher::keyToString(queuedKey), ImVec2(80, 20))) { waitingForKey = true; } }
}

void CrystalUI::subTab(std::string childName, ImVec2 childSize, std::vector<std::string> tabNames, int* selectedSubTab) {
	int length = tabNames.front().length();
	int strIndex = 1;
	for (int i = 1; i < tabNames.size(); i++) {
		if (length > tabNames.at(i).length()) {
			length = tabNames.at(i).length();
			strIndex = i;
		}
	}

	ImGui::BeginChild(childName.c_str(), childSize, true, ImGuiWindowFlags_HorizontalScrollbar);

	int minWidth = ImGuiHelper::getTextLength(tabNames.at(strIndex).c_str()).x;
	int maxWidth = 200;

	int btnWidth = (ImGuiHelper::getWidth() - ImGui::GetStyle().ItemSpacing.x * (tabNames.size())) / tabNames.size();
	int btnHeight = clamp(ImGuiHelper::getHeight(), 20.f, 60.f);
	btnWidth = (std::max)(minWidth, (std::min)(btnWidth, maxWidth));

	{
		ImGui::SetCursorPosX((childSize.x - btnWidth * tabNames.size() - ImGui::GetStyle().ItemSpacing.x) / 2);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	for (int i = 0; i < tabNames.size(); i++) {
		std::string it = tabNames.at(i);
		ImGui::PushStyleColor(ImGuiCol_Button, *selectedSubTab == i ? ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] : ImGui::GetStyle().Colors[ImGuiCol_Button]);
		ImGui::PushStyleColor(ImGuiCol_Text, *selectedSubTab == i ? ImGui::GetStyle().Colors[ImGuiCol_Text] : ImGui::GetStyle().Colors[ImGuiCol_Text]);
		ImGui::Button(it.c_str(), ImVec2(btnWidth, btnHeight));
		if (ImGui::IsItemClicked()) *selectedSubTab = i;
		ImGui::SameLine();
		ImGui::PopStyleColor(2);
	}
	ImGui::PopStyleVar();

	ImGui::EndChild();
}