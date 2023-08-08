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
using namespace Shortcuts;
using namespace Variables;
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

void CrystalClient::arrangeText(int arrayLength, PlayLayer* menulay, bool first) {
	auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

	auto ptr = static_cast<CCLabelBMFont*>(profile.displayNodes[arrayLength]);

	float tr = 0, tl = 0, br = 0, bl = 0, thisLabel;

	for (int i = 0; i < 15; i++) {
		if (profile.displays[i]) {
			switch (profile.displayPositions[i]) {
				case TR:
					if (arrayLength == i)
						thisLabel = tr;
					tr += 1.0f * profile.displayScaleF;
					break;
				case TL:
					if (arrayLength == i)
						thisLabel = tl;
					tl += 1.0f * profile.displayScaleF;
					break;
				case BR:
					if (arrayLength == i)
						thisLabel = br;
					br += 1.0f * profile.displayScaleF;
					break;
				case BL:
					if (arrayLength == i)
						thisLabel = bl;
					bl += 1.0f * profile.displayScaleF;
					break;
			}
		}
	}

	float height = 0, x = 0;

	switch (profile.displayPositions[arrayLength]) {
		case TR:
			height = size.height - 10 - (thisLabel * profile.displaySpaceF);
			x = size.width - 5;
			break;
		case TL:
			height = size.height - 10 - (thisLabel * profile.displaySpaceF);
			x = 5.0f;
			break;
		case BR:
			height = 10.0f + (thisLabel * profile.displaySpaceF);
			x = size.width - 5;
			break;
		case BL:
			height = 10.0f + (thisLabel * profile.displaySpaceF);
			x = 5.0f;
			break;
	}

	profile.displayNodes[arrayLength]->setPosition(x, height);

	if (arrayLength != 0) {
		profile.displayNodes[arrayLength]->setOpacity(50);
	}
	if (profile.displayScaleF < 0.1f || profile.displayScaleF > 1.5f)
		profile.displayScaleF = 1.0f;

	float sc = profile.displayScaleF * 0.45f;
	if (arrayLength == 0)
	{
		sc *= 1.8f;
		profile.displayNodes[arrayLength]->setPosition(x, height + 10);
	}

	profile.displayNodes[arrayLength]->setScale(sc);
	if (profile.displayOpacityF < 1)
		profile.displayOpacityF = 255;
	else if (profile.displayOpacityF > 255)
		profile.displayOpacityF = 255;
	profile.displayNodes[arrayLength]->setOpacity(profile.displayOpacityF);
	profile.displayNodes[arrayLength]->setAnchorPoint(profile.displayNodes[arrayLength]->getPositionX() > 284.5f
										? ccp(1.0f, profile.displayNodes[arrayLength]->getAnchorPoint().y)
										: ccp(0.0f, profile.displayNodes[arrayLength]->getAnchorPoint().y));

	if (first) {
		for (int d = 0; d < 15; d++) {
			menulay->addChild(profile.displayNodes[d], 1000);
		}
	}
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
	CrystalClient::ImExtendedToggleable("Hitbox Viewer", &Crystal::profile.hitboxes);
	if (ImGui::BeginPopupModal("Hitbox Viewer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Show Hitboxes on Death", &Crystal::profile.onDeath);
		CrystalClient::ImToggleable("Show Hitbox Trail", &Crystal::profile.drawTrail);
		CrystalClient::ImToggleable("Show Hitboxes in Editor", &Crystal::profile.inEditor);
		//CrystalClient::ImToggleable("Fill Hitboxes", &Crystal::profile.fillHitbox);
		//ImGui::InputFloat("Hitbox Fill Opacity", &Crystal::profile.fillOpacity);
		CrystalClient::ImToggleable("Coin Tracker", &Crystal::profile.coinFind);
		CrystalClient::ImToggleable("Show Trajectory [BETA]", &Crystal::profile.trajectory);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	/* CrystalClient::ImExtendedToggleable("Hitbox Multiplier", &Crystal::profile.hitboxMultiply);
	if (ImGui::BeginPopupModal("Hitbox Multiplier", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Solids Multiplier", &Crystal::profile.multiplySolids);
		ImGui::InputFloat("Hazard Multiplier", &Crystal::profile.multiplyHazards);
		ImGui::InputFloat("Special Multiplier", &Crystal::profile.multiplySpecial);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	} */
	CrystalClient::ImToggleable("No Progress Bar", &Crystal::profile.progressBar);
	CrystalClient::ImToggleable("Accurate Percentage", &Crystal::profile.accpercentage);
	CrystalClient::ImExtendedToggleable("Hide Attempts Label", &Crystal::profile.hideatts);
	if (ImGui::BeginPopupModal("Hide Attempts Label", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide in Normal Mode", &Crystal::profile.hidenormalatts);
		CrystalClient::ImToggleable("Hide in Practice Mode", &Crystal::profile.hidepracticeatts);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Practice Music Hack", &Crystal::profile.pracmusic);
	CrystalClient::ImToggleable("Hide Pause Menu", &Crystal::profile.hidepause);
	CrystalClient::ImToggleable("Ignore ESC", &Crystal::profile.ignoreESC);
	CrystalClient::ImToggleable("Confirm Quit", &Crystal::profile.confirmQuit);
	CrystalClient::ImToggleable("Auto LDM", &Crystal::profile.autoldm);
	CrystalClient::ImToggleable("Auto Song Downloader", &Crystal::profile.autoSong);
	CrystalClient::ImToggleable("Flipped Dual Controls", &Crystal::profile.flippedcontrol);
	CrystalClient::ImToggleable("Mirrored Dual Controls", &Crystal::profile.mirrorcontrol);
	CrystalClient::ImToggleable("StartPos Switcher", &Crystal::profile.startpos);
	CrystalClient::ImToggleable("Checkpoint Switcher", &Crystal::profile.checkpointswitch);
	CrystalClient::ImToggleable("Frame Stepper", &Crystal::profile.framestep);
	CrystalClient::ImToggleable("Load from Last Checkpoint", &Crystal::profile.lastCheckpoint);
	CrystalClient::ImToggleable("No Glow", &Crystal::profile.noglow);
	CrystalClient::ImToggleable("No Mirror Effect", &Crystal::profile.mirror);
	CrystalClient::ImToggleable("Layout Mode", &Crystal::profile.layout);
	CrystalClient::ImExtendedToggleable("AutoClicker", &Crystal::profile.autoclick);
	if (ImGui::BeginPopupModal("AutoClicker", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputInt("Push on Frame", &profile.ACpushframe);
		ImGui::InputInt("Release on Frame", &profile.ACrelframe);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Display", NULL, window_flags);
	CrystalClient::ImToggleable("Testmode Label", &profile.testmode);
	ImGui::InputFloat("Display Scale", &profile.displayScaleF);
	ImGui::InputFloat("Display Opacity", &profile.displayOpacityF);
	ImGui::InputFloat("Display Spacing", &profile.displaySpaceF);
	CrystalClient::ImExtendedToggleable("Cheat Indicator", &Crystal::profile.displays[0]);
	if (ImGui::BeginPopupModal("Cheat Indicator", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[0], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[0]);
		//ImGui::InputFloat("Scale", &profile.displayScale[0]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Custom Message", &Crystal::profile.displays[1]);
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		strcpy(profile.messageBuffer, profile.message.c_str());
		ImGui::InputTextWithHint("Message", "Custom Message", profile.messageBuffer, IM_ARRAYSIZE(profile.messageBuffer));
		profile.message = profile.messageBuffer;
		ImGui::Combo("Position", (int *)&profile.displayPositions[1], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[1]);
		//ImGui::InputFloat("Scale", &profile.displayScale[1]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("CPS display", &Crystal::profile.displays[2]);
	if (ImGui::BeginPopupModal("CPS display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Green Pulse On Click", &Crystal::profile.tclicks);
		CrystalClient::ImToggleable("Show Clicks", &Crystal::profile.sclicks);
		CrystalClient::ImToggleable("Only Clicks", &Crystal::profile.oclicks);
		CrystalClient::ImToggleable("Reset Clicks Every Attempt", &Crystal::profile.rclicks);
		ImGui::Combo("Position", (int *)&profile.displayPositions[2], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[2]);
		//ImGui::InputFloat("Scale", &profile.displayScale[2]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", &Crystal::profile.displays[3]);
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[3], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[3]);
		//ImGui::InputFloat("Scale", &profile.displayScale[3]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Last Death", &Crystal::profile.displays[4]);
	if (ImGui::BeginPopupModal("Last Death", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[4], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[4]);
		//ImGui::InputFloat("Scale", &profile.displayScale[4]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Attempts", &Crystal::profile.displays[5]);
	if (ImGui::BeginPopupModal("Attempts", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Attempts", &Crystal::profile.tattoo);
		ImGui::Combo("Position", (int *)&profile.displayPositions[5], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[5]);
		//ImGui::InputFloat("Scale", &profile.displayScale[5]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", &Crystal::profile.displays[6]);
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Total Jumps", &Crystal::profile.tjumps);
		CrystalClient::ImToggleable("Attempt Jumps", &Crystal::profile.ajumps);
		ImGui::Combo("Position", (int *)&profile.displayPositions[6], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[6]);
		//ImGui::InputFloat("Scale", &profile.displayScale[6]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Run From", &Crystal::profile.displays[7]);
	if (ImGui::BeginPopupModal("Run From", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[7], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[7]);
		//ImGui::InputFloat("Scale", &profile.displayScale[7]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Best Run", &Crystal::profile.displays[8]);
	if (ImGui::BeginPopupModal("Best Run", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[8], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[8]);
		//ImGui::InputFloat("Scale", &profile.displayScale[8]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", &Crystal::profile.displays[9]);
	if (ImGui::BeginPopupModal("Noclip Accuracy", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", &Crystal::profile.redDying);
		ImGui::Combo("Position", (int *)&profile.displayPositions[9], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[9]);
		//ImGui::InputFloat("Scale", &profile.displayScale[9]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Noclip Deaths", &Crystal::profile.displays[10]);
	if (ImGui::BeginPopupModal("Noclip Deaths", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Red Pulse on Death", &Crystal::profile.redDeath);
		ImGui::Combo("Position", (int *)&profile.displayPositions[10], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[10]);
		//ImGui::InputFloat("Scale", &profile.displayScale[10]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Level Name and ID", &Crystal::profile.displays[11]);
	if (ImGui::BeginPopupModal("Level Name and ID", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Hide ID", &Crystal::profile.hideID);
		CrystalClient::ImToggleable("Show Author", &Crystal::profile.author);
		ImGui::Combo("Position", (int *)&profile.displayPositions[11], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[11]);
		//ImGui::InputFloat("Scale", &profile.displayScale[11]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Macro Status", &Crystal::profile.displays[12]);
	if (ImGui::BeginPopupModal("Macro Status", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Combo("Position", (int *)&profile.displayPositions[12], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[12]);
		//ImGui::InputFloat("Scale", &profile.displayScale[12]);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clock", &Crystal::profile.displays[13]);
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("12-hour format", &Crystal::profile.ipm);
		CrystalClient::ImToggleable("In-Attempt Time", &Crystal::profile.iat);
		CrystalClient::ImToggleable("In-Level Time", &Crystal::profile.ilt);
		CrystalClient::ImToggleable("In-Game Time", &Crystal::profile.igt);
		ImGui::Combo("Position", (int *)&profile.displayPositions[13], profile.displayOptions, IM_ARRAYSIZE(profile.displayOptions));
		//ImGui::InputFloat("Opacity", &profile.displayOpacity[13]);
		//ImGui::InputFloat("Scale", &profile.displayScale[13]);
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
	CrystalClient::ImToggleable("Anticheat Bypass", &profile.anticheat);
	CrystalClient::ImToggleable("Unlock All", &profile.unlockAll);
	CrystalClient::ImToggleable("Scale Hack", &profile.scalehack);
	CrystalClient::ImToggleable("Object Limit Bypass", &profile.objlimit);
	CrystalClient::ImToggleable("Custom Object Object Limit Bypass", &profile.customobjlimit);
	CrystalClient::ImToggleable("Verify Bypass", &profile.verify);
	CrystalClient::ImToggleable("Copy Bypass", &profile.copy);
	CrystalClient::ImToggleable("Editor Zoom Bypass", &profile.editorZoom);
	CrystalClient::ImToggleable("Level Edit Bypass", &profile.levelEdit);
	CrystalClient::ImToggleable("Load Failed Bypass", &profile.loadfail);
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
	//ImGui::PushItemWidth(100);
	//ImGui::InputInt("##Draw Divide", &target_fps, 0, 1000);
	//ImGui::PopItemWidth();
	//ImGui::SameLine();
	//CrystalClient::ImToggleable("Draw Divide", &drawDivide);
    ImGui::InputFloat("Speedhack", &profile.speed);
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(profile.speed);
	CrystalClient::ImExtendedToggleable("Safe Mode", &profile.safeMode);
	if (ImGui::BeginPopupModal("Safe Mode", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Auto Safe Mode", &profile.autoSafeMode);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Lock Cursor", &profile.lockCursor);
	CrystalClient::ImToggleable("Transparent BG", &profile.transparentBG);
	CrystalClient::ImToggleable("Transparent Lists", &profile.translists);
	CrystalClient::ImToggleable("Better BG", &profile.betterbg);
	CrystalClient::ImToggleable("Demon List Button", &profile.buttonDL);
	CrystalClient::ImToggleable("Challenge List Button", &profile.buttonCL);
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]", NULL, window_flags);
    CrystalClient::ImToggleable("Record", &profile.record);
	ImGui::SameLine();
    CrystalClient::ImToggleable("Replay", &profile.replay);
	CrystalClient::ImToggleable("ClickBot", &profile.clickBot);
	ImGui::SameLine();
	CrystalClient::ImToggleable("Delta Lock", &profile.deltaLock);
	ImGui::InputFloat("ClickBot Volume", &profile.CBvolume);
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
	//CrystalClient::ImToggleable("Enable Macro Buffer", &macroBuffer);
	//if (ImGui::Button("Clear Macro Buffer")) {
		//newQueue.clear();
	//}
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
    ImGui::Combo("Keybind", &currentKey, keybindings, IM_ARRAYSIZE(keybindings));
    ImGui::Combo("Mod to Switch", &currentMod, modbindings, IM_ARRAYSIZE(modbindings));
    if (ImGui::Button("Add Keybind")) {
        keybinds.push_back({currentKey, currentMod});
    }
	for (size_t i = 0; i < keybinds.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text("%s", modbindings[keybinds[i].activeMod]);
		ImGui::SameLine();
		ImGui::Text("%s", keybindings[keybinds[i].activeKey]);
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			keybinds.erase(keybinds.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
	ImGui::Begin("Variable Changer", NULL, window_flags);
    ImGui::Combo("Variable", &currentVar, playerVars, IM_ARRAYSIZE(playerVars));
	ImGui::InputFloat("Value", &currentValue);
    if (ImGui::Button("Add Change")) {
        variables.push_back({currentVar, currentValue});
    }
	for (size_t i = 0; i < variables.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text("%s", playerVars[variables[i].activeVar]);
		ImGui::SameLine();
		ImGui::Text("%s", std::to_string(variables[i].activeValue).c_str());
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			variables.erase(variables.begin() + i);
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

class $modify(HitboxLevelEditorLayer, LevelEditorLayer) {
    static inline tulip::HitboxNode* drawer;
	static inline bool paused = false;

	bool init(GJGameLevel* lvl) {
		drawer = tulip::HitboxNode::create();
		auto ret = LevelEditorLayer::init(lvl);
		drawer->setVisible(false);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		// i hate bad practices
		drawer->m_drawTrail = Crystal::profile.drawTrail;
		s_noLimitTrail = false;

		for (int s = 0; s < profile.regularPath.size(); s++) {
			drawer->addToPlayer1Queue(profile.regularPath[s]);
		}
		this->updateHitboxEditor();

		if (Crystal::profile.inEditor) drawer->setVisible(true);
		return ret;
	}
	bool checkCollisions(PlayerObject* player, float uhh) {
		auto ret = LevelEditorLayer::checkCollisions(player, uhh);
		if (player == m_player1) {
			drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
		return ret;
	}
	void onPlaytest() {
		LevelEditorLayer::onPlaytest();
		drawer->drawForPlayer1(m_player1);
		this->updateHitboxEditor();
		if (Crystal::profile.inEditor) {
			drawer->setVisible(true);
		}
	}
	void onPausePlaytest() {
		LevelEditorLayer::onPausePlaytest();
		paused = true;
		this->updateHitboxEditor();
	}
	void updateHitboxEditor() {
		if (!paused) return;
		if (s_noLimitTrail) drawer->m_noLimitTrail = true;

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				drawer->drawForObject(obj);
			}
		}
	}
	void onResumePlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
		LevelEditorLayer::onResumePlaytest();
	}
	void onStopPlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
        drawer->clearQueue();
        if (Crystal::profile.inEditor) {
			drawer->setVisible(true);
		}
        LevelEditorLayer::onStopPlaytest();
    }

	void update(float dt) {
		drawer->clear();
		LevelEditorLayer::update(dt);

		if (m_player1) {
			if (Crystal::profile.inEditor) drawer->drawForPlayer1(m_player1);
			
		}
		if (m_player2) {
			if (Crystal::profile.inEditor) drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				if (Crystal::profile.inEditor) drawer->drawForObject(obj);
			}
		}
	}
};

class $modify(EditorUI) {
	void keyDown(enumKeyCodes code) {
		EditorUI::keyDown(code);
		if (s_drawer) {
			s_drawer->clear();
			for (int s = 0; s < profile.regularPath.size(); s++) {
				s_drawer->addToPlayer1Queue(profile.regularPath[s]);
			}
			if (GJBaseGameLayer::get()->m_player1) {
				s_drawer->drawForPlayer1(GJBaseGameLayer::get()->m_player1);
			}
			if (GJBaseGameLayer::get()->m_player2) {
				s_drawer->drawForPlayer2(GJBaseGameLayer::get()->m_player2);
			}

			float xp = GJBaseGameLayer::get()->m_player1->getPositionX();

			for (int s = GJBaseGameLayer::get()->sectionForPos(xp) - 5; s < GJBaseGameLayer::get()->sectionForPos(xp) + 6; ++s) {
				if (s < 0) continue;
				if (s >= GJBaseGameLayer::get()->m_sectionObjects->count()) break;
				auto section = static_cast<CCArray*>(GJBaseGameLayer::get()->m_sectionObjects->objectAtIndex(s));
				for (size_t i = 0; i < section->count(); ++i) {
					auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

					if (s_onlyHitboxes) obj->setOpacity(0);

					if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
					if (!obj->m_active) continue;

					s_drawer->drawForObject(obj);
				}
			}
		} 
	}

	void scrollWheel(float y, float x) {
		auto kb = CCDirector::sharedDirector()->getKeyboardDispatcher();
		//if (kb->getShiftKeyPressed() && scrollzoom) {
			//auto zoom = this->m_editorLayer->m_objectLayer->getScale();
			//zoom = std::pow(std::numbers::e, std::log(std::max(zoom, 0.001f)) - y * 0.025f);
			//this->updateZoom(zoom);
		//} else {
			EditorUI::scrollWheel(y, x);
		//}
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
	
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
		}

		if (PlayLayer::get() && gameStarted && (profile.TPSbypass || profile.FPSbypass || profile.deltaLock || profile.replay || profile.record || profile.renderer)) {
			auto dir = CCDirector::sharedDirector();

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

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (profile.verify) {
			ok->m_isVerified = true;
		}	
		if (Crystal::profile.autoldm) {
			ok->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(ok);
	}

	bool init(GJGameLevel* ed) {
        EditLevelLayer::init(ed);

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(GJGameLevel) {
	void savePercentage(int percentage, bool practice, int clicks, int attemptTime, bool vfDChk) {
		if (profile.safeMode && !profile.autoSafeMode) return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, false);
		if (profile.safeMode && profile.autoSafeMode && profile.displayNodes[0]->getColor() == ccc3(255,0,0)) return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, false);
		if (profile.anticheat) return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, true);
		else return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, vfDChk);
	}
};

class $modify(GameManager) {
    bool isIconUnlocked(int a, IconType b) {
        auto icon = GameManager::isIconUnlocked(a,b);
        if (profile.unlockAll) {
            return true;
        } else {
            return icon;
        }
    } 

    bool isColorUnlocked(int a, bool b) {
        auto color = GameManager::isColorUnlocked(a,b);
        if (profile.unlockAll) {
            return true;
        } else {
            return color;
        }
    }
};

class $(MyGameObject, GameObject) {
	CCSprite* m_backgroundLayer;
	bool m_realVisible;
	cocos2d::_ccColor3B m_realColor;

	void setVisible(bool v) {
		if (Crystal::profile.layout) {
			m_fields->m_realVisible = v;

			if (m_objectType == GameObjectType::Decoration) {
				GameObject::setVisible(false);
			} else {
				GameObject::setVisible(v); // for CCParticleSystem (idk why)
				GameObject::setVisible(true);
			}
		} else GameObject::setVisible(v);
	}

	void revertVisibility() {
		setVisible(m_fields->m_realVisible);
	}

	void setOpacity(unsigned char g) {
		GameObject::setOpacity(g);

		if (Crystal::profile.layout && m_objectType != GameObjectType::Decoration) {
			CCSpritePlus::setOpacity(255);
			if (m_glowSprite)
				m_glowSprite->setOpacity(255);
		}
	}

	void setGlowColor(cocos2d::_ccColor3B const& col) {
		if (Crystal::profile.layout) {
			GameObject::setGlowColor(ccc3(255, 255, 255));
		} else {
			GameObject::setGlowColor(col);
		}
	}

	void setObjectColor(const cocos2d::ccColor3B& cor) {
		if (Crystal::profile.layout && m_objectType != GameObjectType::Decoration) {
			GameObject::setObjectColor(ccc3(255, 255, 255));
		} else {
			GameObject::setObjectColor(cor);
		}
	}

    virtual void update(float time2) {
		if (Crystal::profile.noglow) {
			m_isGlowDisabled = true;
		}
		if (Crystal::profile.instantdeath) {
			m_particleAdded = true;
   			m_hasParticles = false;
		}
		GameObject::update(time2);
	}

	void activatedByPlayer(GameObject* other) {
		if (profile.trajectory && s_drawer->m_pIsSimulation) {
			if (this->getType() != GameObjectType::Slope &&
				this->getType() != GameObjectType::Solid &&
				this->getType() != GameObjectType::GravityPad &&
				this->getType() != GameObjectType::PinkJumpPad && this->getType() != GameObjectType::RedJumpPad &&
				this->getType() != GameObjectType::YellowJumpPad && this->getType() != GameObjectType::DashRing &&
				this->getType() != GameObjectType::DropRing && this->getType() != GameObjectType::GravityDashRing &&
				this->getType() != GameObjectType::GravityRing && this->getType() != GameObjectType::GreenRing &&
				this->getType() != GameObjectType::PinkJumpRing && this->getType() != GameObjectType::RedJumpRing &&
				this->getType() != GameObjectType::YellowJumpRing && this->getType() != GameObjectType::Special &&
				this->getType() != GameObjectType::CollisionObject && this->getType() != GameObjectType::Hazard &&
				this->getType() != GameObjectType::InverseGravityPortal &&
				this->getType() != GameObjectType::NormalGravityPortal &&
				this->getType() != GameObjectType::TeleportPortal &&
				this->getType() != GameObjectType::MiniSizePortal &&
				this->getType() != GameObjectType::RegularSizePortal) 
			{
				return;
			}
		}
		GameObject::activatedByPlayer(other);
	}
};

class $modify(LevelTools) {
	static bool verifyLevelIntegrity(gd::string mg, int de) {
		if (profile.loadfail || profile.levelEdit) return true;
		return LevelTools::verifyLevelIntegrity(mg, de);
	}
};

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		currentMacro.setPushingData(true, b);
        if (profile.clickBot) {
            if (!Clickbot::inited) {
                FMOD::System_Create(&Clickbot::system);
                Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, nullptr);
                Clickbot::inited = true;
            }

            Clickbot::now = std::chrono::system_clock::now();
            Clickbot::cycleTime = Clickbot::now - Clickbot::start;
            if (Clickbot::cycleTime.count() < 0.5f) {
                std::string path = Clickbot::pickRandomSoftClick();
                Clickbot::start = std::chrono::system_clock::now();
                std::cout << Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
            } else {
                std::string path = Clickbot::pickRandomClick();
                Clickbot::start = std::chrono::system_clock::now();
                Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
            }
            
            Clickbot::system->playSound(Clickbot::clickSound, nullptr, true, &Clickbot::clickChannel);
            Clickbot::clickChannel->setVolume((float)(profile.CBvolume / 100));
            Clickbot::clickChannel->setPaused(false);
            Clickbot::system->update();
        }
		if (Crystal::profile.flippedcontrol) {
			if (!b) GJBaseGameLayer::pushButton(i,true);
			if (b) GJBaseGameLayer::pushButton(i,false);
		} else if (Crystal::profile.mirrorcontrol) {
			GJBaseGameLayer::pushButton(i,true);
			GJBaseGameLayer::pushButton(i,false);
		} else {
			GJBaseGameLayer::pushButton(i,b);
		}
		clickscount++;
		click_count++;
		holding = true;
	}

	void releaseButton(int i, bool b) {
		currentMacro.setPushingData(false, b);
		if (profile.clickBot) {
			if (Clickbot::cycleTime.count() < 0.5f) {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			} else {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			}
			
			
			Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
			Clickbot::releaseChannel->setVolume((float)(profile.CBvolume / 100));
			Clickbot::releaseChannel->setPaused(false);
			Clickbot::system->update();
		}
        if (Crystal::profile.flippedcontrol) {
			if (!b) GJBaseGameLayer::releaseButton(i,true);
			if (b) GJBaseGameLayer::releaseButton(i,false);
		} else if (Crystal::profile.mirrorcontrol) {
			GJBaseGameLayer::releaseButton(i,true);
			GJBaseGameLayer::releaseButton(i,false);
		} else {
			GJBaseGameLayer::releaseButton(i,b);
		}

		holding = false;
	}
};

class $modify(HardStreak) {
	void addPoint(cocos2d::CCPoint point) {
		if (profile.trajectory && s_drawer->m_pIsSimulation) return;
		HardStreak::addPoint(point);
	}
};

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		auto layer = LevelInfoLayer::create(g);
		if (profile.copy) {
			g->m_password = 1;
		}

		if (Crystal::profile.autoldm) {
			g->m_lowDetailModeToggled = true;
		}

		return layer;
	}

	bool init(GJGameLevel* level) {
        LevelInfoLayer::init(level);
        
        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
 
    }
};

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (profile.hidepause) pause->setVisible(false);
		if (Crystal::profile.levelEdit) {
			auto editorSprite = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
			auto menu = static_cast<CCMenu*>(pause->getChildByID("center-button-menu"));
			auto editorButton = CCMenuItemSpriteExtra::create(editorSprite, pause, menu_selector(PauseLayer::goEdit));

			if (menu->getChildrenCount() != 5) {
				editorButton->setPosition({-212.25f, 0.0f});
				editorButton->setScale(0.8f);
				editorButton->setAnchorPoint({0.5f, 0.5f});

				menu->setPosition({325.0f, 130.0f});
				menu->addChild(editorButton);
				menu->updateLayout();
			}
		}
		return pause;
	}

	void keyDown(cocos2d::enumKeyCodes key) {
		if (key == KEY_Escape) {
			if (!Crystal::profile.ignoreESC) {
				PauseLayer::keyDown(key);
			}
		} else {
			PauseLayer::keyDown(key);
		}
	}
};

class $modify(PlayerObject) {
	void addAllParticles() {
		if (!Crystal::profile.instantdeath) {
			PlayerObject::addAllParticles();
		}
	}
	void playerDestroyed(bool idk) {
		PlayerObject::playerDestroyed(idk);
		s_drawOnDeath = true;
        if (Crystal::profile.instantdeath) {
			PlayLayer::get()->resetLevel();
		}
		if (Crystal::profile.pracmusic) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
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
			g_startPosText->setString(label.c_str());
		}
		if (profile.record) currentMacro.createCheckpointData();
		return cpo;
	}
};

class $modify(Main, PlayLayer) {
    void updateIndex(bool increment) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		auto win_size = CCDirector::sharedDirector()->getWinSize();

		if (m_isPracticeMode && profile.checkpointswitch && (!m_isTestMode && !CCDirector::sharedDirector()->getKeyboardDispatcher()->getShiftKeyPressed())) {
			if (increment) {
				g_checkpointIndex++;
			} else {
				g_checkpointIndex--;
			}

			if (g_checkpointIndex == g_checkpoints.size()) {
				g_checkpointIndex = -1;
			} else if (g_checkpointIndex < -1) {
				g_checkpointIndex = g_checkpoints.size() - 1;
			}

			auto label = std::to_string(g_checkpointIndex + 1) + "/" + std::to_string(g_checkpoints.size());
			g_startPosText->setString(label.c_str());

			if (g_checkpointIndex == -1) {
				m_startPosCheckpoint = nullptr;
				m_playerStartPosition = ccp(0, 105);
			} else {
				m_startPosCheckpoint = g_checkpoints[g_checkpointIndex].first;
				m_playerStartPosition = g_checkpoints[g_checkpointIndex].second;
			}
		}

		if (m_isTestMode && profile.startpos) {
			if (increment) {
				g_startPosIndex++;
			} else {
				g_startPosIndex--;
			}

			if (g_startPosIndex == g_startPoses.size()) {
				g_startPosIndex = -1;
			} else if (g_startPosIndex < -1) {
				g_startPosIndex = g_startPoses.size() - 1;
			}

			auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
			g_startPosText->setString(label.c_str());

			if (m_isTestMode) {
				m_startPosCheckpoint = nullptr;
				if (g_startPosIndex == -1) {
					m_startPos = nullptr;
					m_playerStartPosition = ccp(0, 105);
				} else {
					m_startPos = g_startPoses[g_startPosIndex].first;
					m_playerStartPosition = g_startPoses[g_startPosIndex].second;
				}
			}
		}

		resetLevel();
	}

    void addObject(GameObject* g) {
		if (Crystal::profile.noglow) g->m_isGlowDisabled = true;
		PlayLayer::addObject(g);
		SPs.push_back(reinterpret_cast<StartPosObject*>(g));
		if ((g->m_objectID == 1329 || g->m_objectID == 142) && profile.coinFind) coins.push_back(g);
		if (Crystal::profile.startpos) {
			if (g->m_objectID == 31) {
				g->retain();
				g_startPoses.push_back({reinterpret_cast<StartPosObject*>(g), g->getPosition()});
				g_startPosIndex += 1;
				auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
				g_startPosText->setString(label.c_str());
			}
		}
	}	

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

    void resetLevel() {
		drawer->m_pDieInSimulation = false;
		drawer->m_pIsSimulation = false;
		
		if (profile.bestRun) {
			bestEnd2 = (m_player1->getPositionX() / m_levelLength) * 100;
		}
        if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();
		
		PlayLayer::resetLevel();

		if (profile.replay || profile.record) currentMacro.resetActions(profile.record);

		
		if (profile.cheatIndicate) {
			bad = "Not Cheating";
			g_cheating->setColor(ccc3(0,255,0));
		}

		if (Crystal::profile.rclicks) {
			clickscount = 0;
		}

		if (profile.displays[2]) {
			click_count = 0;
			click_time_sum = 0.f;
		}

		if (profile.displays[6]) {
			m_attemptJumpCount = 0;
		}
		
		if (profile.displays[7]) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from %.0lf%%", start);
			profile.displayNodes[7]->setString(str);
		}
		
		if (profile.displays[8]) {
			bestStart2 = (m_player1->getPositionX() / m_levelLength) * 100;
			if ((bestEnd2 - bestStart2) > (bestEnd - bestStart)) {
				bestStart = bestStart2;
				bestEnd = bestEnd2;
			}
			display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);
			profile.displayNodes[8]->setString(display.c_str());
		}
		
	}
/*
    void destroyPlayer(PlayerObject* p, GameObject* g) {
		
		if (profile.trajectory && drawer->shouldInterrumpHooks(p)) {
			drawer->m_pDieInSimulation = true;
			return;
		}
		
	}
*/
    void fullReset() {
		if (Crystal::profile.lastCheckpoint && m_isPracticeMode) {
			loadLastCheckpoint();
			resetLevel();
		} else {
			PlayLayer::fullReset();
		}
	}

    void checkCollisions(PlayerObject* p, float g) {
		if (profile.anticheat) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
			m_inlineCalculatedKickTime = 0.0;
			m_accumulatedKickCounter = 0;
			m_kickCheckDeltaSnapshot = (float)std::time(nullptr);
		}

        if (Crystal::profile.autoclick) {
            clickframe++;
            if (clickframe == Crystal::profile.ACpushframe) {
                GJBaseGameLayer::get()->pushButton(1, true);
            }
            if (clickframe >= (Crystal::profile.ACpushframe + Crystal::profile.ACrelframe)) {
                GJBaseGameLayer::get()->releaseButton(1, true);
                clickframe = 0;
            }
        }

        PlayLayer::checkCollisions(p, g);

		for (int d = 0; d < 15; d++) {
			profile.displayNodes[d]->setVisible(profile.displays[d]);
			CrystalClient::get()->arrangeText(d, this, false);
		}

        if (p == m_player1) {
            drawer->addToPlayer1Queue(m_player1->getObjectRect());
            if (profile.replay && (int)(m_time * 60) != lastMacroTime) {
				profile.regularPath.push_back(m_player1->getObjectRect());
				lastMacroTime = (int)(m_time * 60);
			}
        }
        if (p == m_player2) {
            drawer->addToPlayer2Queue(m_player2->getObjectRect());
        }
	}

    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		if (Crystal::profile.accpercentage) {
			if (percent > 100.00) {
				percent = 100.00;
			}
			char str[64];
			sprintf(str, "%.2lf%%", percent);
			m_percentLabel->setString(str);
		}
	}

    CGImageRef CGImageFromCCImage(CCImage* img) {
		float width = img->getWidth();
		float height = img->getHeight();
		int dataLen = width * height * 4;

		CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, img->getData(), dataLen, NULL);


		return CGImageCreate(
			width, height, 
			8, 8 * 4, width * 4, 
			CGColorSpaceCreateDeviceRGB(), 
			kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedLast, 
			provider,   // data provider
			NULL,       // decode
			true,        // should interpolate
			kCGRenderingIntentDefault
		);
	}

	bool CGImageWriteToFile(CGImageRef image) {
		std::stringstream newthing;
		newthing << (std::string)geode::Mod::get()->getConfigDir();
		newthing << "/Amethyst/Renderer/Frames/";
  		newthing << "frame_";
		newthing << std::setw(4) << std::setfill('0') << std::to_string(ss);
		newthing << ".png";
		std::string name = newthing.str();

		ss++;

		CFStringRef file = CFStringCreateWithCString(kCFAllocatorDefault,
		name.c_str(),
		kCFStringEncodingMacRoman);
		CFStringRef type = CFSTR("public.png");
		CFURLRef urlRef = CFURLCreateWithFileSystemPath( kCFAllocatorDefault, file, kCFURLPOSIXPathStyle, false );
		CGImageDestinationRef destination = CGImageDestinationCreateWithURL( urlRef, kUTTypePNG, 1, NULL );
		CGImageDestinationAddImage( destination, image, NULL );
		CGImageDestinationFinalize( destination );
		if (!destination) {
			return false;
		}

		CGImageDestinationAddImage(destination, image, nil);

		if (!CGImageDestinationFinalize(destination)) {
			CFRelease(destination);
			return false;
		}

		CFRelease(destination);
		return true;
	}

	void captureScreen() {
		auto size = CCDirector::sharedDirector()->getWinSize();
		auto renderer = CCRenderTexture::create(size.width, size.height, cocos2d::kCCTexture2DPixelFormat_RGBA8888);

		renderer->begin();
		if (static_cast<CCNode*>(PlayLayer::get())->getChildrenCount()) {
			CCArrayExt<CCNode*> children = this->getChildren();
			for (auto* child : children) {
				using namespace std::literals::string_view_literals;
				if ((typeinfo_cast<CCLabelBMFont*>(child) && typeinfo_cast<CCLabelBMFont*>(child)->getString() == "Testmode"sv) || child->getZOrder() == 1000) {
					//label->setVisible(false);
					//break;
					//do nothing
				} else {
					child->visit();
				}
			}
		}
		//static_cast<cocos2d::CCNode*>(PlayLayer::get())->visit();
		renderer->end();

		auto img = renderer->newCCImage(true);
		CGImageWriteToFile(CGImageFromCCImage(img));    
	}

	void Press(int key) {
		// Create an HID hardware event source
		CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

		// Create a new keyboard key press event
		CGEventRef evt = CGEventCreateKeyboardEvent(src, (CGKeyCode) key, true);

		// Post keyboard event and release
		CGEventPost (kCGHIDEventTap, evt);
		CFRelease (evt); CFRelease (src);
	}

	void Release(int key) {
		// Create an HID hardware event source
		CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

		// Create a new keyboard key release event
		CGEventRef evt = CGEventCreateKeyboardEvent(src, (CGKeyCode) key, false);

		// Post keyboard event and release
		CGEventPost (kCGHIDEventTap, evt);
		CFRelease (evt); CFRelease (src);
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

		CGEventRef ourEvent = CGEventCreate(NULL);
		auto point = CGEventGetLocation(ourEvent);
		CFRelease(ourEvent);

		if (!ImGuiCocos::get().isVisible() && Crystal::profile.lockCursor && !m_hasCompletedLevel) CGWarpMouseCursorPosition(point);

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

		if (profile.displays[0]) {
			bad = ".";
			if (profile.noclip || profile.speed < 1 || Crystal::profile.mirror || Crystal::profile.framestep || Crystal::profile.autoclick || Crystal::profile.layout || Crystal::profile.record || Crystal::profile.replay || Crystal::profile.FPS > 360.0 || Crystal::profile.TPS > 360.0) {
				profile.displayNodes[0]->setColor(ccc3(255,0,0));
			} else {
				profile.displayNodes[0]->setColor(ccc3(0,255,0));
			}

			profile.displayNodes[0]->setString(bad.c_str());
		}
		if (profile.displays[1]) {
			profile.displayNodes[1]->setString(profile.messageBuffer);
		}
		if (profile.displays[2]) {
			const auto know = std::chrono::high_resolution_clock::now();

			const std::chrono::duration<float> dif = know - previous;
			click_time_sum += dif.count();

			std::string fixy = "/" + std::to_string(clickscount);
			std::string displayC = std::to_string(clickscount);
			std::string disply = cipy + fixy;
			std::string dasply = cipy + " CPS";

			//if (std::chrono::duration<float>(know - last).count() > 1.0f) {
				last = know;
				const auto cps = static_cast<int>(std::roundf(static_cast<float>(click_count) / m_time));
				click_time_sum = 0.f;
				//click_count = 0;
			
				cipy = std::to_string(cps);
			//}

			if (holding && Crystal::profile.tclicks) {
				profile.displayNodes[2]->setColor(ccc3(0, 255, 0));
			} else {
				profile.displayNodes[2]->setColor(ccc3(255, 255, 255));
			}

			if (Crystal::profile.sclicks) {
				profile.displayNodes[2]->setString(disply.c_str());
			} else if (Crystal::profile.oclicks) {
				profile.displayNodes[2]->setString(displayC.c_str());
			} else {
				profile.displayNodes[2]->setString(dasply.c_str());
			}

			previous = know;
		}
		if (profile.displays[3]) {
			const auto now = std::chrono::high_resolution_clock::now();

			const std::chrono::duration<float> diff = now - previous_frame;
			frame_time_sum += diff.count();
			frame_count++;

			if (std::chrono::duration<float>(now - last_update).count() > 1.0f) {
				last_update = now;
				const auto fps = static_cast<int>(std::roundf(static_cast<float>(frame_count) / frame_time_sum));
				frame_time_sum = 0.f;
				frame_count = 0;
				profile.displayNodes[3]->setString((std::to_string(fps) + " FPS").c_str());
			}

			previous_frame = now;
		}
		if (profile.displays[4]) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death: %.0lf%%", start);
			profile.displayNodes[4]->setString(str);
		}
		if (profile.displays[5]) {
			if (Crystal::profile.tattoo) {
				std::string at = "Global Atts: " + std::to_string(m_level->m_attempts);
				profile.displayNodes[5]->setString(at.c_str());
			} else {
				auto work = m_currentAttempt;
				char str[64];
				sprintf(str, "Attempts: %0d", work);
				profile.displayNodes[5]->setString(str);
			}
		}
		if (profile.displays[6]) {
			std::string nd = "Jumps: " + std::to_string(m_jumpCount);
			std::string ed = "Total Jumps: " + std::to_string(m_level->m_jumps);
			std::string ad = "Jumps: " + std::to_string(m_attemptJumpCount);

			if (Crystal::profile.ajumps) {
				profile.displayNodes[6]->setString(ad.c_str());
			} else if (Crystal::profile.tjumps) {
				profile.displayNodes[6]->setString(ed.c_str());
			} else {
				profile.displayNodes[6]->setString(nd.c_str());
			}
		}
		if (profile.displays[9]) {
			char ok[20];
            auto accu = (float)(frames - noclipped_frames) / (float)frames;
            sprintf(ok, "%.2f%%", accu * 100);
            profile.displayNodes[9]->setString(ok);

			if (Crystal::profile.redDying && dying) {
				profile.displayNodes[9]->setColor(ccc3(255, 0, 0));
			} else {
				profile.displayNodes[9]->setColor(ccc3(255, 255, 255));
			}
		}
		if (profile.displays[10]) {
			std::string nd = "Noclip Deaths: ";
			profile.displayNodes[10]->setString(nd.c_str());

			if (Crystal::profile.redDeath && deaath) {
				profile.displayNodes[10]->setColor(ccc3(255, 0, 0));
			} else {
				profile.displayNodes[10]->setColor(ccc3(255, 255, 255));
			}
		}
		if (profile.displays[11]) {
			std::string displayL;
			std::string levelName = PlayLayer::get()->m_level->m_levelName;
			std::string levelAuthor = PlayLayer::get()->m_level->m_creatorName;
			std::string levelID = std::to_string(PlayLayer::get()->m_level->m_levelID);			
			if (PlayLayer::get()->m_level->m_levelID == 0) {
				levelID = "Copy";
			}
			if (PlayLayer::get()->m_level->m_levelID < 22 && PlayLayer::get()->m_level->m_levelID > 0) {
				levelAuthor = "RobTop"; 
			}

			if (Crystal::profile.hideID && !Crystal::profile.author) {
				displayL = levelName;
			} else if (Crystal::profile.hideID && Crystal::profile.author) {
				displayL = levelName + " by " + levelAuthor;
			} else {
				displayL = levelName + " (" + levelID + ")";
			}
			profile.displayNodes[11]->setString(displayL.c_str());
		}
		if (profile.displays[12]) {
            if (profile.replay && !profile.renderer) {
                std::string status = "Playing: " + std::to_string(currentP1index) + "/" + std::to_string(P1pushes.size()) + " (Frame " + std::to_string((int)(m_time * profile.TPS)) + ")";
                profile.displayNodes[12]->setString(status.c_str());
            } else if (profile.record) {
                std::string status = "Recording: Macro Frame " + std::to_string((int)(m_time * profile.TPS));
                profile.displayNodes[12]->setString(status.c_str());
            } else if (profile.replay && profile.renderer) {
                std::string status = "Rendering: Video Frame " + std::to_string((int)(m_time * 60));
                profile.displayNodes[12]->setString(status.c_str());
            } else {
				profile.displayNodes[12]->setString("Not using Amethyst");
			}
        }
		if (profile.displays[13]) {
			auto t = std::time(nullptr);
			std::tm tm = *std::localtime(&t);

			std::ostringstream oss;
			if (Crystal::profile.ipm) {
				oss << std::put_time(&tm, "%I:%M:%S %p");
			} else {
				oss << std::put_time(&tm, "%H:%M:%S");
			}
			auto clstr = oss.str();

			if (Crystal::profile.iat) {
				int minutes = static_cast<int>(m_time / 60);
    			int seconds = static_cast<int>(m_time) % 60;

				std::ostringstream timeStream;
    			timeStream << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds;
				std::string time = timeStream.str();

				profile.displayNodes[13]->setString(time.c_str());
			} else if (Crystal::profile.ilt) {
				int hours = static_cast<int>(timee / 3600);
				int minutes = static_cast<int>(timee / 60);
    			int seconds = static_cast<int>(timee) % 60;

				std::ostringstream timeStr;
    			timeStr << std::setfill('0') << std::setw(2) << hours << ":"
               	<< std::setw(2) << minutes << ":"
               	<< std::setw(2) << seconds;
				std::string tie = timeStr.str();

				profile.displayNodes[13]->setString(tie.c_str());
			} else if (Crystal::profile.igt) {
				auto nov = std::chrono::high_resolution_clock::now();
            	auto teim = std::chrono::duration_cast<std::chrono::seconds>(nov - tiem);

            	int hours = static_cast<int>(teim.count() / 3600);
    			int minutes = static_cast<int>(teim.count() / 60);
    			int secs = static_cast<int>(teim.count()) % 60;

				std::ostringstream tStr;
    			tStr << std::setfill('0') << std::setw(2) << hours << ":"
               	<< std::setw(2) << minutes << ":"
               	<< std::setw(2) << secs;
				std::string tei = tStr.str();

				profile.displayNodes[13]->setString(tei.c_str());
			} else {
				profile.displayNodes[13]->setString(clstr.c_str());
			}
		}

		if (Crystal::profile.progressBar) {
			m_sliderGrooveSprite->setVisible(false);
			m_percentLabel->setPositionX(cocos2d::CCDirector::sharedDirector()->getWinSize().width / 2 - (m_percentLabel->getContentSize().width / 4));
		} else {
			m_sliderGrooveSprite->setVisible(true);
		}
		if (Crystal::profile.hideatts) {
			if (Crystal::profile.hidenormalatts && !m_isPracticeMode) m_attemptLabel->setVisible(false);
			if (Crystal::profile.hidepracticeatts && m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
        drawer->clear();

		for (int i = 0; i < variables.size(); i++) {
			if (variables[i].activeVar == 0) m_player1->m_gravity = variables[i].activeValue;
			if (variables[i].activeVar == 1) m_player1->m_xVelocity = variables[i].activeValue;
			if (variables[i].activeVar == 2) m_player1->m_yVelocity = variables[i].activeValue;
			if (variables[i].activeVar == 3) m_player1->m_position.x = variables[i].activeValue;
			if (variables[i].activeVar == 4) m_player1->m_position.y = variables[i].activeValue;
			if (variables[i].activeVar == 5) m_player1->m_jumpAccel = variables[i].activeValue;
			if (variables[i].activeVar == 6) m_player1->m_vehicleSize = variables[i].activeValue;
		}

		if (profile.record || profile.replay) f4 = 1.f / (profile.FPS * (profile.TPS / 60)) / speedhack;

		if (gameStarted && (!profile.framestep || (Crystal::profile.framestep && shouldUpdate))) currentFrame += f4;
		if (gameStarted && (!profile.framestep || (Crystal::profile.framestep && shouldUpdate))) currentTXTFrame++;

		if (!profile.framestep || (Crystal::profile.framestep && shouldUpdate)) {
			PlayLayer::update(f4);
			if (profile.renderer) record.handle_recording(this, f4);
		}

		if (profile.trajectory) drawer->processMainTrajectory(f4);

		if (profile.replay && gameStarted) currentMacro.updateReplay(f4);

		if (profile.layout) {
			auto p = PlayLayer::get()->getChildren()->objectAtIndex(0);
			auto bg = static_cast<CCSprite*>(p);
			ccColor3B color = { (GLubyte)(40), (GLubyte)(125), (GLubyte)(255) };
			bg->setColor(color);
		}

		if (s_showOnDeath) {
			if (!s_drawOnDeath || !Crystal::profile.hitboxes) return;
			drawer->setVisible(true);
		}		

		for (size_t i = 0; i < coins.size(); i++) {
			if (coins[i] && m_player1->getPositionX() <= coins[i]->getPositionX() && Crystal::profile.hitboxes && profile.coinFind) drawer->drawSegment(m_player1->getPosition(), coins[i]->getPosition(), 0.5f, ccc4f(0, 1, 0, 1));
		}

		if (m_player1 && Crystal::profile.hitboxes) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2 && Crystal::profile.hitboxes) {
			drawer->drawForPlayer2(m_player2);
		}

		s_showOnDeath = Crystal::profile.onDeath;

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				if (Crystal::profile.hitboxes) drawer->drawForObject(obj);
			}
		}
	}

    void markCheckpoint() {
		PlayLayer::markCheckpoint();
	}

	void removeLastCheckpoint() {
		PlayLayer::removeLastCheckpoint();
		if (profile.record) currentMacro.removeCheckpointData();
	}

    void startMusic() {
		if (Crystal::profile.pracmusic) {
			auto p = m_isPracticeMode;
			m_isPracticeMode = false; // pretend there is no practice mode
			PlayLayer::startMusic();
			m_isPracticeMode = p;
		} else {
			PlayLayer::startMusic();
		}
	}

	std::string getOffsetTime(float time) {
		std::stringstream ret;
		ret << "00:";
		ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time / 60)) << ":";
		ret << std::setw(2) << std::setfill('0') << std::to_string((int)(time) % 60);
		return ret.str();
	}

	std::string exec(std::string command) {
		char buffer[128];
		std::string result = "";

		// Open pipe to file
		FILE* pipe = popen(command.c_str(), "r");
		if (!pipe) {
			return "Render Failed";
		}

		// read till end of process:
		while (!feof(pipe)) {

			// use buffer to read and add to result
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}

		pclose(pipe);
		return result;
	}

    void onQuit() {
		if (profile.trajectory) drawer->onQuitTrajectory();
		std::string renderprocess;
		//FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		std::string basicNAME = (std::string)renderer + "/new.mp4";
		if (profile.renderer) {
			record.stop();
		}
		coins.clear();
		if (!shouldQuit && Crystal::profile.confirmQuit && !m_hasLevelCompleteMenu) {
			geode::createQuickPopup(
				"Confirm Quit",            // title
				"Are you sure you would like to Quit?",   // content
				"Cancel", "Quit",      // buttons
				[](auto, bool btn2) {
					if (btn2) {
						shouldQuit = true;
					}
				}
			);
		} else {
			PlayLayer::onQuit();
		}
	}

    void togglePracticeMode(bool p) {
		if (Crystal::profile.pracmusic) {
			if (!m_isPracticeMode && p) {
				m_isPracticeMode = p;
				m_UILayer->toggleCheckpointsMenu(p);
				PlayLayer::startMusic();
				this->stopActionByTag(18);
			} else {
				PlayLayer::togglePracticeMode(p);
			}
		} else {
			PlayLayer::togglePracticeMode(p);
		}
	}

    void toggleFlipped(bool one, bool two) {
		if (!Crystal::profile.mirror) {
			PlayLayer::toggleFlipped(one, two);
		}
	}

	void startGame() {
		PlayLayer::startGame();
		gameStarted = true;
	}

    static inline tulip::HitboxNode* drawer;

	bool init(GJGameLevel* gl) {
		//leftDisplay = 0;
		timee = 0.0f;
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (Crystal::profile.startpos || Crystal::profile.checkpointswitch) {
			rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_startPosIndex = -1;
			g_startPoses = {};
			g_checkpointIndex = -1;
			g_checkpoints = {};
		}

		for (int d = 0; d < 15; d++) {
			profile.displayNodes[d] = CCLabelBMFont::create("Loading...", "bigFont.fnt");
		}

        drawer = tulip::HitboxNode::create();

		ss = 0;
		clickscount = 0;
		click_count = 0;
		gameStarted = false;
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

		for (int d = 0; d < 15; d++) {
			profile.displayNodes[d]->setVisible(profile.displays[d]);
		}

		if (!profile.testmode) {
			if (this->getChildrenCount()) {
				CCArrayExt<CCNode*> children = this->getChildren();
				for (auto* child : children) {
					using namespace std::literals::string_view_literals;
					if (auto* label = typeinfo_cast<CCLabelBMFont*>(child); label && label->getString() == "Testmode"sv) {
						label->setVisible(false);
						break;
					}
				}
			}
		}
		auto win_size = CCDirector::sharedDirector()->getWinSize();

		if (profile.clickBot) Clickbot::start = std::chrono::system_clock::now();

        m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = Crystal::profile.onDeath;
		drawer->m_drawTrail = Crystal::profile.drawTrail;
		s_onlyHitboxes = false;
		if (s_showOnDeath) s_drawOnDeath = false;

		if (profile.trajectory) drawer->createPlayersForTrajectory();

		currentFrame = 0;
		
		if (Crystal::profile.startpos || Crystal::profile.checkpointswitch) {
			g_startPosText->setPosition(win_size.width / 2, corner - 275);
			g_startPosText->setScale(0.5);
			g_startPosText->setOpacity(50);

			rightButton->::Main::setPosition(win_size.width / 2 - 30, corner - 275);
			rightButton->setScale(0.5);
			rightButton->setOpacity(50);
			
			leftButton->::Main::setPosition(win_size.width / 2 + 30, corner - 275);
			leftButton->setFlipX(true);
			leftButton->setScale(0.5);
			leftButton->setOpacity(50);

			if (!m_isTestMode) {
				g_startPosText->setVisible(false);
				rightButton->setVisible(false);
				leftButton->setVisible(false);
			}
			
			addChild(g_startPosText, 1000);
			addChild(rightButton, 1000);
			addChild(leftButton, 1000);
		}
		if (Crystal::profile.progressBar) {
			m_percentLabel->setPositionX(CCDirector::sharedDirector()->getWinSize().width / 2);
		}
		for (int d = 0; d < 15; d++) {
			CrystalClient::get()->arrangeText(d, this, true);
		}
		return true;
	}
};

