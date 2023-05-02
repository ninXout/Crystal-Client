#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "CrystalClient.hpp"
#include <imgui.h>
#include "ImGui.hpp"
#include "Includes.hpp"
#include "Hacks.hpp"

USE_GEODE_NAMESPACE();

using namespace Shortcuts;
using namespace Variables;
using namespace Crystal;
using namespace CrystalTheme;

void CrystalClient::drawGUI() {
    ImGui::Begin("Player");
	CrystalClient::ImExtendedToggleable("Noclip", &Crystal::profile.noclip);
	if (ImGui::BeginPopupModal("Noclip", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Noclip Player 1", &Crystal::profile.noclipP1);
		CrystalClient::ImToggleable("Noclip Player 2", &Crystal::profile.noclipP2);
		CrystalClient::ImToggleable("Tint Screen on Death", &Crystal::profile.tintOnDeath);
		ImGui::PushItemWidth(100);
		ImGui::InputFloat("##Noclip Accuracy Limit", &profile.resetAcc);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		CrystalClient::ImToggleable("Noclip Accuracy Limit", &profile.resetOnAccuracy);
		ImGui::PushItemWidth(100);
		ImGui::InputInt("##Noclip Deaths Limit", &profile.resetDeath);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		CrystalClient::ImToggleable("Noclip Deaths Limit", &profile.resetOnDeath);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("No Death Effect", &Crystal::profile.deathEffect);
	CrystalClient::ImToggleable("Instant Death Respawn", &Crystal::profile.instantdeath);
	CrystalClient::ImExtendedToggleable("Auto Reset", &Crystal::profile.autoreset);
	if (ImGui::BeginPopupModal("Auto Reset", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Auto Reset Percentage", &Crystal::profile.autoresetnum);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Respawn Bug Fix", &Crystal::profile.respawnfix);
	CrystalClient::ImToggleable("Practice Bug Fix", &Crystal::profile.practiceorbfix);
	CrystalClient::ImExtendedToggleable("No Wave Pulse", &Crystal::profile.nopulse);
	if (ImGui::BeginPopupModal("No Wave Pulse", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputFloat("Wave Trail Size", &Crystal::profile.trailsize);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("Solid Wave Trail", &Crystal::profile.solidwave);
	CrystalClient::ImToggleable("Invisible Player", &Crystal::profile.invisibleplayer);
	ImGui::End();

	ImGui::Begin("Icon");
	CrystalClient::ImExtendedToggleable("Rainbow Icon", &Crystal::profile.rainbowIcon);
	if (ImGui::BeginPopupModal("Rainbow Icon", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Rainbow Player Color 1", &Crystal::profile.rainbowP1);
		CrystalClient::ImToggleable("Rainbow Player Color 2", &Crystal::profile.rainbowP2);
		CrystalClient::ImToggleable("Rainbow Wave Trail Player 1", &Crystal::profile.rainbowP1wave);
		CrystalClient::ImToggleable("Rainbow Wave Trail Player 2", &Crystal::profile.rainbowP2wave);
		ImGui::InputFloat("Rainbow Speed", &Crystal::profile.rainbowspeed);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::End();

	ImGui::Begin("Level");
	CrystalClient::ImExtendedToggleable("Hitbox Viewer", &Crystal::profile.hitboxes);
	if (ImGui::BeginPopupModal("Hitbox Viewer", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("Show Hitboxes on Death", &Crystal::profile.onDeath);
		CrystalClient::ImToggleable("Show Hitbox Trail", &Crystal::profile.drawTrail);
		CrystalClient::ImToggleable("Show Hitboxes in Editor", &Crystal::profile.inEditor);
		CrystalClient::ImToggleable("Fill Hitboxes", &Crystal::profile.fillHitbox);
		ImGui::InputFloat("Hitbox Fill Opacity", &Crystal::profile.fillOpacity);
		CrystalClient::ImToggleable("Coin Tracker", &Crystal::profile.coinFind);
		CrystalClient::ImToggleable("Show Trajectory [BETA]", &Crystal::profile.trajectory);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
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
	CrystalClient::ImToggleable("Ignore ESC", &Crystal::profile.ignoreESC);
	CrystalClient::ImToggleable("Confirm Quit", &Crystal::profile.confirmQuit);
	CrystalClient::ImToggleable("Auto LDM", &Crystal::profile.autoldm);
	CrystalClient::ImToggleable("Flipped Dual Controls", &Crystal::profile.flippedcontrol);
	CrystalClient::ImToggleable("Mirrored Dual Controls", &Crystal::profile.mirrorcontrol);
	CrystalClient::ImToggleable("Start Pos Switcher", &Crystal::profile.startpos);
	CrystalClient::ImToggleable("Frame Stepper", &Crystal::profile.framestep);
	CrystalClient::ImToggleable("Load from Last Checkpoint", &Crystal::profile.lastCheckpoint);
	CrystalClient::ImToggleable("No Glow", &Crystal::profile.noglow);
	CrystalClient::ImToggleable("No Mirror Effect", &Crystal::profile.mirror);
	CrystalClient::ImToggleable("Layout Mode", &Crystal::profile.layout);
	CrystalClient::ImToggleable("AutoClicker", &Crystal::profile.autoclick);
    ImGui::End();
    ImGui::Begin("Display");
	CrystalClient::ImToggleable("Testmode Label", &Crystal::profile.testmode);
	CrystalClient::ImExtendedToggleable("Custom Message", &Crystal::profile.customMessage);
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputTextWithHint("Message", "Custom Message", profile.message, IM_ARRAYSIZE(profile.message));
		ImGui::PushItemWidth(200);
		ImGui::Combo("##", &profile.POScustomMessage, positionList, IM_ARRAYSIZE(positionList));
		ImGui::PopItemWidth();
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImToggleable("FPS Display", &Crystal::profile.fps);
	CrystalClient::ImToggleable("Clicks", &Crystal::profile.cps);
	CrystalClient::ImToggleable("Jumps", &Crystal::profile.jumps);
	CrystalClient::ImToggleable("Cheat Indicator", &Crystal::profile.cheatIndicate);
	CrystalClient::ImToggleable("Last Death", &Crystal::profile.lastDeath);
	CrystalClient::ImToggleable("Attempts", &Crystal::profile.attempts);
	CrystalClient::ImToggleable("Best Run", &Crystal::profile.bestRun);
	CrystalClient::ImToggleable("Run From", &Crystal::profile.runFrom);
	CrystalClient::ImToggleable("Noclip Accuracy", &Crystal::profile.noclipAcc);
	CrystalClient::ImToggleable("Noclip Deaths", &Crystal::profile.noclipDeath);
	CrystalClient::ImToggleable("Total Attempts", &Crystal::profile.totalAtt);
	CrystalClient::ImToggleable("Level Name and ID", &Crystal::profile.lvlData);
	CrystalClient::ImToggleable("Macro Status", &Crystal::profile.macroStatus);
	CrystalClient::ImExtendedToggleable("Clock", &Crystal::profile.clock);
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("In-Game Time", &Crystal::profile.igt);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Customization");
    //ImGui::ColorEdit4("Accent Color", LightColour, ImGuiColorEditFlags_NoInputs);
    //ImGui::ColorEdit4("Base Color", BGColour, ImGuiColorEditFlags_NoInputs);
    CrystalClient::ImToggleable("RGB Accent Color", &profile.RGBAccent);
    CrystalClient::ImToggleable("Borders", &profile.borders);
    CrystalClient::ImToggleable("Rounded Windows", &profile.rounded);
    ImGui::End();
    ImGui::Begin("Bypasses");
    //ImGui::InputFloat("Editor Grid Size", &gridSize, 0.001f, 1000.000f, "%.3f");
	CrystalClient::ImToggleable("ACTUAL anticheat", &profile.anticheat);
    ImGui::End();
    ImGui::Begin("Global");
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
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]");
    CrystalClient::ImToggleable("Record", &profile.record);
	ImGui::SameLine();
    CrystalClient::ImToggleable("Replay", &profile.replay);
	CrystalClient::ImToggleable("ClickBot", &profile.clickBot);
	ImGui::SameLine();
	CrystalClient::ImToggleable("Delta Lock", &profile.deltaLock);
	ImGui::InputFloat("ClickBot Volume", &profile.CBvolume);
    //ImGui::Combo("Macro Type", &currentMacroType, macroTypes, IM_ARRAYSIZE(macroTypes));
    ImGui::InputTextWithHint("Macro Name", "Macro Name", profile.macroname, IM_ARRAYSIZE(profile.macroname));
    if (ImGui::Button("Save Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/" + (std::string)profile.macroname + ".thyst";
		std::fstream myfile(filename.c_str(), std::ios::app);
		myfile << pushes.size();
		myfile << "\n";
		for (size_t i = 0; i < pushes.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << pushes[i];
			myfile << "\n";
		}
		myfile << releases.size();
		myfile << "\n";
		for (size_t i = 0; i < releases.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << releases[i];
			myfile << "\n";
		}
		// pushes
		myfile << pushData.size();
		myfile << "\n";
		for (size_t i = 0; i < pushData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << pushData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << pushData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << pushData[i].accel;
			myfile << "\n";
		}
		// releases
		myfile << releaseData.size();
		myfile << "\n";
		for (size_t i = 0; i < releaseData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << releaseData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << releaseData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << releaseData[i].accel;
			myfile << "\n";
		}
		// frames
		myfile << framesData.size();
		myfile << "\n";
		for (size_t i = 0; i < framesData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << framesData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << framesData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << framesData[i].accel;
			myfile << "\n";
		}
	}
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/" + (std::string)profile.macroname + ".thyst";
        std::string line;
		std::fstream file;
		file.open(filename, std::ios::in);
		if (file.is_open()) {
			getline(file, line);
			int len;
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				pushes.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				releases.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newPush;
				getline(file, line);
				newPush.xpos = stof(line);
				getline(file, line);
				newPush.ypos = stof(line);
				getline(file, line);
				newPush.accel = stod(line);
				pushData.push_back(newPush);
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newRel;
				getline(file, line);
				newRel.xpos = stof(line);
				getline(file, line);
				newRel.ypos = stof(line);
				getline(file, line);
				newRel.accel = stod(line);
				releaseData.push_back(newRel);
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newFrameDat;
				getline(file, line);
				newFrameDat.xpos = stof(line);
				getline(file, line);
				newFrameDat.ypos = stof(line);
				getline(file, line);
				newFrameDat.accel = stod(line);
				framesData.push_back(newFrameDat);
			}
			file.close();
		}
	}
    ImGui::SameLine();
    if (ImGui::Button("Clear Macro")) {
        pushes.clear();
		releases.clear();
		pushData.clear();
		releaseData.clear();
		framesData.clear();
		checkpointFrames.clear();
		checkpoints.clear();
    }
	//CrystalClient::ImToggleable("Enable Macro Buffer", &macroBuffer);
	//if (ImGui::Button("Clear Macro Buffer")) {
		//newQueue.clear();
	//}
    ImGui::End();
    ImGui::Begin("Shortcuts");
    if (ImGui::Button("Open Songs Folder")) {
        system("open ~/Library/Caches");
    }
    if (ImGui::Button("Open Crystal Folder")) {
        system("open Crystal");
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
		ImGui::Text(modbindings[keybinds[i].activeMod]);
		ImGui::SameLine();
		ImGui::Text(keybindings[keybinds[i].activeKey]);
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			keybinds.erase(keybinds.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
	ImGui::Begin("Variable Changer");
    ImGui::Combo("Variable", &currentVar, playerVars, IM_ARRAYSIZE(playerVars));
	ImGui::InputFloat("Value", &currentValue);
    if (ImGui::Button("Add Change")) {
        variables.push_back({currentVar, currentValue});
    }
	for (size_t i = 0; i < variables.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text(playerVars[variables[i].activeVar]);
		ImGui::SameLine();
		ImGui::Text(std::to_string(variables[i].activeValue).c_str());
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			variables.erase(variables.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
	ImGui::Begin("Internal Renderer");
	CrystalClient::ImToggleable("Render Recording", &rendering);
	CrystalClient::ImToggleable("Include Sound", &withAudio);
	ImGui::End();
	ImGui::ShowDemoWindow();
}

void CrystalClient::addTheme() {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colours = ImGui::GetStyle().Colors;

    if (profile.RGBAccent) {
        LightColour[0] = LightColour[0] + rDir;
        LightColour[1] = LightColour[1] + gDir;
        LightColour[2] = LightColour[2] + bDir;

        if (LightColour[0] >= 1 || LightColour[0] <= 0) { rDir = rDir * -1; }
        if (LightColour[1] >= 1 || LightColour[1] <= 0) { gDir = gDir * -1; }
        if (LightColour[2] >= 1 || LightColour[2] <= 0) { bDir = bDir * -1; }
    }

    DarkColour[0] = (LightColour[0] * 0.5f);
    DarkColour[1] = (LightColour[1] * 0.5f);
    DarkColour[2] = (LightColour[2] * 0.5f);
    DarkColour[3] = LightColour[3];
    VeryLightColour[0] = (LightColour[0] * 1.5f);
    VeryLightColour[1] = (LightColour[1] * 1.5f);
    VeryLightColour[2] = (LightColour[2] * 1.5f);
    VeryLightColour[3] = LightColour[3];

    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    style->Alpha = 1.f;
    style->WindowRounding = profile.rounded ? 12.f : 0.f;
    style->FrameRounding = 4.f;
    style->ScrollbarSize = 15.f;
    style->ScrollbarRounding = 12.f;
    style->PopupRounding = 4.f;
    style->WindowBorderSize = 1.5f;
    colours[ImGuiCol_TitleBg] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_TitleBgActive] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_WindowBg] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_Border] = RGBAtoIV4(profile.borders ? LightColour : BGColour);
    colours[ImGuiCol_FrameBg] = RGBAtoIV4(DarkColour);
    colours[ImGuiCol_FrameBgHovered] = RGBAtoIV4(DarkColour);
    colours[ImGuiCol_FrameBgActive] = RGBAtoIV4(LightColour);
    colours[ImGuiCol_PlotHistogram] = RGBAtoIV4(LightColour);
    colours[ImGuiCol_Button] = RGBAtoIV4(LightColour);
    colours[ImGuiCol_ButtonHovered] = RGBAtoIV4(VeryLightColour);
    colours[ImGuiCol_Header] = RGBAtoIV4(DarkColour);
    colours[ImGuiCol_HeaderHovered] = RGBAtoIV4(LightColour);
    colours[ImGuiCol_HeaderActive] = RGBAtoIV4(VeryLightColour);
    colours[ImGuiCol_SliderGrab] = RGBAtoIV4(LightColour);
    colours[ImGuiCol_SliderGrabActive] = RGBAtoIV4(VeryLightColour);
    colours[ImGuiCol_CheckMark] = RGBAtoIV4(VeryLightColour);
}

void CrystalClient::getTextPos(CCNode* label, int anchor) {
	auto win_size = CCDirector::sharedDirector()->getWinSize();
	// tl, tr, bl, br
	if (anchor == 1) {
		nextTL++;
		label->setPositionX(0.f);
		label->setAnchorPoint(ccp(0.f, 1.f));
		label->setPositionY(win_size.height - (2.f * nextTL));
	} else if (anchor == 2) {
		nextTR++;
		label->setPositionX(win_size.width);
		label->setAnchorPoint(ccp(0.f, 1.f));
		label->setPositionY(win_size.height - (2.f * nextTR));
	} else if (anchor == 3) {
		nextBL++;
		label->setPositionX(0.f);
		label->setAnchorPoint(ccp(0.f, 0.f));
		label->setPositionY(4.f * nextBL);
	} else {
		nextBR++;
		label->setPositionX(win_size.width);
		label->setAnchorPoint(ccp(0.f, 0.f));
		label->setPositionY(4.f * nextBR);
	}
}

cocos2d::_ccColor3B CrystalClient::getRainbow(float offset) {
	float R;
	float G;
	float B;

	float hue = fmod(g + offset, 360);
	float sat = 1;
	float vc = 1;
	HSVtoRGB(R, G, B, hue, sat, vc);

	cocos2d::_ccColor3B out;
	out.r = R*255;
	out.g = G*255;
	out.b = B*255;
	return out;
}

void CrystalClient::arrangeText(int arrayLength, PlayLayer* menulay) {
	//std::distance(item_names, std::find(item_names, item_names + arrayLength, "Custom Message"))
	int anchor = 1;
	if (PlayLayer::get()->m_isTestMode) anchor = 2;
	setAnchoredPosition(g_message, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_cheating, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_run, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_jumps, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_tatts, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_death, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(font, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_atts, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_bestRun, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_levelInfo, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_clicks, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(text, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_macro, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
	setAnchoredPosition(g_clock, anchor, reinterpret_cast<CCLayer*>(menulay));
	anchor++;
}

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        cocos2d::enumKeyCodes dispatchedkey = KEY_Tab;
		for (int m = 0; m < keybinds.size(); m++) {
			if (keybinds[m].activeMod == 12) {
				dispatchedkey = CrystalClient::shortcutKey(keybinds[m].activeKey);
			}
		}
        if (down && key == dispatchedkey) {
            CrystalClient::get()->toggle();
            return true;
        }
		if (down && key == KEY_F && profile.framestep && PlayLayer::get()) {
			shouldUpdate = true;
			PlayLayer::get()->update(1.f / profile.TPS);
			shouldUpdate = false;
		}
        if (!CrystalClient::get()->isRendering) return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};

class $modify(CCDirector) {
    void drawScene() {
        CrystalClient::get()->setup();

        CCDirector::drawScene();

        CrystalClient::get()->render();
    }
};

class $modify(MenuLayer) {
	bool init() {
		MenuLayer::init();
		//CrystalClient::get()->loadFromFile();
		//Crystal::write((geode::Mod::get()->getSaveDir() / "GH_config.dat"), profile);
		//Crystal::saveMods(profile);
		profile = Crystal::loadMods();
		loadKeybinds();
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
		//if (!classicspeed) CCScheduler::update(f3 * speedhack);
		if (PlayLayer::get() && (rendering)) {
			auto dir = CCDirector::sharedDirector();

			float spf = (float)dir->getAnimationInterval();
			float tScale = dir->getScheduler()->getTimeScale();

			f3 = spf * tScale;
			renderTime += 1.f / static_cast<float>(spf);
		}
		if ((profile.TPSbypass || profile.replay || profile.record || profile.FPSbypass) && PlayLayer::get() && !PlayLayer::get()->m_isPaused) {
			auto dir = CCDirector::sharedDirector();

			//if (record) f3 *= speedhack;

			float spf = (float)dir->getAnimationInterval() * (60 / profile.TPS);
			auto nspeedhack = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
    
			const float newdt = 1.f / profile.TPS / nspeedhack;
			const float otherdt = 1.f / profile.FPS / nspeedhack;

			float totaldt = 1.f / (profile.FPS * (profile.TPS / 60)) / nspeedhack;

			if (profile.deltaLock) return CCScheduler::update(totaldt);

			g_disable_render = true;

			if (profile.FPSbypass) cocos2d::CCApplication::sharedApplication()->setAnimationInterval(otherdt);
			else cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.f / 60.f);

			if (profile.TPSbypass && !profile.FPSbypass) {
				const int times = std::min(static_cast<int>((f3 + g_left_over) / newdt), 100); // limit it to 100x just in case
				for (int i = 0; i < times; ++i) {
					if (i == times - 1)
						g_disable_render = false;
					CCScheduler::update(newdt);
				}
				g_left_over += f3 - newdt * times;
			} else if (profile.FPSbypass && !profile.TPSbypass) {
				const int fpstimes = std::min(static_cast<int>((f3 + fps_left_over) / otherdt), 100); // limit it to 100x just in case
				for (int i = 0; i < fpstimes; ++i) {
					if (i == fpstimes - 1)
						g_disable_render = false;
					CCScheduler::update(otherdt);
				}
				fps_left_over += f3 - otherdt * fpstimes;
			} else if (profile.FPSbypass && profile.TPSbypass) {
				const int totaltimes = std::min(static_cast<int>((f3 + t_left_over) / totaldt), 100); // limit it to 100x just in case
				for (int i = 0; i < totaltimes; ++i) {
					if (i == totaltimes - 1)
						g_disable_render = false;
					CCScheduler::update(totaldt);
				}
				t_left_over += f3 - totaldt * totaltimes;
			}
		} else {
			CCScheduler::update(f3);
		}
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
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
    
	virtual void activateObject() {
		bool a = this->m_hasBeenActivated;
    	bool b = this->m_hasBeenActivatedP2;
		GameObject::activateObject();
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode) {
    		if (this->m_hasBeenActivated && !a) g_activated_objects.push_back(this);
        	if (this->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(this);
    	}
	}
};

class $modify(LevelTools) {
	static bool verifyLevelIntegrity(gd::string mg, int de) {
		if (profile.loadfail) return true;
		return LevelTools::verifyLevelIntegrity(mg, de);
	}
};

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		pushing = true;
		if (profile.record) {
            pushes.push_back(currentFrame);
            pushData.push_back(AmethystReplay::create());
        }
        if (profile.clickBot) {
            if (!inited) {
                FMOD::System_Create(&Clickbot::system);
                Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, nullptr);
                inited = true;
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
            Clickbot::clickChannel->setVolume((float)(250 / 100));
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
	}

	void releaseButton(int i, bool b) {
		pushing = false;
		if (profile.record) {
            releases.push_back(currentFrame);
			releaseData.push_back(AmethystReplay::create());
		}
		if (profile.clickBot) {
			if (Clickbot::cycleTime.count() < 0.5f) {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			} else {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			}
			
			
			Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
			Clickbot::releaseChannel->setVolume((float)(250 / 100));
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
	}

	void bumpPlayer(PlayerObject* player, GameObject* object) {
		bool a = object->m_hasBeenActivated;
    	bool b = object->m_hasBeenActivatedP2;
		GJBaseGameLayer::bumpPlayer(player, object);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode) {
        	if (object->m_hasBeenActivated && !a) g_activated_objects.push_back(object);
        	if (object->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(object);
    	}
	}
};

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (Crystal::profile.nopulse) m_pulseSize = profile.trailsize;
		if (Crystal::profile.solidwave) m_isSolid = true;
		HardStreak::updateStroke(f);
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
};

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (profile.hidepause) pause->setVisible(false);
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
	void playDeathEffect() {
		if (!Crystal::profile.deathEffect) {
			PlayerObject::playDeathEffect();
		}
	}
	void addAllParticles() {
		if (!Crystal::profile.instantdeath) {
			PlayerObject::addAllParticles();
		}
	}
	void update(float spe) {		
		if (m_waveTrail && Crystal::profile.solidwave) {
			m_waveTrail->setBlendFunc(getBlendFunc()); // removes the blending of it
		}
		if (Crystal::profile.invisibleplayer) {
			PlayerObject::setVisible(false);
		}
		PlayerObject::update(spe);
	}
	void ringJump(GameObject* ring) {
		bool a;
		bool b;
		a = ring->m_hasBeenActivated;
    	b = ring->m_hasBeenActivatedP2;
		PlayerObject::ringJump(ring);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && Crystal::profile.practiceorbfix) {
        	if (ring->m_hasBeenActivated && !a) g_activated_objects.push_back(ring);
        	if (ring->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(ring);
    	}
	}
	void saveToCheckpoint(PlayerCheckpoint* g) {
		PlayerObject::saveToCheckpoint(g);
		if (Crystal::profile.checkpointswitch) {
			g->retain();
            g_checkpointsPos.push_back(g->getPosition());
            g_checkpointsIG.push_back(g);
            g_checkpointIndex += 1;
            auto label = std::to_string(g_checkpointIndex + 1) + "/" + std::to_string(g_checkpointsIG.size());
            g_checkpointText->setString(label.c_str());
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

class $modify(Main, PlayLayer) {
    void updateIndex(bool increment) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (m_isTestMode) {
			g_startPosText->setOpacity(255);
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
		}

		if (increment) {
			g_startPosIndex++;
			if (m_isPracticeMode) g_checkpointIndex++;
		} else {
			g_startPosIndex--;
			if (m_isPracticeMode) g_checkpointIndex--;
		}

		if (g_startPosIndex == g_startPoses.size()) {
			g_startPosIndex = -1;
		} else if (g_startPosIndex < -1) {
			g_startPosIndex = g_startPoses.size() - 1;
		}



		auto colorPulseBegin = CCTintTo::create(0.0, 0, 255, 0);
		auto colorPulseEnd = CCTintTo::create(0.5, 255, 255, 255);

		auto opacityPulseBegin = CCFadeTo::create(0.0, 255);
		auto opacityPulseEnd = CCFadeTo::create(0.5, 50);

		if (m_isTestMode) {
			auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
			g_startPosText->setString(label.c_str());
			auto opacityPulseBegin = CCFadeTo::create(0, 255);
			auto opacityPulseWait = CCFadeTo::create(0.4, 255);
			auto opacityPulseEnd = CCFadeTo::create(0.3, 0);

			//g_startPosText->runAction(opacityPulseBegin);
			//g_startPosText->runAction(opacityPulseWait);
			//g_startPosText->runAction(opacityPulseEnd);
		}

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

		resetLevel();
		if (m_isPracticeMode) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
			m_player1->loadFromCheckpoint(g_checkpointsIG[g_checkpointIndex]);
		}
		if (m_isTestMode) g_startPosText->setOpacity(50);
		if (m_isPaused)
			GameSoundManager::sharedManager()->stopBackgroundMusic();
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

    void updateVisibility() {
		if (!g_disable_render) PlayLayer::updateVisibility();
	}

    void resetLevel() {
		if (Crystal::profile.respawnfix) {
			if (m_isTestMode || m_isPracticeMode) {
				smoothOut = 2;
			}
		}
		if (profile.bestRun) {
			bestEnd2 = (m_player1->getPositionX() / m_levelLength) * 100;
		}
        if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();

		PlayLayer::resetLevel();

		if (m_isPracticeMode && profile.record) {
			if (checkpoints.size() > 0) checkpoints.back().apply(GJBaseGameLayer::get()->m_player1);

			if (checkpointFrames.size() == 0) checkpointFrames.push_back(0);
			currentOffset = checkpointFrames.back();

			currentFrame = (int)(m_time * profile.TPS) + currentOffset;

			if (framesData.size() > 0) {
				while (framesData.size() >= currentFrame && framesData.size() != 0) {
					framesData.pop_back();
				}
			}

			if (pushes.size() > 0) {
				while (pushes.back() >= currentFrame && pushes.size() != 0) {
					pushData.pop_back();
					pushes.pop_back();
				}
			}

			if (releases.size() > 0) {
				while (releases.back() >= currentFrame && releases.size() != 0) {
					releaseData.pop_back();
					releases.pop_back();
				}
			}

			if (pushing) {
				pushData.push_back(AmethystReplay::create());
				pushes.push_back(currentFrame);
			}

		} else {
			currentPindex = 0;
			currentRindex = 0;
			currentIndex = 0;
			currentFrame = 0;
			currentOffset = 0;
			if (profile.replay) GJBaseGameLayer::get()->releaseButton(1, true);
		}
		if (m_checkpoints->count() == 0) {
        	g_activated_objects.clear();
        	g_activated_objects_p2.clear();
        	g_orbCheckpoints.clear();
    	} else {
			if (Crystal::profile.practiceorbfix && m_isPracticeMode) {
				const auto [p1, p2] = g_orbCheckpoints.back();
        		g_activated_objects.erase(
            		g_activated_objects.begin() + p1,
            		g_activated_objects.end()
        		);
        		g_activated_objects_p2.erase(
            		g_activated_objects_p2.begin() + p2,
            		g_activated_objects_p2.end()
        		);
        		for (const auto& object : g_activated_objects) {
            		object->m_hasBeenActivated = true;
        		}
        		for (const auto& object : g_activated_objects_p2) {
            		object->m_hasBeenActivatedP2 = true;
        		}
			}
    	}
		if (profile.cheatIndicate) {
			bad = "Not Cheating";
			g_cheating->setColor(ccc3(0,255,0));
		}
		if (profile.runFrom) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from %.0lf%%", start);
			g_run->setString(str);
		}
		if (profile.bestRun) {
			bestStart2 = (m_player1->getPositionX() / m_levelLength) * 100;
			if ((bestEnd2 - bestStart2) > (bestEnd - bestStart)) {
				bestStart = bestStart2;
				bestEnd = bestEnd2;
			}
			display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);
			g_bestRun->setString(display.c_str());
		}
		frames = noclipped_frames = noclip_deaths = 0;
		would_die = false;
	}

    void destroyPlayer(PlayerObject* p, GameObject* g) {
		if (g == m_antiCheatObject) {
			return PlayLayer::destroyPlayer(p,g);
		}
		would_die = true;
		if (profile.resetOnAccuracy) {
			auto accu = (float)(frames-noclipped_frames) / (float)frames;
			if (accu * 100 <= profile.resetAcc) {
				frames = noclipped_frames = noclip_deaths = 0;
				resetLevel();
				//char str[20];
				//sprintf(str, "%.2f%%", profile.resetAcc);
				//if (profile.noclipAcc) reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(str);
			}
		}
		if (profile.resetOnDeath) {
			if (noclip_deaths >= profile.resetDeath) {
				frames = noclipped_frames = noclip_deaths = 0;
				resetLevel();
				//if (profile.noclipDeath) g_death->setString(std::to_string(noclip_deaths).c_str());
			}
		}
		if (profile.anticheat) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
		}
		if (Crystal::profile.noclip && !Crystal::profile.noclipP2 && Crystal::profile.noclipP1) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (Crystal::profile.noclip && Crystal::profile.noclipP2 && !Crystal::profile.noclipP1) {
			if (p == m_player1) PlayLayer::destroyPlayer(p,g);

		} 
		if (!Crystal::profile.noclip || (Crystal::profile.noclip && !Crystal::profile.noclipP2 && !Crystal::profile.noclipP1)) {
			PlayLayer::destroyPlayer(p,g);
		}
	}

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

        if (profile.macroStatus) {
            if (profile.replay && !rendering) {
                std::string status = "Playing: " + std::to_string(currentPindex) + "/" + std::to_string(pushes.size()) + " (Frame " + std::to_string((int)(m_time * profile.TPS + currentOffset)) + ")";
                g_macro->setString(status.c_str());
            } else if (profile.record) {
                std::string status = "Recording: Macro Frame " + std::to_string((int)(m_time * profile.TPS + currentOffset));
                g_macro->setString(status.c_str());
            } else if (profile.replay && rendering) {
                std::string status = "Rendering: Video Frame " + std::to_string((int)(m_time * 60));
                g_macro->setString(status.c_str());
            }
        }

        PlayLayer::checkCollisions(p, g);
		g_message->setVisible(profile.customMessage);
		g_jumps->setVisible(profile.jumps);
		g_atts->setVisible(profile.attempts);
		g_run->setVisible(profile.runFrom);
		g_bestRun->setVisible(profile.bestRun);
		g_levelInfo->setVisible(profile.lvlData);
		g_clicks->setVisible(profile.cps);
		g_cheating->setVisible(profile.cheatIndicate);
		g_tatts->setVisible(profile.totalAtt);
		g_death->setVisible(profile.lastDeath);
		font->setVisible(profile.noclipDeath);
		text->setVisible(profile.noclipAcc);
		g_macro->setVisible(profile.macroStatus);
		g_clock->setVisible(profile.clock);

        if (p == m_player1) {
            drawer->addToPlayer1Queue(m_player1->getObjectRect());
            //newQueue.push_back(m_player1->getObjectRect());
        }
        if (p == m_player2) {
            drawer->addToPlayer2Queue(m_player2->getObjectRect());
        }
	}

    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		double percent = (m_player1->getPositionX() - 50 / m_levelLength) * 100;
		if (((int)percent == Crystal::profile.autoresetnum) && profile.autoreset) {
			resetLevel();
		}
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
		newthing << CrystalClient::getRenderPath(true);
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
		static_cast<cocos2d::CCNode*>(PlayLayer::get())->visit();
		renderer->end();

		auto img = renderer->newCCImage(true);
		CGImageWriteToFile(CGImageFromCCImage(img));    
	}

    void update(float f4) {
		if (g >= 360)
			g = 0;
		else
			g += profile.rainbowspeed;
		col = CrystalClient::get()->getRainbow(0);
		colInverse = CrystalClient::get()->getRainbow(180);

		frames += f4;

		if (would_die && !lastDeath) {
			if (profile.noclipDeath) {
				noclip_deaths++;
			}
		}

		lastDeath = would_die;

		if (would_die) {
			noclipped_frames += f4;
			would_die = false;
			if (opacity < 70) {
				opacity += 10;
				if (Crystal::profile.tintOnDeath) noclipRed->setOpacity(opacity);
			}
		} else {
			if (opacity > 0) {
				opacity -= 10;
				noclipRed->setOpacity(opacity);
			}
		}

		if (m_player1) {
			if (Crystal::profile.rainbowP1) m_player1->setColor(col);
			if (Crystal::profile.rainbowP2) m_player1->setSecondColor(colInverse);
			if (m_player1->m_waveTrail)
				if (Crystal::profile.rainbowP1wave) m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			if (Crystal::profile.rainbowP2) m_player2->setColor(colInverse);
			if (Crystal::profile.rainbowP1) m_player2->setSecondColor(col);
			if (m_player2->m_waveTrail)
				if (Crystal::profile.rainbowP2wave) m_player2->m_waveTrail->setColor(colInverse);
		}

		if (profile.noclipAcc) {
			percent = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		if (profile.noclipAcc) {
            char ok[20];
            auto accu = (float)(frames - noclipped_frames) / (float)frames;
            sprintf(ok, "%.2f%%", accu * 100);
            reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
        }
		if (profile.customMessage) {
			g_message->setString(profile.message);
		}
		if (profile.cheatIndicate) {
			if (profile.noclip || profile.speed < 1 || Crystal::profile.mirror || Crystal::profile.framestep || Crystal::profile.autoclick || Crystal::profile.layout) {
				bad = "Cheating";
				g_cheating->setColor(ccc3(155,0,0));
			}

			g_cheating->setString(bad.c_str());

		}
		if (profile.clock) {
			auto t = std::time(nullptr);
			std::tm tm = *std::localtime(&t);

			std::ostringstream oss;
			oss << std::put_time(&tm, "%H:%M:%S");
			auto clstr = oss.str();

			g_clock->setString(clstr.c_str());
		}
		if (profile.noclipDeath) {
			std::string nd = "Noclip Deaths: " + std::to_string(noclip_deaths);
			font->setString(nd.c_str());
		}
		if (profile.jumps) {
			std::string nd = "Total Jumps: " + std::to_string(m_level->m_jumps);
			g_jumps->setString(nd.c_str());
		}
		if (profile.cps) {
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
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
		if (profile.attempts) {
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);
		}
		if (profile.totalAtt) {
			std::string at = "Global Atts: " + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
		}
		if (profile.lastDeath) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death: %.0lf%%", start);
			g_death->setString(str);
		}
        drawer->clear();

		if (Crystal::profile.respawnfix) {
			if (!smoothOut) {
				return update(f4);
			}

			float time = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();
			if (smoothOut != 0 && f4 - time < 1) {
				smoothOut --;
			}

			PlayLayer::update(time);
		} else {
			if (!profile.framestep || (Crystal::profile.framestep && shouldUpdate)) {
				PlayLayer::update(f4);
				//if (rendering) recordOverride();
			}
		}

		currentFrame = (int)(m_time * profile.TPS) + currentOffset;

        if (profile.record && lastTime != (int)(m_time * 60)) {
			framesData.push_back(AmethystReplay::create());
			lastTime = (int)(m_time * 60);
		}

        if (profile.replay && pushes.size() > 0 && ((m_player1->getPositionX() / m_levelLength) * 100) <= 100) {
            if (currentPindex > pushes.size()) currentPindex--;
            if (currentRindex > releases.size()) currentRindex--;

            if (pushes[currentPindex] <= currentFrame) {
                GJBaseGameLayer::get()->pushButton(1, true);
                if (currentMacroType == 1) {
                    //pushData[currentPindex].apply(GJBaseGameLayer::get()->m_player1);
                }
                currentPindex++;
            }

            if (releases[currentRindex] <= currentFrame) {
                GJBaseGameLayer::get()->releaseButton(1, true);
                if (currentMacroType == 1) {
                    //releaseData[currentRindex].apply(GJBaseGameLayer::get()->m_player1);
                }
                currentRindex++;
            }
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
		if (Crystal::profile.practiceorbfix) g_orbCheckpoints.push_back({g_activated_objects.size(), g_activated_objects_p2.size()});
		PlayLayer::markCheckpoint();
		if (!PlayLayer::get()->m_isDead) {
            checkpoints.push_back(store());
            checkpointFrames.push_back(currentFrame);
        }
	}

	void removeLastCheckpoint() {
		if (Crystal::profile.practiceorbfix) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		checkpoints.pop_back();
        checkpointFrames.pop_back();
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

    void onQuit() {
		//FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (withAudio) {
			lastTime = 0;
			std::string rendercmd = "ffmpeg -framerate 60 -y -i " + CrystalClient::getRenderPath(true) + "frame_%4d.png -i " + (std::string)PlayLayer::get()->m_level->getAudioFileName() + " -shortest -pix_fmt yuv420p " + CrystalClient::getRenderPath(true) + "output.mp4";
			std::string fullcmd = "osascript -e 'tell app \"Terminal\" to do script \"" + rendercmd + "\"'";
			auto renderprocess = system(fullcmd.c_str());
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

    static inline tulip::HitboxNode* drawer;

	bool init(GJGameLevel* gl) {
		//leftDisplay = 0;
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (Crystal::profile.startpos) {
			rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_startPosIndex = -1;
			g_startPoses = {};
			
		}
		if (Crystal::profile.checkpointswitch) {
			CPrightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			CPleftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_checkpointText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_checkpointIndex = -1;
			g_checkpointsIG = {};
			
		}
		g_message = CCLabelBMFont::create(profile.message, "bigFont.fnt");
		g_jumps = CCLabelBMFont::create("Total Jumps: 0", "bigFont.fnt");
		g_atts = CCLabelBMFont::create("Attempts: 0", "bigFont.fnt");
		g_run = CCLabelBMFont::create("Run from ???", "bigFont.fnt");
		g_bestRun = CCLabelBMFont::create("Best Run: 0 to 0", "bigFont.fnt");
		g_levelInfo = CCLabelBMFont::create("Unnamed (No ID)", "bigFont.fnt");
		g_clicks = CCLabelBMFont::create("?? Clicks", "bigFont.fnt");
		clickscount = 0;
		g_cheating = CCLabelBMFont::create("Not Cheating", "bigFont.fnt");
		g_tatts = CCLabelBMFont::create("Global Atts: ??", "bigFont.fnt");
		g_death = CCLabelBMFont::create("Last Death: ???", "bigFont.fnt");
		font = CCLabelBMFont::create("Noclip Deaths: ???", "bigFont.fnt");
		text = CCLabelBMFont::create("100%", "bigFont.fnt");
		g_macro = CCLabelBMFont::create("Playing: 0/0", "bigFont.fnt");
		g_clock = CCLabelBMFont::create("00:00:00 AM", "bigFont.fnt");
        drawer = tulip::HitboxNode::create();

		ss = 0;
		PlayLayer::init(gl);

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

		noclipRed = CCSprite::createWithSpriteFrameName("block005b_05_001.png");
		noclipRed->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2});
		noclipRed->setScale(1000.0f);
		noclipRed->setColor(ccc3(255,0,0));
		noclipRed->setOpacity(0);
		noclipRed->setZOrder(1000);
		m_UILayer->addChild(noclipRed);

        m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = Crystal::profile.onDeath;
		drawer->m_drawTrail = Crystal::profile.drawTrail;
		s_onlyHitboxes = false;
		if (s_showOnDeath) s_drawOnDeath = false;

		if (profile.trajectory) drawer->createPlayersForTrajectory();

		currentFrame = 0;
		
		if (Crystal::profile.startpos) {
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
			g_startPosText->setScale(0.5);
			g_startPosText->setOpacity(50);
			rightButton->::Main::setPosition(220 , corner - 275);
			rightButton->setScale(0.5);
			
			rightButton->setOpacity(50);
			leftButton->::Main::setPosition(310 , corner - 275);
			leftButton->setRotation(180);
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
		if (Crystal::profile.checkpointswitch) {
			g_checkpointText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				//g_checkpointText->setPosition(245 , corner - 275);
			}
			g_checkpointText->setScale(0.5);
			g_checkpointText->setOpacity(50);
			CPrightButton->::Main::setPosition(220 , corner - 275);
			CPrightButton->setScale(0.5);

			CPrightButton->setOpacity(50);
			CPleftButton->::Main::setPosition(310 , corner - 275);
			CPleftButton->setRotation(180);
			CPleftButton->setScale(0.5);

			CPleftButton->setOpacity(50);

			if (!m_isPracticeMode) {/*
				g_checkpointText->setVisible(false);
				CPrightButton->setVisible(false);
				CPleftButton->setVisible(false);
				*/
			}
			addChild(g_checkpointText, 1000);
			addChild(CPrightButton, 1000);
			addChild(CPleftButton, 1000);
		}
		if (Crystal::profile.progressBar) {
			m_percentLabel->setPositionX(CCDirector::sharedDirector()->getWinSize().width / 2);
		}
		if (profile.runFrom) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from: %.0lf%%", start);
			g_run->setString(str);
		}
		if (profile.jumps) {
			std::string po = "Total Jumps:" + std::to_string(gl->m_jumps);
			g_jumps->setString(po.c_str());
		}
		if (profile.totalAtt) {
			std::string at = "Global Atts:" + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
		}
		if (profile.lastDeath) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death:%.0lf%%", start);
			g_death->setString(str);
		}
		if (profile.attempts) {
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);
		}
		if (profile.bestRun) {
			bestEnd = 0;
			bestStart = 0;
			bestEnd2 = 0;
			bestStart2 = 0;
			bestStart = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		if (profile.lvlData) {
			std::string display;
			std::string levelName = gl->m_levelName;
			std::string levelAuthor = gl->m_creatorName;
			std::string levelID = std::to_string(gl->m_levelID);
			if (hideID) {
				levelID = "--------";
			} else if (gl->m_levelID < 22 && gl->m_levelID > 0) {
				levelAuthor = "RobTop"; // this wasnt working from Polargeist (3) to Cycles (9) so i had to do that lmao
			} else if (levelID == "0") {
				levelID = "Copy";
			}
			if (author) {
				display = levelName + " by " + levelAuthor + " (" + levelID + ")";
			} else {
				display = levelName + " (" + levelID + ")";
			}
			g_levelInfo->setString(display.c_str());
		}
		if (profile.cps) {
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
		}
		if (profile.noclipAcc){
			text->setTag(31403);
		}
		if (profile.macroStatus) {
			std::string status = "Playing: 0/" + std::to_string(pushes.size());
			g_macro->setString(status.c_str());
		}
		CrystalClient::get()->arrangeText(13, this);
		return true;
	}
};

class $(UILayer) {
	void customMod(int current) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		if (current == 0) {
			Crystal::profile.noclip = !Crystal::profile.noclip;
		} else if (current == 1) {
			//autoKill = !autoKill;
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
			PlayLayer::get()->markCheckpoint();
		} else if (current == 11) {
			PlayLayer::get()->removeLastCheckpoint();
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

template<>
struct json::Serialize<CrystalProfile> {
    static json::Value to_json(CrystalProfile const& value) {
        auto ret = json::Object();
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
        ret["autoldm"] = Crystal::profile.autoldm;
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
        return ret;
    }
    
};

void Crystal::saveMods(CrystalProfile const& data) {
    std::fstream jsonOutFile;
	jsonOutFile.open(geode::Mod::get()->getSaveDir().append("GH_config.json"), std::ios::out);
	jsonOutFile << json::Serialize<CrystalProfile>::to_json(profile).dump();
	jsonOutFile.close();
}

CrystalProfile Crystal::loadMods() {
    std::fstream input(geode::Mod::get()->getSaveDir().append("GH_config.json"));
    if (input && !input.eof()) {
		auto json = json2::parse(input);
        return CrystalProfile {
            .noclip = json["noclip"],
            .noclipP1 = json["noclipP1"],
            .noclipP2 = json["noclipP2"],
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
            .autoldm = json["autoldm"],
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
            .ACrelframe = json["ACrelframe"]
        };
    }
    return Crystal::profile;
}