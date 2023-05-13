#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "CrystalClient.hpp"
#include <imgui.h>
#include "ImGui.hpp"
#include "Includes.hpp"
#include "Hacks.hpp"
#include "CrystalTheme.hpp"

using namespace geode::prelude;

using namespace Shortcuts;
using namespace Variables;
using namespace Crystal;
using namespace AmethystReplay;

void CrystalClient::drawGUI() {
	ImGuiWindowFlags window_flags = 0;
	if (theme.invisBG) window_flags |= ImGuiWindowFlags_NoBackground;
	if (theme.titlebar) window_flags |= ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Player", NULL, window_flags);
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

	ImGui::Begin("Icon", NULL, window_flags);
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

	ImGui::Begin("Level", NULL, window_flags);
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
    ImGui::Begin("Display", NULL, window_flags);
	CrystalClient::ImToggleable("Testmode Label", &Crystal::profile.testmode);
	CrystalClient::ImExtendedToggleable("Custom Message", &Crystal::profile.customMessage);
	if (ImGui::BeginPopupModal("Custom Message", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::InputTextWithHint("Message", "Custom Message", profile.message, IM_ARRAYSIZE(profile.message));
		ImGui::PushItemWidth(200);
		if (ImGui::Button("Move Up")) {
			GUIpositions[0]--;
			GUIpositions[1]++;
		}
		ImGui::SameLine();
		if (ImGui::Button("Move Down")) {
			GUIpositions[0]++;
			GUIpositions[1]--;
		}
		ImGui::PopItemWidth();
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("FPS Display", &Crystal::profile.fps);
	if (ImGui::BeginPopupModal("FPS Display", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		if (ImGui::Button("Move Up")) {
			GUIpositions[1]--;
			GUIpositions[2]++;
		}
		ImGui::SameLine();
		if (ImGui::Button("Move Down")) {
			GUIpositions[1]++;
			GUIpositions[2]--;
		}
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Clicks", &Crystal::profile.cps);
	if (ImGui::BeginPopupModal("Clicks", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		if (ImGui::Button("Move Up")) {
			GUIpositions[2]--;
			GUIpositions[3]++;
		}
		ImGui::SameLine();
		if (ImGui::Button("Move Down")) {
			GUIpositions[2]++;
			GUIpositions[3]--;
		}
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Jumps", &Crystal::profile.jumps);
	if (ImGui::BeginPopupModal("Jumps", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		if (ImGui::Button("Move Up")) {
			GUIpositions[3]--;
			GUIpositions[4]++;
		}
		ImGui::SameLine();
		if (ImGui::Button("Move Down")) {
			GUIpositions[3]++;
			GUIpositions[4]--;
		}
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	CrystalClient::ImExtendedToggleable("Cheat Indicator", &Crystal::profile.cheatIndicate);
	CrystalClient::ImExtendedToggleable("Last Death", &Crystal::profile.lastDeath);
	CrystalClient::ImExtendedToggleable("Attempts", &Crystal::profile.attempts);
	CrystalClient::ImExtendedToggleable("Best Run", &Crystal::profile.bestRun);
	CrystalClient::ImExtendedToggleable("Run From", &Crystal::profile.runFrom);
	CrystalClient::ImExtendedToggleable("Noclip Accuracy", &Crystal::profile.noclipAcc);
	CrystalClient::ImExtendedToggleable("Noclip Deaths", &Crystal::profile.noclipDeath);
	CrystalClient::ImExtendedToggleable("Total Attempts", &Crystal::profile.totalAtt);
	CrystalClient::ImExtendedToggleable("Level Name and ID", &Crystal::profile.lvlData);
	CrystalClient::ImExtendedToggleable("Macro Status", &Crystal::profile.macroStatus);
	CrystalClient::ImExtendedToggleable("Clock", &Crystal::profile.clock);
	if (ImGui::BeginPopupModal("Clock", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImToggleable("In-Game Time", &Crystal::profile.igt);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
    ImGui::End();
    ImGui::Begin("Customization", NULL, window_flags);
    ImGui::ColorEdit4("Accent Color", theme.LightColour, ImGuiColorEditFlags_NoInputs);
    ImGui::ColorEdit4("Base Color", theme.BGColour, ImGuiColorEditFlags_NoInputs);
    CrystalClient::ImToggleable("RGB Accent Color", &theme.RGBAccent);
    CrystalClient::ImToggleable("Borders", &theme.borders);
    CrystalClient::ImToggleable("Rounded Windows", &theme.rounded);
	CrystalClient::ImToggleable("No Title Bar", &theme.titlebar);
	CrystalClient::ImToggleable("Invisible BG", &theme.invisBG);
	CrystalClient::ImExtendedToggleable("Different Titlebar Color", &theme.diffTitleBar);
	if (ImGui::BeginPopupModal("Different Titlebar Color", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::ColorEdit4("Titlebar Color", theme.TitleColour, ImGuiColorEditFlags_NoInputs);
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::InputFloat("Border Rounding", &theme.borderRounding);
	ImGui::InputFloat("Scrollbar Size", &theme.scrollbarSize);
	ImGui::InputFloat("Scrollbar Rounding", &theme.scrollbarRounding);
	ImGui::InputText("##Theme Name", themeName, IM_ARRAYSIZE(themeName));
	if (ImGui::Button("Save Theme")) Crystal::saveTheme(theme, std::string(themeName));
	ImGui::SameLine();
	if (ImGui::Button("Load Theme")) theme = Crystal::loadTheme(std::string(themeName));
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
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]", NULL, window_flags);
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
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + (std::string)profile.macroname + ".thyst";
		std::fstream myfile(filename.c_str(), std::ios::app);
		myfile << P1pushes.size();
		myfile << "\n";
		for (size_t i = 0; i < P1pushes.size(); i++)
		{
			myfile << std::setprecision(10) << std::fixed << P1pushes[i];
			myfile << "\n";
		}
		myfile << P1releases.size();
		myfile << "\n";
		for (size_t i = 0; i < P1releases.size(); i++)
		{
			myfile << std::setprecision(10) << std::fixed << P1releases[i];
			myfile << "\n";
		}
		myfile << P2pushes.size();
		myfile << "\n";
		for (size_t i = 0; i < P2pushes.size(); i++)
		{
			myfile << std::setprecision(10) << std::fixed << P2pushes[i];
			myfile << "\n";
		}
		myfile << P2releases.size();
		myfile << "\n";
		for (size_t i = 0; i < P2releases.size(); i++)
		{
			myfile << std::setprecision(10) << std::fixed << P2releases[i];
			myfile << "\n";
		}
	}
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
		std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/Amethyst/Macros/" + (std::string)profile.macroname + ".thyst";
        std::string line;
		std::fstream file;
		file.open(filename, std::ios::in);
		if (file.is_open()) {
			getline(file, line);
			int len;
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				P1pushes.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				P1releases.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				P2pushes.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				P2releases.push_back(stof(line));
			}
			file.close();
		}
	}
    ImGui::SameLine();
    if (ImGui::Button("Clear Macro")) {
        P1pushes.clear();
		P1releases.clear();
		P2pushes.clear();
		P2releases.clear();
		checkpointFrames.clear();
		P1checkpoints.clear();
		P2checkpoints.clear();
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
	ImGui::Begin("Variable Changer", NULL, window_flags);
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
	ImGui::Begin("Internal Renderer", NULL, window_flags);
	CrystalClient::ImToggleable("Render Recording", &rendering);
	CrystalClient::ImToggleable("Include Sound", &withAudio);
	if (ImGui::Button("Test Renderer")) {
		std::string systemCMD = "cd " + (std::string)renderer + " && ./ffmpeg";
		std::string systemFullcmd = "osascript -e 'tell app \"Terminal\" to do script \"" + systemCMD + "\"'";
		system(systemFullcmd.c_str());
	}
	ImGui::End();
}

void CrystalClient::addTheme() {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colours = ImGui::GetStyle().Colors;

	auto io = ImGui::GetIO();

	if (io.DeltaTime <= 0.0f) io.DeltaTime = 0.00001f;

    if (theme.RGBAccent) {
        theme.LightColour[0] = theme.LightColour[0] + theme.rDir;
        theme.LightColour[1] = theme.LightColour[1] + theme.gDir;
        theme.LightColour[2] = theme.LightColour[2] + theme.bDir;

        if (theme.LightColour[0] >= 1 || theme.LightColour[0] <= 0) { theme.rDir = theme.rDir * -1; }
        if (theme.LightColour[1] >= 1 || theme.LightColour[1] <= 0) { theme.gDir = theme.gDir * -1; }
        if (theme.LightColour[2] >= 1 || theme.LightColour[2] <= 0) { theme.bDir = theme.bDir * -1; }
    }

    theme.DarkColour[0] = (theme.LightColour[0] * 0.5f);
    theme.DarkColour[1] = (theme.LightColour[1] * 0.5f);
    theme.DarkColour[2] = (theme.LightColour[2] * 0.5f);
    theme.DarkColour[3] = theme.LightColour[3];
    theme.VeryLightColour[0] = (theme.LightColour[0] * 1.5f);
    theme.VeryLightColour[1] = (theme.LightColour[1] * 1.5f);
    theme.VeryLightColour[2] = (theme.LightColour[2] * 1.5f);
    theme.VeryLightColour[3] = theme.LightColour[3];

    style->FrameRounding = 4.0f;
    style->GrabRounding = 4.0f;
    style->Alpha = 1.f;
    style->WindowRounding = theme.borderRounding;
    style->FrameRounding = 4.f;
    style->ScrollbarSize = theme.scrollbarSize;
    style->ScrollbarRounding = theme.scrollbarRounding;
    style->PopupRounding = theme.borderRounding;
    style->WindowBorderSize = 1.5f;
    colours[ImGuiCol_TitleBg] = CrystalTheme::RGBAtoIV4(theme.diffTitleBar ? theme.TitleColour : theme.BGColour);
    colours[ImGuiCol_TitleBgActive] = CrystalTheme::RGBAtoIV4(theme.BGColour);
    colours[ImGuiCol_WindowBg] = CrystalTheme::RGBAtoIV4(theme.BGColour);
    colours[ImGuiCol_Border] = CrystalTheme::RGBAtoIV4(theme.borders ? theme.LightColour : theme.BGColour);
    colours[ImGuiCol_FrameBg] = CrystalTheme::RGBAtoIV4(theme.DarkColour);
    colours[ImGuiCol_FrameBgHovered] = CrystalTheme::RGBAtoIV4(theme.DarkColour);
    colours[ImGuiCol_FrameBgActive] = CrystalTheme::RGBAtoIV4(theme.LightColour);
    colours[ImGuiCol_PlotHistogram] = CrystalTheme::RGBAtoIV4(theme.LightColour);
    colours[ImGuiCol_Button] = CrystalTheme::RGBAtoIV4(theme.LightColour);
    colours[ImGuiCol_ButtonHovered] = CrystalTheme::RGBAtoIV4(theme.VeryLightColour);
    colours[ImGuiCol_Header] = CrystalTheme::RGBAtoIV4(theme.DarkColour);
    colours[ImGuiCol_HeaderHovered] = CrystalTheme::RGBAtoIV4(theme.LightColour);
    colours[ImGuiCol_HeaderActive] = CrystalTheme::RGBAtoIV4(theme.VeryLightColour);
    colours[ImGuiCol_SliderGrab] = CrystalTheme::RGBAtoIV4(theme.LightColour);
    colours[ImGuiCol_SliderGrabActive] = CrystalTheme::RGBAtoIV4(theme.VeryLightColour);
    colours[ImGuiCol_CheckMark] = CrystalTheme::RGBAtoIV4(theme.VeryLightColour);
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
	int anchor = 0;
	setAnchoredPosition(g_message, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.customMessage) anchor++;
	setAnchoredPosition(g_cheating, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.cheatIndicate) anchor++;
	setAnchoredPosition(g_run, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.runFrom) anchor++;
	setAnchoredPosition(g_jumps, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.jumps) anchor++;
	setAnchoredPosition(g_tatts, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.totalAtt) anchor++;
	setAnchoredPosition(g_death, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.lastDeath) anchor++;
	setAnchoredPosition(font, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.noclipDeath) anchor++;
	setAnchoredPosition(g_atts, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.attempts) anchor++;
	setAnchoredPosition(g_bestRun, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.bestRun) anchor++;
	setAnchoredPosition(g_levelInfo, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.lvlData) anchor++;
	setAnchoredPosition(g_clicks, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.cps) anchor++;
	setAnchoredPosition(text, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.noclipAcc) anchor++;
	setAnchoredPosition(g_macro, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.macroStatus) anchor++;
	setAnchoredPosition(g_clock, GUIpositions[anchor], reinterpret_cast<CCLayer*>(menulay));
	if (profile.clock) anchor++;
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
		if (down && key == KEY_G && profile.framestep && PlayLayer::get()) {
			for (int i = 0; i < 10; i++) {
				shouldUpdate = true;
				PlayLayer::get()->update(1.f / profile.TPS);
				shouldUpdate = false;
			}
		}
        if (!CrystalClient::get()->isRendering) return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};

$execute {
	CrystalClient::get()->initPatches();
}

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
		profile = Crystal::loadMods();
		theme = Crystal::loadTheme("GH_theme.json");
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
		}
		if ((profile.TPSbypass || profile.replay || profile.record || profile.FPSbypass) && PlayLayer::get() && !PlayLayer::get()->m_isPaused) {
			auto dir = CCDirector::sharedDirector();

			//if (record) f3 *= speedhack;

			float spf = (float)dir->getAnimationInterval() * (60 / profile.TPS);
			auto nspeedhack = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
    
			const float newdt = 1.f / profile.TPS / nspeedhack;
			const float otherdt = 1.f / profile.FPS / nspeedhack;

			float totaldt = 1.f / (profile.FPS * (profile.TPS / 60)) / nspeedhack;

			if (rendering) renderTime += totaldt;

			if (profile.deltaLock) return CCScheduler::update(totaldt);

			g_disable_render = true;

			if (profile.FPSbypass) cocos2d::CCApplication::sharedApplication()->setAnimationInterval(otherdt);
			else cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.f / 60.f);

			if (profile.TPSbypass || profile.FPSbypass) {
				const int totaltimes = std::min(static_cast<int>((f3 + t_left_over) / totaldt), 100); // limit it to 100x just in case
				for (int i = 0; i < totaltimes; ++i) {
					if (i == totaltimes - 1)
						g_disable_render = false;
					CCScheduler::update(totaldt);
				}
				t_left_over += f3 - totaldt * totaltimes;
			} else {
				CCScheduler::update(f3);
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

	bool init(GJGameLevel* ed) {
        EditLevelLayer::init(ed);

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(GJGameLevel) {
	void savePercentage(int percentage, bool practice, int clicks, int attemptTime, bool vfDChk) {
		if (profile.safeMode && !profile.autoSafeMode) return;
		if (profile.safeMode && profile.autoSafeMode && bad == "Cheating") return;
		GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, vfDChk);
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
		if (b) P1pushing = true;
		if (!b) P2pushing = true;
		if (profile.record) {
            if (b) P1pushes.push_back(currentFrame);
			if (!b) P2pushes.push_back(currentFrame);
        }
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
	}

	void releaseButton(int i, bool b) {
		if (b) P1pushing = false;
		if (!b) P2pushing = false;
		if (profile.record) {
            if (b) P1releases.push_back(currentFrame);
			if (!b) P2releases.push_back(currentFrame);
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

	bool init(GJGameLevel* level) {
        LevelInfoLayer::init(level);
        
        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
 
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

	if (PlayLayer::get()->m_isPracticeMode && profile.record) {
        if (P1checkpoints.size() > 0) P1checkpoints.back().apply(GJBaseGameLayer::get()->m_player1);
		if (P2checkpoints.size() > 0) P2checkpoints.back().apply(GJBaseGameLayer::get()->m_player2);

        if (checkpointFrames.size() == 0) checkpointFrames.push_back(0);
        currentFrame = checkpointFrames.back();

        if (P1pushes.size() > 0) {
            while (P1pushes.back() >= currentFrame && P1pushes.size() != 0) {
                P1pushes.pop_back();
            }
        }

        if (P1releases.size() > 0) {
            while (P1releases.back() >= currentFrame && P1releases.size() != 0) {
                P1releases.pop_back();
            }
        }

		if (P2pushes.size() > 0) {
            while (P2pushes.back() >= currentFrame && P2pushes.size() != 0) {
                P2pushes.pop_back();
            }
        }

        if (P2releases.size() > 0) {
            while (P2releases.back() >= currentFrame && P2releases.size() != 0) {
                P2releases.pop_back();
            }
        }

        if (P1pushing) P1pushes.push_back(currentFrame);
		if (P2pushing) P2pushes.push_back(currentFrame);

    } else {
        currentP1index = 0;
        currentR1index = 0;
		currentP2index = 0;
        currentR2index = 0;
        currentFrame = 0;
        if (profile.replay) GJBaseGameLayer::get()->releaseButton(1, true);
		if (profile.replay) GJBaseGameLayer::get()->releaseButton(1, false);
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
                std::string status = "Playing: " + std::to_string(currentP1index) + "/" + std::to_string(P1pushes.size()) + " (Frame " + std::to_string((int)(m_time * profile.TPS)) + ")";
                g_macro->setString(status.c_str());
            } else if (profile.record) {
                std::string status = "Recording: Macro Frame " + std::to_string((int)(m_time * profile.TPS));
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
		if (g >= 360)
			g = 0;
		else
			g += profile.rainbowspeed;
		col = CrystalClient::get()->getRainbow(0);
		colInverse = CrystalClient::get()->getRainbow(180);

		CGEventRef ourEvent = CGEventCreate(NULL);
		auto point = CGEventGetLocation(ourEvent);
		CFRelease(ourEvent);

		if (!CrystalClient::get()->isRendering && profile.lockCursor && !m_hasCompletedLevel) CGWarpMouseCursorPosition(point);

		frames += f4;

		if (would_die && !lastDeath) {
			if (profile.noclipDeath) {
				noclip_deaths++;
			}
		}

		lastDeath = would_die;

		if (would_die && !m_isDead && !m_hasCompletedLevel) {
			noclipped_frames += f4;
			would_die = false;
			if (opacity < 70) {
				opacity += 10;
				if (Crystal::profile.tintOnDeath) noclipRed->setOpacity(opacity);
			}
		} else {
			if (opacity > 0) {
				opacity -= 10;
				if (Crystal::profile.tintOnDeath) noclipRed->setOpacity(opacity);
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
			if (profile.noclip || profile.speed < 1 || Crystal::profile.mirror || Crystal::profile.framestep || Crystal::profile.autoclick || Crystal::profile.layout || Crystal::profile.record || Crystal::profile.replay || Crystal::profile.FPS > 360.0 || Crystal::profile.TPS > 360.0) {
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

		if (profile.record || profile.replay) f4 = 1.f / (profile.FPS * (profile.TPS / 60)) / speedhack;

		if (gameStarted) currentFrame += f4;

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
				if (rendering && lastTime != (int)(m_time * 60)) {
					captureScreen();
					lastTime = (int)(m_time * 60);
				}
			}
		}

		if (profile.replay && P1pushes.size() > 0 && currentR1index < P1releases.size()) {
			if (P1pushes[currentP1index] <= currentFrame && currentP1index < P1pushes.size()) {
				GJBaseGameLayer::get()->pushButton(1, true);
				currentP1index++;
			}

			if (P1releases[currentR1index] <= currentFrame && currentR1index < P1releases.size()) {
				GJBaseGameLayer::get()->releaseButton(1, true);
				currentR1index++;
			}

			if (P2pushes.size() > 0) {
				if (P2pushes[currentP2index] <= currentFrame && currentP2index < P2pushes.size()) {
					GJBaseGameLayer::get()->pushButton(1, false);
					currentP2index++;
				}

				if (P2releases[currentR2index] <= currentFrame && currentR2index < P2releases.size()) {
					GJBaseGameLayer::get()->releaseButton(1, false);
					currentR2index++;
				}
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
            P1checkpoints.push_back(store(m_player1));
			P2checkpoints.push_back(store(m_player2));
            checkpointFrames.push_back(currentFrame);
        }
	}

	void removeLastCheckpoint() {
		if (Crystal::profile.practiceorbfix) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		P1checkpoints.pop_back();
		P2checkpoints.pop_back();
        checkpointFrames.pop_back();
	}

    void startMusic() {
		CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
		CGEventRef saveCommandDown = CGEventCreateKeyboardEvent(source, (CGKeyCode)0x02, true);
		CGEventSetFlags(saveCommandDown, kCGEventFlagMaskCommand);
		CGEventSetFlags(saveCommandDown, kCGEventFlagMaskShift);
		CGEventRef saveCommandUp = CGEventCreateKeyboardEvent(source, (CGKeyCode)0x02, false);

		CGEventPost(kCGAnnotatedSessionEventTap, saveCommandDown);
		CGEventPost(kCGAnnotatedSessionEventTap, saveCommandUp);

		CFRelease(saveCommandUp);
		CFRelease(saveCommandDown);
		CFRelease(source);
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
		std::string renderprocess;
		//FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (withAudio) {
			lastTime = 0;
			std::string rendercmd = "cd " + (std::string)renderer + " && ./ffmpeg -framerate 60 -y -i " + (std::string)framesFol + "/frame_%4d.png -ss " + getOffsetTime(PlayLayer::get()->m_levelSettings->m_songOffset) + " -i " + (std::string)PlayLayer::get()->m_level->getAudioFileName() + " -t " + std::to_string(PlayLayer::get()->m_time) + " -pix_fmt yuv420p -vb 20M -c:v libx264 " + (std::string)renderer + "/" + std::to_string(PlayLayer::get()->m_level->m_levelID) + ".mp4";
			std::string fullcmd = "osascript -e 'tell app \"Terminal\" to do script \"" + rendercmd + "\"'";
			auto renderprocess = system(fullcmd.c_str());
			//renderprocess = exec(rendercmd);
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
		gameStarted = false;
		renderTime = 0;

		if (!ghc::filesystem::exists(framesFol)) {
			ghc::filesystem::create_directories(framesFol);
		} else {
			ghc::filesystem::remove_all(framesFol);
			ghc::filesystem::create_directory(framesFol);
		}

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
			std::string status = "Playing: 0/" + std::to_string(P1pushes.size());
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

class $modify(CreatorLayer) {
	virtual bool init() {
        CreatorLayer::init();

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
        LeaderboardsLayer::init(state);

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LocalLevelManager) {
	bool init() {
		LocalLevelManager::init();

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(ModifiedSearchLayer, LevelSearchLayer) {
	bool init() {
		LevelSearchLayer::init();

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

		auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
			return strncmp(lbl->getString(), "Trending", 8) == 0;
		})->getParent()->getParent()->getParent();

		auto bg = findFirstChildRecursive<CCNode>(this, [](CCNode* n) {
			return n->getContentSize().height == 115.0f;
		});

		findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* thing) {
			return strncmp(thing->getString(), "Filters", 7) == 0;
		})->removeFromParentAndCleanup(true);

		findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* thing) {
			return strncmp(thing->getString(), "Quick Search", 12) == 0;
		})->removeFromParentAndCleanup(true);

		auto mpos = menu->getPosition();
		auto bsize = bg->getContentSize();

		bg->setContentSize(CCSize(bsize.width, bsize.height + 35.0));
		menu->setPositionY(mpos.y - 17.5);

		auto button_sprite = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");
		auto button_sprite2 = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");

		auto demon_button = CCMenuItemSpriteExtra::create(button_sprite, this, menu_selector(ModifiedSearchLayer::onDemonList));
		auto demon_label = CCLabelBMFont::create("Demon List", "bigFont.fnt");
		auto demon_icon = CCSprite::createWithSpriteFrameName("rankIcon_all_001.png");

		demon_button->addChild(demon_label);
		demon_button->addChild(demon_icon);

		demon_label->setScale(0.55);
		demon_label->setPosition(ccp(70, 17));
		demon_icon->setPosition(ccp(140, 16));
		demon_button->setPosition(reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(0))->getPosition() + ccp(0, 35));


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

		menu->addChild(demon_button);
		menu->addChild(challenge_button);

        return true;
    }

	void onDemonList(CCObject*) {
		m_searchInput->onClickTrackNode(false);
		auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3141), ""));

		auto s = CCScene::create();
		s->addChild(p);
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
	}

	void onChallengeList(CCObject*) {
		m_searchInput->onClickTrackNode(false);
		auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3142), ""));

		auto s = CCScene::create();
		s->addChild(p);
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
	}
};

class $(GameLevelManager) {
	void ProcessHttpRequest(gd::string gdurl, gd::string gdquery, gd::string idk, int type) {
		std::string url(gdurl);
		std::string query(gdquery);

		if (url == "http://www.boomlings.com/database/getGJLevels21.php") {
			auto thing = atoi(query.substr(query.find("page=") + 5).c_str());
			if (query.find("type=3141") != std::string::npos) {
				url = std::string("http://absolllute.com/api/mega_hack/demonlist/page") + std::to_string(thing) + ".txt";
			} else if (query.find("type=3142") != std::string::npos) {
				url = std::string("http://absolllute.com/api/mega_hack/challengelist/page") + std::to_string(thing) + ".txt";
			}
		}

		GameLevelManager::ProcessHttpRequest(url, query, idk, type);
	}
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* search) {
		LevelBrowserLayer::init(search);

        if (profile.transparentBG) CrystalClient::get()->addTransparentBG(this);

        return true;
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
		ret["testmode"] = Crystal::profile.testmode;
		ret["customMessage"] = Crystal::profile.customMessage;
		ret["fps"] = Crystal::profile.fps;
		ret["cps"] = Crystal::profile.cps;
		ret["jumps"] = Crystal::profile.jumps;
		ret["cheatIndicate"] = Crystal::profile.cheatIndicate;
		ret["lastDeath"] = Crystal::profile.lastDeath;
		ret["attempts"] = Crystal::profile.attempts;
		ret["bestRun"] = Crystal::profile.bestRun;
		ret["runFrom"] = Crystal::profile.runFrom;
		ret["noclipAcc"] = Crystal::profile.noclipAcc;
		ret["noclipDeath"] = Crystal::profile.noclipDeath;
		ret["totalAtt"] = Crystal::profile.totalAtt;
		ret["lvlData"] = Crystal::profile.lvlData;
		ret["macroStatus"] = Crystal::profile.macroStatus;
		ret["clock"] = Crystal::profile.clock;
		ret["safeMode"] = Crystal::profile.safeMode;
		ret["autoSafeMode"] = Crystal::profile.autoSafeMode;
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
            .ACrelframe = json["ACrelframe"],
			.testmode = json["testmode"],
			.customMessage = json["customMessage"],
			.fps = json["fps"],
			.cps = json["cps"],
			.jumps = json["jumps"],
			.cheatIndicate = json["cheatIndicate"],
			.lastDeath = json["lastDeath"],
			.attempts = json["attempts"],
			.bestRun = json["bestRun"],
			.runFrom = json["runFrom"],
			.noclipAcc = json["noclipAcc"],
			.noclipDeath = json["noclipDeath"],
			.totalAtt = json["totalAtt"],
			.lvlData = json["lvlData"],
			.macroStatus = json["macroStatus"],
			.clock = json["clock"],
			.safeMode = json["safeMode"],
			.autoSafeMode = json["autoSafeMode"],
        };
    }
    return Crystal::profile;
}

template<>
struct json::Serialize<CrystalTheme> {
    static json::Value to_json(CrystalTheme const& value) {
        auto ret = json::Object();
        ret["BGColour-Red"] = value.BGColour[0];
        ret["BGColour-Green"] = value.BGColour[1];
        ret["BGColour-Blue"] = value.BGColour[2];
        ret["BGColour-Alpha"] = value.BGColour[3];
        ret["LightColour-Red"] = value.LightColour[0];
        ret["LightColour-Green"] = value.LightColour[1];
        ret["LightColour-Blue"] = value.LightColour[2];
        ret["LightColour-Alpha"] = value.LightColour[3];
        ret["TitleColour-Red"] = value.TitleColour[0];
        ret["TitleColour-Green"] = value.TitleColour[1];
        ret["TitleColour-Blue"] = value.TitleColour[2];
        ret["TitleColour-Alpha"] = value.TitleColour[3];
        ret["borderRounding"] = value.borderRounding;
        ret["scrollbarSize"] = value.scrollbarSize;
        ret["scrollbarRounding"] = value.scrollbarRounding;
        ret["RGBAccent"] = value.RGBAccent;
        ret["borders"] = value.borders;
        ret["rounded"] = value.rounded;
        ret["titlebar"] = value.titlebar;
        ret["invisBG"] = value.invisBG;
        ret["diffTitleBar"] = value.diffTitleBar;
        return ret;
    }
    
};

void Crystal::saveTheme(CrystalTheme const& data, std::string Sfilename) {
    std::fstream jsonOutFile;
	jsonOutFile.open(geode::Mod::get()->getConfigDir().append("Config").append(Sfilename), std::ios::out);
	jsonOutFile << json::Serialize<CrystalTheme>::to_json(data).dump();
	jsonOutFile.close();
}

CrystalTheme Crystal::loadTheme(std::string Lfilename) {
    std::fstream input(geode::Mod::get()->getConfigDir().append("Config").append(Lfilename));
    if (input && !input.eof()) {
		auto json = json2::parse(input);
        return CrystalTheme {
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
            .diffTitleBar = json["diffTitleBar"]
        };
    }
    return theme;
}