class $(UILayer) {
	void customMod(int current) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		if (current == 0) {
			Crystal::profile.noclip = !Crystal::profile.noclip;
		} else if (current == 1) {
			PlayLayer::get()->destroyPlayer(PlayLayer::get()->m_player1, nullptr);
		} else if (current == 2) {
			PlayLayer::get()->resetLevel();
		} else if (current == 3) {
			if (speedhack != 1) {
				CCDirector::sharedDirector()->getScheduler()->setTimeScale(1);
			} else {
				CCDirector::sharedDirector()->getScheduler()->setTimeScale(speedhack);
			}
		} else if (current == 4) {
			s_showOnDeath = !s_showOnDeath;
		} else if (current == 5) {
			if (Crystal::profile.autoclick) {
				Crystal::profile.autoclick = false;
				GJBaseGameLayer::get()->releaseButton(1,true);
			} else {
				Crystal::profile.autoclick = true;
			}
		} else if (current == 6) {
			mpl->updateIndex(false);
		} else if (current == 7) {
			mpl->updateIndex(true);
		} else if (current == 10) {
			if (PlayLayer::get()->m_isPracticeMode) PlayLayer::get()->markCheckpoint();
		} else if (current == 11) {
			if (PlayLayer::get()->m_isPracticeMode) PlayLayer::get()->removeLastCheckpoint();
		} else if (current == 13 && profile.framestep) {
			shouldUpdate = true;
			mpl->update(1.f / (profile.FPS * (profile.TPS / 60)) / profile.speedhack);
			shouldUpdate = false;
		}
	}

	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());

		for (int m = 0; m < keybinds.size(); m++) {
			if (kc == CrystalClient::shortcutKey(keybinds[m].activeKey)) {
				customMod(keybinds[m].activeMod);
			}
		}

		UILayer::keyDown(kc);
	}
};

class $modify(CreatorLayer) {
	virtual bool init() {
        CreatorLayer::init();

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
        LeaderboardsLayer::init(state);

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LocalLevelManager) {
	bool init() {
		LocalLevelManager::init();

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(ModifiedSearchLayer, LevelSearchLayer) {
	virtual bool init() {
		LevelSearchLayer::init();

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

		if (Crystal::profile.buttonDL || Crystal::profile.buttonCL) {
			findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* thing) {
				return strncmp(thing->getString(), "Filters", 7) == 0;
			})->removeFromParentAndCleanup(true);

			findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* thing) {
				return strncmp(thing->getString(), "Quick Search", 12) == 0;
			})->removeFromParentAndCleanup(true);

			auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
				return strncmp(lbl->getString(), "Trending", 8) == 0;
			})->getParent()->getParent()->getParent();

			auto mpos = menu->getPosition();
			menu->setPositionY(mpos.y - 17.5);
		}

		if (Crystal::profile.buttonDL) {
			auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
				return strncmp(lbl->getString(), "Trending", 8) == 0;
			})->getParent()->getParent()->getParent();

			auto button_sprite = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");

			auto demon_button = CCMenuItemSpriteExtra::create(button_sprite, this, menu_selector(ModifiedSearchLayer::onDemonList));
			auto demon_label = CCLabelBMFont::create("Demon List", "bigFont.fnt");
			auto demon_icon = CCSprite::createWithSpriteFrameName("rankIcon_all_001.png");

			demon_button->addChild(demon_label);
			demon_button->addChild(demon_icon);

			demon_label->setScale(0.55);
			demon_label->setPosition(ccp(70, 17));
			demon_icon->setPosition(ccp(140, 16));
			demon_button->setPosition(reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(0))->getPosition() + ccp(0, 35));

			menu->addChild(demon_button);
		} 
		
		if (Crystal::profile.buttonCL) {
			auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
				return strncmp(lbl->getString(), "Trending", 8) == 0;
			})->getParent()->getParent()->getParent();

			auto button_sprite2 = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");
			
			auto challenge_button = CCMenuItemSpriteExtra::create(button_sprite2, this, menu_selector(ModifiedSearchLayer::onChallengeList));
			auto challenge_label = CCLabelBMFont::create("Challenge List", "bigFont.fnt");
			auto challenge_icon = CCSprite::createWithSpriteFrameName("rankIcon_top100_001.png");

			challenge_button->addChild(challenge_label);
			challenge_button->addChild(challenge_icon);

			challenge_label->setScale(0.45);
			challenge_label->setPosition(ccp(70, 17));
			challenge_icon->setPosition(ccp(145, 16));
			challenge_icon->setScale(0.8);
			challenge_button->setPosition(reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(1))->getPosition() + ccp(0, 35));

			menu->addChild(challenge_button);
		}
		return true;
	}

	void onDemonList(CCObject*) {
		if (Crystal::profile.buttonDL) {
			m_searchInput->onClickTrackNode(false);
			auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3141), ""));

			auto s = CCScene::create();
			s->addChild(p);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
		}
	}

	void onChallengeList(CCObject*) {
		if (Crystal::profile.buttonCL) {
			m_searchInput->onClickTrackNode(false);
			auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3142), ""));

			auto s = CCScene::create();
			s->addChild(p);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
		}
	}
};

class $(GameLevelManager) {
	void ProcessHttpRequest(gd::string gdurl, gd::string gdquery, gd::string idk, int type) {
		std::string url(gdurl);
		std::string query(gdquery);

		if (url == "http://www.boomlings.com/database/getGJLevels21.php") {
			auto thing = atoi(query.substr(query.find("page=") + 5).c_str());
			if (query.find("type=3141") != std::string::npos && Crystal::profile.buttonDL) {
				url = std::string("http://absolllute.com/api/mega_hack/demonlist/page") + std::to_string(thing) + ".txt";
			} else if (query.find("type=3142") != std::string::npos && Crystal::profile.buttonCL) {
				url = std::string("http://absolllute.com/api/mega_hack/challengelist/page") + std::to_string(thing) + ".txt";
			}
		}

		GameLevelManager::ProcessHttpRequest(url, query, idk, type);
	}
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* search) {
		LevelBrowserLayer::init(search);

        if (Crystal::profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(CustomSongWidget) {
	bool init(SongInfoObject* so, LevelSettingsObject* ls, bool a, bool b , bool c , bool d, bool hideBackground) {
		CustomSongWidget::init(so,ls, a, b, c, d, hideBackground);
	
		if (Crystal::profile.autoSong) {
			auto button = findFirstChildRecursive<CCMenuItemSpriteExtra>(this, [](CCNode* n) {
				return n->getPositionY() == -180.0f;
		});

        if (button->isVisible()) {
			button->activate();
		}
	}

		return true;
	}
};

class $modify(CCLayerColor) {
	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (Crystal::profile.translists) {
			return CCLayerColor::initWithColor(ccc4(0, 0, 0, 0), 0, 0);
		} else {
			return CCLayerColor::initWithColor(yk, f1, f2);
		} 
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
		ret["keybindsSize"] = keybinds.size();
		for (int i = 0; i < keybinds.size(); i++) {
			ret[std::to_string(i).c_str()]["key"] = keybinds[i].activeKey;
			ret[std::to_string(i).c_str()]["mod"] = keybinds[i].activeMod;
		}
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
			keybinds.clear();
			for (int i = 0; i < json["keybindsSize"]; i++) {
				keybinds.push_back({json[std::to_string(i).c_str()]["key"], json[std::to_string(i).c_str()]["mod"]});
			}
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