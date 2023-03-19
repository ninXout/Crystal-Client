#include "platform/platform.hpp"
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "CrystalClient.hpp"
#include "Hacks.hpp"
#include <imgui.h>
#include "ImGui.hpp"
#include "Amethyst.hpp"
#include "subprocess.hpp"
#include <iostream>

USE_GEODE_NAMESPACE();

void CrystalClient::toggle() {
    auto platform = reinterpret_cast<PlatformToolbox*>(PlayLayer::get());
    if (!m_visible) {
        platform->showCursor();
    }
    if (m_visible) {
		CrystalClient::get()->saveMods();
		CrystalClient::get()->saveShortcuts();
        if (PlayLayer::get() && !PlayLayer::get()->m_isPaused && !PlayLayer::get()->m_hasLevelCompleteMenu) {
			platform->hideCursor();
			//CrystalClient::get()->arrangeText(13);
		}
    }
    this->show(!m_visible);
}

void CrystalClient::saveShortcuts() {
	std::ofstream clear(Mod::get()->getSaveDir() / "shortcuts.cmp");
    clear << "";
    clear.close();
	std::fstream sfile;
	sfile.open(Mod::get()->getSaveDir() / "shortcuts.cmp", std::ios::app);
	sfile << activeKeys.size() << '\n';
	for (size_t i = 0; i < activeKeys.size(); i++) {
		sfile << activeKeys[i] << '\n';
		sfile << activeMods[i] << '\n';
	}
	sfile.close();
}

void CrystalClient::loadShortcuts() {
	activeKeys.clear();
	activeMods.clear();
	std::string line;
	std::fstream sfile;
    sfile.open(Mod::get()->getSaveDir() / "shortcuts.cmp", std::ios::in);
	if (sfile.is_open()) {
		getline(sfile, line);
		int len;
		len = stoi(line);
		for (int lineno = 1; lineno <= len; lineno++) {
			getline(sfile, line);
			activeKeys.push_back(stoi(line));
			getline(sfile, line);
			activeMods.push_back(stoi(line));
		}
		sfile.close();
	}
}

void CrystalClient::applyTheme(std::string const& name) {
    ImGuiStyle * style = &ImGui::GetStyle();
    ImVec4* colours = ImGui::GetStyle().Colors;

    if (sameAsAccent) {
        for (int a = 0; a < 3; a++) {
            BGColour[a] = LightColour[a];
        }
    }

    if (RGBAccent) {
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
    style->WindowRounding = rounded ? 12.f : 0.f;
    style->FrameRounding = 4.f;
    style->ScrollbarSize = 15.f;
    style->ScrollbarRounding = 12.f;
    style->PopupRounding = 4.f;
    style->WindowBorderSize = 1.5f;
    colours[ImGuiCol_TitleBg] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_TitleBgActive] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_WindowBg] = RGBAtoIV4(BGColour);
    colours[ImGuiCol_Border] = RGBAtoIV4(borders ? BGColour : LightColour);
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

void CrystalClient::drawPages() {
    ImGui::Begin("General");
    for (int i = 0; i < playerHacks.size(); i++) {
        CrystalClient::ImToggleable(playerHacks[i], &playerBools[i]);
        if (i == 14) ImGui::InputFloat("Wave Trail Size", &pulse, 0.01f, 10.00f, "%.2f");
        if (i == 40) {
            ImGui::SliderInt("Push Frames", &clickPush, 1, 20);
            ImGui::SliderInt("Release Frames", &clickRel, 1, 20);
        }
    }
    ImGui::End();
    ImGui::Begin("Display");
	/*
    if (ImGui::TreeNode("Order of Displays")) {
            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
            {
                const char* item = item_names[n];
                ImGui::Selectable(item);

                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
                {
                    int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
                    {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        ImGui::ResetMouseDragDelta();
                    }
                }
            }
        ImGui::TreePop();
    }
	*/
    for (int i = 0; i < guiHacks.size(); i++) {
        if (i != 9 && i != 2) CrystalClient::ImToggleable(guiHacks[i], &guiBools[i]);
        if (i == 0) ImGui::InputTextWithHint("Message", "Custom Message", message, IM_ARRAYSIZE(message));
        if (i == 2) {
			CrystalClient::ImExtendedToggleable(guiHacks[i], &guiBools[i]);
			if (ImGui::BeginPopupModal(guiHacks[i], NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				CrystalClient::ImToggleable("Reset clicks each attempt", &hasSetupFonts);
				if (ImGui::Button("Close")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
        }
        if (i == 9) {
			CrystalClient::ImExtendedToggleable(guiHacks[i], &guiBools[i]);
			if (ImGui::BeginPopupModal(guiHacks[i], NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				CrystalClient::ImToggleable("Increased Leniency", &lenient);
                ImGui::InputFloat("Kill at Accuracy", &killaccuracy, 0.00f, 99.99f, "%.2f");
                CrystalClient::ImToggleable("Reset at Accuracy", &resetaccuracy);
				if (ImGui::Button("Close")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
        }
    }
    ImGui::End();
    ImGui::Begin("Customization");
    ImGui::ColorEdit4("Accent Color", LightColour);
    ImGui::ColorEdit4("Base Color", BGColour);
    //CrystalClient::ImToggleable("Base Color Same As Accent Color", &sameAsAccent);
    CrystalClient::ImToggleable("RGB Accent Color", &RGBAccent);
    CrystalClient::ImToggleable("Borders", &borders);
    CrystalClient::ImToggleable("Rounded Windows", &rounded);
    ImGui::End();
    ImGui::Begin("Bypasses");
    //ImGui::InputFloat("Editor Grid Size", &gridSize, 0.001f, 1000.000f, "%.3f");
    for (int i = 0; i < bypassHacks.size(); i++) {
        CrystalClient::ImToggleable(bypassHacks[i], &bypassBools[i]);
    }
    ImGui::End();
    ImGui::Begin("Global");
	ImGui::PushItemWidth(100);
    ImGui::InputInt("##FPS Bypass", &bypass, 0, 1000);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("FPS Bypass", &hasSetupFonts);
	ImGui::PushItemWidth(100);
	ImGui::InputFloat("##TPS Bypass", &tps);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	CrystalClient::ImToggleable("TPS Bypass", &tpsBypass);
    ImGui::InputFloat("Speedhack", &speedhack, 0.001f, 10.000f, "%.3f");
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(speedhack);
    cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.0 / bypass);
    //ImGui::InputInt("Draw Divide", &DRAW_DIVIDE, 0, 10);
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]");
    CrystalClient::ImToggleable("Record", &record);
	ImGui::SameLine();
    CrystalClient::ImToggleable("Replay", &replay);
	CrystalClient::ImToggleable("ClickBot", &clickBot);
	ImGui::SameLine();
	CrystalClient::ImToggleable("Delta Lock", &deltaLock);
    ImGui::Combo("Macro Type", &currentMacroType, macroTypes, IM_ARRAYSIZE(macroTypes));
    ImGui::InputTextWithHint("Macro Name", "Macro Name", macroname, IM_ARRAYSIZE(macroname));
    if (ImGui::Button("Save Macro")) {
        std::string filename = (std::string)Mod::get()->getSaveDir() + (std::string)macroname + ".thyst";
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
		myfile << frameData.size();
        myfile << "\n";
		for (size_t i = 0; i < frameData.size(); i++)
        {
            myfile << std::setprecision(6) << std::fixed << frameData[i].xpos;
            myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << frameData[i].ypos;
            myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << frameData[i].accel;
            myfile << "\n";
        }
    }
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
        std::string line;
        std::string filename = (std::string)Mod::get()->getSaveDir() + (std::string)macroname + ".thyst";
        std::fstream file;
        file.open(filename, std::ios::in);
        if (file.is_open()) {
            getline(file, line);
            int len;
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                pushes.insert(pushes.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                releases.insert(releases.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
				Amethyst::AmethystFrame newPush;
                getline(file, line);
				newPush.xpos = stof(line);
				getline(file, line);
				newPush.ypos = stof(line);
				getline(file, line);
				newPush.accel = stod(line);
                pushData.insert(pushData.end(), newPush);
            }
			getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
				Amethyst::AmethystFrame newRel;
                getline(file, line);
				newRel.xpos = stof(line);
				getline(file, line);
				newRel.ypos = stof(line);
				getline(file, line);
				newRel.accel = stod(line);
                releaseData.insert(releaseData.end(), newRel);
            }
			getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
				Amethyst::AmethystFrame newFrameDat;
                getline(file, line);
				newFrameDat.xpos = stof(line);
				getline(file, line);
				newFrameDat.ypos = stof(line);
				getline(file, line);
				newFrameDat.accel = stod(line);
                frameData.insert(frameData.end(), newFrameDat);
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
		frameData.clear();
        CPoffset.clear();
        checkpointData.clear();
    }
    ImGui::End();
    ImGui::Begin("Keybinds");
    ImGui::Combo("Keybind", &currentKey, keybindings, IM_ARRAYSIZE(keybindings));
    ImGui::Combo("Mod to Switch", &currentMod, modbindings, IM_ARRAYSIZE(modbindings));
    if (ImGui::Button("Add Keybind")) {
        activeKeys.push_back(currentKey);
        activeMods.push_back(currentMod);
    }
	for (size_t i = 0; i < activeMods.size(); i++) {
		ImGui::AlignTextToFramePadding();
		ImGui::Text(modbindings[activeMods[i]]);
		ImGui::SameLine();
		ImGui::Text(keybindings[activeKeys[i]]);
		ImGui::SameLine();
		if (ImGui::Button(("x##" + std::to_string(i)).c_str())) {
			activeKeys.erase(activeKeys.begin() + i);
			activeMods.erase(activeMods.begin() + i);
		}
		ImGui::Separator();
	}
    ImGui::End();
    ImGui::Begin("Shortcuts");
    //CrystalClient::ImToggleable("Enable NONG Loader", &EnableNONGLoader);
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
    ImGui::End();
	//ImGui::Begin("Internal Renderer");
	//CrystalClient::ImToggleable("Render Recording", &rendering);
	//CrystalClient::ImToggleable("Include Sound", &withAudio);
	//ImGui::End();
}

void CrystalClient::saveMods() {
    std::ofstream clear(Mod::get()->getSaveDir() / "modconfig.cmp");
    clear << "";
    clear.close();
    std::fstream config(Mod::get()->getSaveDir() / "modconfig.cmp", std::ios::app);
    config << LightColour[0] << '\n';
    config << LightColour[1] << '\n';
    config << LightColour[2] << '\n';
    config << LightColour[3] << '\n';
	config << message << '\n';
    for (int s = 0; s < playerHacks.size(); s++) {
        config << playerBools[s] << '\n';
    }
    for (int s = 0; s < guiHacks.size(); s++) {
        config << guiBools[s] << '\n';
    }
    for (int s = 0; s < bypassHacks.size(); s++) {
        config << bypassBools[s] << '\n';
    }
    config.close();
}

void CrystalClient::loadMods() {
    std::fstream config(Mod::get()->getSaveDir() / "modconfig.cmp", std::ios::in);
    std::string color;
	if (config.is_open()) {
		    std::getline(config, color);
			LightColour[0] = std::stof(color);
			std::getline(config, color);
			LightColour[1] = std::stof(color);
			std::getline(config, color);
			LightColour[2] = std::stof(color);
			std::getline(config, color);
			LightColour[3] = std::stof(color);
			std::getline(config, color);
			strcpy(message, color.c_str());
			for (int s = 0; s < playerHacks.size(); s++) {
				std::string playerH;
				std::getline(config, playerH);
				if (playerH == "1") {
					playerBools[s] = true;
				} else {
					playerBools[s] = false;
				}
			}
			for (int s = 0; s < guiHacks.size(); s++) {
				std::string guiH;
				std::getline(config, guiH);
				if (guiH == "1") {
					guiBools[s] = true;
				} else {
					guiBools[s] = false;
				}
			}
			for (int s = 0; s < bypassHacks.size(); s++) {
				std::string bypassH;
				std::getline(config, bypassH);
				if (bypassH == "1") {
					bypassBools[s] = true;
				} else {
					bypassBools[s] = false;
				}
			}
	}
    config.close();
}

void CrystalClient::setAnchoredPosition(CCNode* label, int anchorPos) {
	auto corner = CCDirector::sharedDirector()->getScreenTop();
	int anchorY = ((anchorPos - 1) * 15) + 10;
	label->setPosition(5, corner - anchorY);
}

void CrystalClient::arrangeText(int arrayLength) {
	//std::distance(item_names, std::find(item_names, item_names + arrayLength, "Custom Message"))
	int anchor = 1;
	if (PlayLayer::get()->m_isTestMode) anchor = 2;
	if (guiBools[0]) {
		setAnchoredPosition(g_message, anchor);
		anchor++;
	} 
	if (guiBools[4]) {
		setAnchoredPosition(g_cheating, anchor);
		anchor++;
	}
	if (guiBools[8]) {
		setAnchoredPosition(g_run, anchor);
		anchor++;
	}
	if (guiBools[3]) {
		setAnchoredPosition(g_jumps, anchor);
		anchor++;
	}
	if (guiBools[11]) {
		setAnchoredPosition(g_tatts, anchor);
		anchor++;
	}
	if (guiBools[5]) {
		setAnchoredPosition(g_death, anchor);
		anchor++;
	}
	if (guiBools[10]) {
		setAnchoredPosition(font, anchor);
		anchor++;
	}
	if (guiBools[6]) {
		setAnchoredPosition(g_atts, anchor);
		anchor++;
	}
	if (guiBools[7]) {
		setAnchoredPosition(g_bestRun, anchor);
		anchor++;
	}
	if (guiBools[12]) {
		setAnchoredPosition(g_levelInfo, anchor);
		anchor++;
	}
	if (guiBools[2]) {
		setAnchoredPosition(g_clicks, anchor);
		anchor++;
	}
	if (guiBools[9]) {
		setAnchoredPosition(text, anchor);
		anchor++;
	}
	if (guiBools[15]) {
		setAnchoredPosition(g_macro, anchor);
		anchor++;
	}
}

void CrystalClient::HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float fC = fV * fS; // Chroma
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;
  
  if(0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if(1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if(2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if(3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if(4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if(5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }
  
  fR += fM;
  fG += fM;
  fB += fM;
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

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
		cocos2d::enumKeyCodes dispatchedkey = KEY_Tab;
		for (int m = 0; m < activeMods.size(); m++) {
			if (activeMods[m] == 12) {
				dispatchedkey = CrystalClient::shortcutKey(activeKeys[m]);
			}
		}
        if (down && key == dispatchedkey) {
            CrystalClient::get()->toggle();
            return true;
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};

class $modify(AchievementNotifier) {
    void willSwitchToScene(CCScene* scene) {
        AchievementNotifier::willSwitchToScene(scene);
        CrystalClient::get()->sceneChanged();
    }
};

class $modify(CCDirector) {
    void drawScene() {
        CrystalClient::get()->setup();

        static GLRenderCtx* gdTexture = nullptr;

        if (shouldUpdateGDRenderBuffer()) {
            if (gdTexture) {
                delete gdTexture;
                gdTexture = nullptr;
            }
            shouldUpdateGDRenderBuffer() = false;
        }
        CCDirector::drawScene();

        CrystalClient::get()->render(gdTexture);
    }
};


CCNode* getChildByFnRecursive(CCNode* node, std::function<bool(CCNode*)> fn) {
    if (fn(node)) return node;

    auto children = node->getChildren();
    if (!children) return nullptr;

    for (int i = 0; i < children->count(); ++i) {
        auto child = getChildByFnRecursive((cocos2d::CCNode*)children->objectAtIndex(i), fn);
        if(child)
            return child;
    }

    return nullptr;
}
/*
class Patch2 : public Patch {
 public:
 	Patch2(byte_array patch, byte_array original, uintptr_t address) : Patch() {
 		m_patch = patch;
 		m_original = original;
 		m_address = (void*)address;
 		m_owner = Mod::get();
 	}
};

class Patch3 : public Patch {
 public:
 	Patch3(char patch, char original, uintptr_t address) : Patch() {
 		m_patch = {patch};
 		m_original = {original};
 		m_address = (void*)(base::get() + address);
 		m_owner = Mod::get();
 	}
};
*/
GEODE_API void GEODE_DLL geode_load(Mod* m) {
	//fps_shower_init();
    /*
		Patch2* lol = new Patch2({'\xeb'}, {'\x76'}, base::get() + 0x18D811);
		lol->apply();
		Patch2* lol2 = new Patch2({'\xeb'}, {'\x76'}, base::get() + 0x18D7D9);
		lol2->apply();


		Patch2* lol3 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x25332);
		lol3->apply();
		Patch2* lol4 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x2533f);
		lol4->apply();

		(new Patch2({'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, 0x1d72d))->apply();

		(new Patch3('\xeb', '\x7c', 0x18bfa))->apply();
		(new Patch3('\xeb', '\x7c', 0x18f25))->apply();
		(new Patch3('\xeb', '\x7c', 0x1b991))->apply();

		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x949cd))->apply();
		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x94b1d))->apply();

		// custom object 
		(new Patch2({'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, 0x1d67c))->apply();
		(new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, 0x1d869))->apply();
		// custom objects
		(new Patch2({'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, 0x1d72d))->apply();
        */
}

class FPSOverlay : public cocos2d::CCNode {
 protected:
    static inline FPSOverlay* s_sharedState = 0;

    cocos2d::CCLabelBMFont* m_label;
    cocos2d::extension::CCScale9Sprite* m_backdrop;
    int m_frames;
    double m_accumulate;
    double m_resetInterval;
	std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
    float frame_time_sum = 0.f;
    int frame_count = 0;

 public:
    static FPSOverlay* sharedState() {
        if (!FPSOverlay::s_sharedState) {
            auto ret = FPSOverlay::s_sharedState = new FPSOverlay();
            ret->init();
        }
        return FPSOverlay::s_sharedState;
    }

 private:
    cocos2d::CCSize getBackdropSize() {
        auto textSize = m_label->getContentSize();
        return cocos2d::CCSizeMake(2 * 6 + textSize.width * 2, 2 * 6 + textSize.height * 2);
    }

 public:
    bool init() {
        m_frames = 0;
        m_resetInterval = 1.0;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
		auto corner = CCDirector::sharedDirector()->getScreenTop();
        
        m_label = cocos2d::CCLabelBMFont::create("No FPS", "bigFont.fnt");
        m_label->setPosition(5 , corner - 305);
		m_label->setScale(0.4);
		m_label->setAnchorPoint({0, 0.5});
		m_label->setOpacity(100);
        addChild(m_label, 2);        

        m_backdrop = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
        m_backdrop->setContentSize(getBackdropSize());
        m_backdrop->setPosition({2, winSize.height - 2});
        m_backdrop->setAnchorPoint(cocos2d::CCPoint(0, 1));
        m_backdrop->setOpacity(0);
        m_backdrop->setScale(0.166666);
        addChild(m_backdrop, 1);

		this->schedule(schedule_selector(FPSOverlay::updateLabel));

        return true;
    }

    void update(float dt) {
    	updateLabel(dt);
    }

    void updateLabel(float dt) {
		const auto now = std::chrono::high_resolution_clock::now();

		const std::chrono::duration<float> diff = now - previous_frame;
		frame_time_sum += diff.count();
		frame_count++;

		if (std::chrono::duration<float>(now - last_update).count() > 1.0f) {
			last_update = now;
			const auto fps = static_cast<int>(std::roundf(static_cast<float>(frame_count) / frame_time_sum));
			frame_time_sum = 0.f;
			frame_count = 0;
			m_label->setString((std::to_string(fps) + " FPS").c_str());
            m_backdrop->setContentSize(getBackdropSize());
		}

		previous_frame = now;
    }
};

class $modify(MenuLayer) {
	bool init() {
		MenuLayer::init();
		CrystalClient::get()->loadMods();
		CrystalClient::get()->loadShortcuts();
		if (bypassBools[10]) cl = 0;
		return true;
	}
};

void fps_shower_init() {
	geode::Loader::get()->queueInGDThread([](){
		cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(FPSOverlay::sharedState(), 0, true);
		auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
		if (scene) {
			auto layer = reinterpret_cast<cocos2d::CCNode*>(scene->getChildren()->objectAtIndex(0));
			if (layer) layer->addChild(FPSOverlay::sharedState(), 100001);
			FPSOverlay::sharedState()->setVisible(false);
		}
	});
}
/*
class $modify(CCLayerColor) {
	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::create(yk);
		}
	}

	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0), f1, f2);
		} else {
			return CCLayerColor::create(yk, f1, f2);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::initWithColor(yk);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0), 0, 0);
		} else {
			return CCLayerColor::initWithColor(yk, f1, f2);
		}
	}
};
*/

static inline tulip::HitboxNode* drawer;

class $modify(HitboxLevelEditorLayer, LevelEditorLayer) {
	static inline bool paused = false;

	bool init(GJGameLevel* lvl) {
		drawer = tulip::HitboxNode::create();
		auto ret = LevelEditorLayer::init(lvl);
		drawer->setVisible(false);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		// i hate bad practices
		drawer->m_drawTrail = playerBools[8];
		s_noLimitTrail = false;
/*
		for (int q = 0; q < newQueue.size(); q++) {
			drawer->addToPlayer1Queue(newQueue[q]);
		}*/
		drawer->drawForPlayer1(m_player1);
		drawer->setVisible(true);
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
		if (playerBools[9]) {
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
        if (playerBools[9]) {
			drawer->setVisible(true);
		}
        LevelEditorLayer::onStopPlaytest();
    }

	void update(float dt) {
		drawer->clear();
		LevelEditorLayer::update(dt);

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
};

class $modify(EditorUI) {
	void keyDown(enumKeyCodes code) {
		EditorUI::keyDown(code);
		if (s_drawer) {
			//s_drawer->clear();
			static_cast<HitboxLevelEditorLayer*>(LevelEditorLayer::get())->updateHitboxEditor();
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

	void zoomIn(cocos2d::CCObject* sender) {
		if (bypassBools[8]) {
			zoom = zoom + 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomIn(sender);
		}
	}

	void zoomOut(cocos2d::CCObject* sender) {
		if (bypassBools[8]) {
			zoom = zoom - 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomOut(sender);
		}
	}
};

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (bypassBools[5]) {
			ok->m_isVerified = true;
		}	
		if (playerBools[20]) {
			ok->m_lowDetailModeToggled = true;
		} 
		if (bypassBools[10]) cl = 1;
		return EditLevelLayer::create(ok);
	}
};

class $modify(GameManager) {
		bool isIconUnlocked(int a, IconType b) {
			auto icon = GameManager::isIconUnlocked(a,b);
			if (!bypassBools[1]) {
				return true;
			} else {
				return icon;
			}
		} 
		bool isColorUnlocked(int a, bool b) {
			auto color = GameManager::isColorUnlocked(a,b);
			if (!bypassBools[1]) {
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
		if (playerBools[39]) {
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

		if (playerBools[39] && m_objectType != GameObjectType::Decoration) {
			CCSpritePlus::setOpacity(255);
			if (m_glowSprite)
				m_glowSprite->setOpacity(255);
		}
	}

	void setGlowColor(cocos2d::_ccColor3B const& col) {
		if (playerBools[39]) {
			GameObject::setGlowColor(ccc3(255, 255, 255));
		} else {
			GameObject::setGlowColor(col);
		}
	}

	void setObjectColor(const cocos2d::ccColor3B& cor) {
		if (playerBools[39] && m_objectType != GameObjectType::Decoration) {
			GameObject::setObjectColor(ccc3(255, 255, 255));
		} else {
			GameObject::setObjectColor(cor);
		}
	}

    virtual void update(float time2) {
		if (playerBools[34]) {
			bool m_isGlowDisabled = true;
		}
		if (playerBools[11]) {
			bool m_particleAdded = true;
   			bool m_hasParticles = false;
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
		if (bypassBools[10]) return true;
		return LevelTools::verifyLevelIntegrity(mg, de);
	}
};


class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		pushing = true;
		//if (b) mouse1Down = true;
	    //if (!b) mouse2Down = true;
		if (record) {
			pushData.push_back(Amethyst::create());
			pushes.insert(pushes.end(), frame);
		}
		if (playerBools[22]) {
			if (!b) GJBaseGameLayer::pushButton(i,true);
			if (b) GJBaseGameLayer::pushButton(i,false);
		} else if (playerBools[23]) {
			GJBaseGameLayer::pushButton(i,true);
			GJBaseGameLayer::pushButton(i,false);
		} else {
			GJBaseGameLayer::pushButton(i,b);
		}
		clickscount++;
	}

	void releaseButton(int i, bool b) {
		pushing = false;
		//if (b) mouse1Down = false;
	    //if (!b) mouse2Down = false;
		if (record) {
			releaseData.push_back(Amethyst::create());
			releases.insert(releases.end(), frame);
		}
        if (playerBools[22]) {
			if (!b) GJBaseGameLayer::releaseButton(i,true);
			if (b) GJBaseGameLayer::releaseButton(i,false);
		} else if (playerBools[23]) {
			GJBaseGameLayer::releaseButton(i,true);
			GJBaseGameLayer::releaseButton(i,false);
		} else {
			GJBaseGameLayer::releaseButton(i,b);
		}
		releasecount++;
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
		if (playerBools[14]) m_pulseSize = pulse;
		if (playerBools[28]) m_isSolid = true;
		//if (playerBools[4] && PlayLayer::get()) this->setColor(col);
		if (playerBools[28]) this->setBlendFunc(getBlendFunc());
		HardStreak::updateStroke(f);
	}
};

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		auto layer = LevelInfoLayer::create(g);
		if (bypassBools[6]) {
			g->m_password = 1;
		}

		if (playerBools[20]) {
			g->m_lowDetailModeToggled = true;
		}
		
		//getNONGs();
		//findsong = std::to_string(level->m_songID);

		if (bypassBools[10]) cl = 0;

		return layer;
	}
};

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (playerBools[41]) pause->setVisible(false);
		PauseLayer* fcuk;
		if (cl != 1 && bypassBools[10]) {
			auto editorSprite = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
			auto menu = CCMenu::create();
			auto editorClick = CCMenuItemSpriteExtra::create(editorSprite, fcuk, menu_selector(PauseLayer::goEdit));
				menu->addChild(editorClick);
				menu->setPosition({22.750f, 92.5f});
				menu->setScale(0.768f);
				menu->setAnchorPoint({0.5f, 0.5f});
			pause->addChild(menu, 0);
		}
		return pause;
	}

	void keyDown(cocos2d::enumKeyCodes key) {
		if (key == KEY_Escape) {
			if (!playerBools[18]) {
				PauseLayer::keyDown(key);
			}
		} else {
			PauseLayer::keyDown(key);
		}
	}
};


class $modify(PlayerObject) {
	void playDeathEffect() {
		if (!playerBools[10]) {
			PlayerObject::playDeathEffect();
		}
		if (playerBools[21]) {
			PlayLayer::get()->resetLevel();
		}
		if (playerBools[17]) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
		}
	}
	void addAllParticles() {
		if (!playerBools[11]) {
			PlayerObject::addAllParticles();
		}
	}
	void update(float spe) {		
		if (m_waveTrail && playerBools[28]) {
			m_waveTrail->setBlendFunc(getBlendFunc()); // removes the blending of it
		}
		if (playerBools[32]) {
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
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && playerBools[26]) {
        	if (ring->m_hasBeenActivated && !a) g_activated_objects.push_back(ring);
        	if (ring->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(ring);
    	}
	}
	void saveToCheckpoint(PlayerCheckpoint* g) {
		PlayerObject::saveToCheckpoint(g);
		if (playerBools[27]) {
			g->retain();
		//g_startPoses.push_back({reinterpret_cast<CheckpointObject*>(g), g->getPosition()});
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
	}
	virtual void setRotation(float love) {
		return PlayerObject::setRotation(love);
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
		if (tpsBypass && PlayLayer::get() && !PlayLayer::get()->m_isPaused) {
			const auto fps = tps;

			auto speedhack = CCDirector::sharedDirector()->getScheduler()->getTimeScale();

			const float target_dt = 1.f / fps / speedhack;

			//cocos2d::CCApplication::sharedApplication()->setAnimationInterval(target_dt);

			//return CCScheduler::update(target_dt);

			// todo: find ways to disable more render stuff
			g_disable_render = false;

			unsigned times = static_cast<int>((f3 + g_left_over) / target_dt);
			if (f3 == 0.f)
				return CCScheduler::update(target_dt);
			auto start = std::chrono::high_resolution_clock::now();
			for (unsigned i = 0; i < times; ++i)
			{
				//if (i == times - 1)
				//    g_disable_render = false;
				CCScheduler::update(target_dt);
				using namespace std::literals;
				if (std::chrono::high_resolution_clock::now() - start > 33.333ms)
				{
					times = i + 1;
					break;
				}
			}
			g_left_over += f3 - target_dt * times;
		} else {
			CCScheduler::update(f3);
		}
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
		}
		if (DrawGridLayer::get() && specialAccess) {
			DrawGridLayer::get()->m_activeGridNodeSize = gridSize;
			DrawGridLayer::get()->m_gridSize = gridSize;
		}
		if (RGBAccent) {
			if (CrystalClient::get()->g >= 360)
				CrystalClient::get()->g = 0;
			else
				CrystalClient::get()->g += rainbowspeed;
		}
		//CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);

    	//CGEventRef evt = CGEventCreateKeyboardEvent(src, (CGKeyCode) 7, true);

    	//CGEventPost (kCGHIDEventTap, evt);
    	//CFRelease (evt); CFRelease (src);
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
			g_startPosText->runAction(CCSequence::create(colorPulseBegin, colorPulseEnd, nullptr));
			g_startPosText->runAction(CCSequence::create(opacityPulseBegin, opacityPulseEnd, nullptr));
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
			load = true;
		}
		if (m_isTestMode) g_startPosText->setOpacity(50);
		if (m_isPaused)
			GameSoundManager::sharedManager()->stopBackgroundMusic();
	}

	void addObject(GameObject* g) {
		if (playerBools[34]) g->m_isGlowDisabled = true;
		if (playerBools[37]) g->m_isDontFade = true;
		if (playerBools[38]) g->m_isDontEnter = true;
		PlayLayer::addObject(g);
		SPs.push_back(reinterpret_cast<StartPosObject*>(g));
		if (playerBools[24]) {
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
		auto gj = reinterpret_cast<PlayerObject*>(PlayLayer::get());
		if (playerBools[27] && m_isPracticeMode) load = true;
		if (guiBools[10]) {
			noclip_deaths = deathwait = 0;
		}
		if (playerBools[25]) {
			if (m_isTestMode || m_isPracticeMode) {
				smoothOut = 2;
			}
		}
		if (guiBools[7]) {
			bestEnd2 = (m_player1->getPositionX() / m_levelLength) * 100;
		}
        if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();
		PlayLayer::resetLevel();
		if (m_isPracticeMode && record) {
			checkpointData.back().apply(GJBaseGameLayer::get()->m_player1);

			if (CPoffset.size() == 0) CPoffset.push_back(0);
			offset = CPoffset.back();

			frame = (int)(m_time * 240) + offset;

			while (frameData.back().xpos >= m_player1->getPositionX() && frameData.size() != 0) {
				frameData.pop_back();
			}

			while (pushes.back() >= frame && pushes.size() != 0) {
				pushData.pop_back();
				pushes.pop_back();
			}

			while (releases.back() >= frame && releases.size() != 0) {
				releaseData.pop_back();
				releases.pop_back();
			}

			if (pushing) {
				pushData.push_back(Amethyst::create());
				pushes.insert(pushes.end(), frame);
			}

		} else {
			frame = lastFrame = newFrame = 0;
			offset = 0;
			pushIt = releaseIt = posIt = 0;
			clickscount = releasecount = 0;
			//GJBaseGameLayer::get()->releaseButton(1, true);
		}
		if (m_checkpoints->count() == 0) {
        	g_activated_objects.clear();
        	g_activated_objects_p2.clear();
        	g_orbCheckpoints.clear();
    	} else {
			if (playerBools[26] && m_isPracticeMode) {
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
		if (guiBools[4]) {
			bad = "Not Cheating";
			g_cheating->setColor(ccc3(0,255,0));
		}
		//if (clickreset) clickscount = 0;
		finished = false;
		if (guiBools[8]) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from %.0lf%%", start);
			g_run->setString(str);
		}
		if (guiBools[7]) {
			bestStart2 = (m_player1->getPositionX() / m_levelLength) * 100;
			if ((bestEnd2 - bestStart2) > (bestEnd - bestStart)) {
				bestStart = bestStart2;
				bestEnd = bestEnd2;
			}
			display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);
			g_bestRun->setString(display.c_str());
		}
		if (guiBools[9]) {
			frames = noclipped_frames = 0;
		}
	}

	void destroyPlayer(PlayerObject* p, GameObject* g) {
		if (g == m_antiCheatObject) {
			return PlayLayer::destroyPlayer(p,g);
		}
		would_die = true;
		if (guiBools[9]) {
			auto accu = (float)(frames-noclipped_frames) / (float)frames;
			if (accu * 100 <= killaccuracy) {
				if (!resetaccuracy) {
					PlayLayer::destroyPlayer(p, g);
				} else {
					resetLevel();
				}
				char str[20];
				sprintf(str, "%.2f%%", killaccuracy);
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(str);
			}
		}
		if (guiBools[10]) {
			deathwait++;
			if (deathwait >= 25) {
				noclip_deaths++;
				deathwait = 0;
			} 
		}
		if (bypassBools[0]) {
			bool m_antiCheatPassed = true;
			bool m_shouldTryToKick = false;
			bool m_hasCheated = false;
		}
		if (playerBools[35]) {
			if (g->m_objectID != 8 || g->m_objectID != 39 || g->m_objectID != 103) {
				PlayLayer::destroyPlayer(p,g);
			}
		}
		if (playerBools[0] && !playerBools[1]) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (playerBools[1] && !playerBools[0]) {
			if (p == m_player1) PlayLayer::destroyPlayer(p,g);
		} 
		if (!playerBools[0] && !playerBools[1]) {
			PlayLayer::destroyPlayer(p,g);
		}
	}

	void fullReset() {
		if (playerBools[30] && m_isPracticeMode) {
			loadLastCheckpoint();
			resetLevel();
		} else {
			PlayLayer::fullReset();
		}
	}

	void checkCollisions(PlayerObject* p, float g) {

		if (bypassBools[0]) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
		}

		if (bypassBools[9]) GJBaseGameLayer::get()->m_player1->setPositionY(1050);
		if (bypassBools[9]) GJBaseGameLayer::get()->m_player1->setPositionX(m_levelLength - 200);

			if (playerBools[40]) {
				clickframe++;
				if (clickframe == clickPush) {
					GJBaseGameLayer::get()->pushButton(1, true);
				}
				if (clickframe >= (clickPush + clickRel)) {
					GJBaseGameLayer::get()->releaseButton(1, true);
					clickframe = 0;
				}
			}

			if (guiBools[15]) {
				if (replay && !rendering) {
					std::string status = "Playing: " + std::to_string(pushIt) + "/" + std::to_string(pushes.size());
					g_macro->setString(status.c_str());
				} else if (record) {
					std::string status = "Recording: Macro Frame " + std::to_string((int)(m_time * 240 + offset));
					g_macro->setString(status.c_str());
				} else if (replay && rendering) {
					std::string status = "Rendering: Video Frame " + std::to_string(m_time * 60);
					g_macro->setString(status.c_str());
				}
			}

			PlayLayer::checkCollisions(p, g);

			auto p1 = GJBaseGameLayer::get()->m_player1;
			auto p2 = GJBaseGameLayer::get()->m_player2;

			frame = (int)(m_time * 240) + offset;

			yAccel = (*reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(GJBaseGameLayer::get()->m_player1) + 0x760));

			if (replay && pushes.size() > 0) {
				if (pushes[pushIt] <= frame) {
					if (currentMacroType == 1) {
						Amethyst::apply(pushData[pushIt], false);
					}
					GJBaseGameLayer::get()->pushButton(1, true);
					pushIt++;
				}

				if (releases[releaseIt] <= frame) {
					if (currentMacroType == 1) {
						Amethyst::apply(releaseData[releaseIt], false);
					}
					GJBaseGameLayer::get()->releaseButton(1, true);
					releaseIt++;
				}
			}

            if (p == m_player1) {
			    drawer->addToPlayer1Queue(m_player1->getObjectRect());
				//newQueue.push_back(m_player1->getObjectRect());
		    }
		    if (p == m_player2) {
			    drawer->addToPlayer2Queue(m_player2->getObjectRect());
		    }

			if (guiBools[9] && !finished) {
				char ok[20];
				auto accu = (float)(frames - noclipped_frames) / (float)frames;
				sprintf(ok, "%.2f%%", accu * 100);
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
			}


	}

	void levelComplete() {
		finished = true;
		PlayLayer::levelComplete();
	}

	void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		int resetPercentage = (m_player1->getPositionX() / m_levelLength) * 100;
		if ((resetPercentage == autoresetnum) && playerBools[31]) {
			resetLevel();
		}
		if (playerBools[13]) {
			double percent = (m_player1->getPositionX() / m_levelLength) * 100;
			if (percent > 100.00) {
				percent = 100.00;
			}
			char str[64];
			sprintf(str, "%.2lf%%", percent);
			this->m_percentLabel->setString(str);
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
			kCGImageAlphaLast, 
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
		CCDirector::sharedDirector()->getRunningScene()->visit();
		renderer->end();

		auto img = renderer->newCCImage(true);
		CGImageWriteToFile(CGImageFromCCImage(img));    
	}

	void update(float f4) {
		if (CrystalClient::get()->g >= 360)
			CrystalClient::get()->g = 0;
		else
			CrystalClient::get()->g += rainbowspeed;
		col = CrystalClient::get()->getRainbow(0);
		colInverse = CrystalClient::get()->getRainbow(180);

		frames += f4;

		if (would_die) {
			noclipped_frames += f4;
			would_die = false;
			//noclipRed->setOpacity(50);
		} else {
			noclipRed->setOpacity(0);
		}

		if (m_player1) {
			if (playerBools[2]) m_player1->setColor(col);
			if (playerBools[3]) m_player1->setSecondColor(colInverse);
			if (playerBools[33]) m_player1->m_waveTrail->setVisible(false);
			if (m_player1->m_waveTrail)
				if (playerBools[4]) m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			if (playerBools[3]) m_player2->setColor(colInverse);
			if (playerBools[2]) m_player2->setSecondColor(col);
			if (m_player2->m_waveTrail)
				if (playerBools[4]) m_player2->m_waveTrail->setColor(colInverse);
		}

		if (guiBools[9]) {
			percent = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		if (guiBools[0]) {
			g_message->setString(message);
		}
		if (guiBools[4]) {
			if (playerBools[0] || speedhack < 1 || playerBools[36] || playerBools[29] || playerBools[40] || playerBools[39] || bypassBools[9]) {
				bad = "Cheating";
				g_cheating->setColor(ccc3(155,0,0));
			}

			g_cheating->setString(bad.c_str());

		}
		if (pausecountdown) {
			if (freezeCount) {
				GameSoundManager::sharedManager()->stopBackgroundMusic();
				countdown++;
				if (countdown <= 60) {
					g_pauseCount->setString("3");
				} else if (countdown <= 120 && countdown > 60) {
					g_pauseCount->setString("2");
				} else if (countdown <= 180 && countdown > 120) {
					g_pauseCount->setString("1");
				} else if (countdown <= 240 && countdown > 180) {
					freezeCount = false;
					startMusic();
					g_pauseCount->setOpacity(0);
					countdown = 0;
				}
			}
		}
		if (guiBools[10]) {
			std::string nd = "Noclip Deaths: " + std::to_string(noclip_deaths);
			font->setString(nd.c_str());
		}
		if (guiBools[3]) {
			std::string nd = "Total Jumps: " + std::to_string(m_level->m_jumps);
			g_jumps->setString(nd.c_str());
		}
		if (playerBools[5]) {
			//m_player2->setSecondColor(secondary);
			//m_player2->setColor(primary);
			//m_player2->m_waveTrail->setColor(primary);
		}
		if (guiBools[2]) {
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
		}
		if (playerBools[12]) {
			m_sliderGrooveSprite->setVisible(false);
		} else {
			m_sliderGrooveSprite->setVisible(true);
			m_percentLabel->setPositionX(m_percentLabel->getPositionX());
		}
		if (playerBools[15]) {
			m_attemptLabel->setVisible(false);
		}
		if (playerBools[16]) {
			if (m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
		if (guiBools[6]) {
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);
		}
		if (guiBools[11]) {
			std::string at = "Global Atts: " + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
		}
		if (guiBools[5]) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death: %.0lf%%", start);
			g_death->setString(str);
		}
        drawer->clear();

		/*
		CGImageRef screenShot = CGWindowListCreateImage( CGRectInfinite, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);

		std::stringstream newthing;
  		newthing << "/Users/trooper/Downloads/InternalRender/frame_";
		newthing << std::setw(3) << std::setfill('0') << std::to_string(ss);
		newthing << "_delay-0.07s.jpg";
		std::string name = newthing.str();

		CFStringRef file = CFStringCreateWithCString(kCFAllocatorDefault,
		name.c_str(),
		kCFStringEncodingMacRoman);
		CFStringRef type = CFSTR("public.jpeg");
		CFURLRef urlRef = CFURLCreateWithFileSystemPath( kCFAllocatorDefault, file, kCFURLPOSIXPathStyle, false );
		CGImageDestinationRef image_destination = CGImageDestinationCreateWithURL( urlRef, type, 1, NULL );
		CGImageDestinationAddImage( image_destination, screenShot, NULL );
		CGImageDestinationFinalize( image_destination );
		ss++;
		std::fstream check;
		check.open(name.c_str());
		*/
		if (deltaLock) {
			auto dir = CCDirector::sharedDirector();

			float spf = (float)dir->getAnimationInterval() * (60 / tps);
			float tScale = dir->getScheduler()->getTimeScale();

			f4 = spf * tScale;
		}
		if (playerBools[25]) {
			if (!smoothOut) {
				return update(f4);
			}

			float time = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();
			if (smoothOut != 0 && f4 - time < 1) {
				smoothOut --;
			}

			PlayLayer::update(time);
		} else {
			if (!playerBools[29] || (playerBools[29] && shouldUpdate)) {
				if (classicspeed) {
					PlayLayer::update(f4 * speedhack);
				} else {
					PlayLayer::update(f4);
					if (rendering && replay && m_time > 0) captureScreen();
				}
			}
		}
		
		if (record) {
			frameData.push_back(Amethyst::create());
		}

		if (replay && frameData.size() > 0 && frame > releases.back()) {
			if (currentMacroType == 2) {
				if (newFrame == 0) newFrame++;
				if (frameData[newFrame].xpos < m_player1->getPositionX()) {
					while (frameData[newFrame].xpos < m_player1->getPositionX()) {
						Amethyst::apply(frameData[newFrame], false);
						newFrame++;
						if (pushes[pushIt] <= frame) {
							GJBaseGameLayer::get()->pushButton(1, true);
							pushIt++;
						}
						if (releases[releaseIt] <= frame) {
							GJBaseGameLayer::get()->releaseButton(1, true);
							releaseIt++;
						}
					}
				}
			}
		}

		//musicOffset = PlayLayer::get()->m_level->m_levelSettings->m_songOffset;
        //if (autoKill) {
			//m_isDead = true;
			//PlayLayer::resetLevel();
			//autoKill = false; // so it doesnt loop
		//}
		if (s_showOnDeath) {
			if (!s_drawOnDeath || !playerBools[7]) return;
			drawer->setVisible(true);
		}		

		if (m_player1 && playerBools[7]) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2 && playerBools[7]) {
			drawer->drawForPlayer2(m_player2);
		}

		s_showOnDeath = playerBools[6];

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

				if (playerBools[7]) drawer->drawForObject(obj);
			}
		}
	}

	void markCheckpoint() {
		if (playerBools[26]) g_orbCheckpoints.push_back({g_activated_objects.size(), g_activated_objects_p2.size()});
		PlayLayer::markCheckpoint();
		if (!m_isDead) {
			checkpointData.push_back(Amethyst::store());
			CPoffset.push_back(frame);
		}
		//std::get<std::deque<int>>(Player1Data["Checkpoints"]).insert(std::get<std::deque<int>>(Player1Data["Checkpoints"]).end(), frame);
	}

	void removeLastCheckpoint() {
		if (playerBools[26]) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		checkpointData.pop_back();
		CPoffset.pop_back();
		//if (std::get<std::deque<int>>(Player1Data["Checkpoints"]).size() > 0) std::get<std::deque<int>>(Player1Data["Checkpoints"]).pop_back();
	}

	void startMusic() {
		if (playerBools[17]) {
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

	void onQuit() {
		FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (!shouldQuit && playerBools[19] && !m_hasLevelCompleteMenu) {
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
			if (withAudio) {
				std::string rendercmd = "ffmpeg -framerate 60 -pattern_type glob -i '" + CrystalClient::getRenderPath(true) + "*.png' \
			-c:v libx264 -pix_fmt yuv420p " + CrystalClient::getRenderPath(true) + "newrender.mp4";
				auto renderprocess = system(rendercmd.c_str());
				//auto songprocess = system(CrystalClient::getSongCmdStr(getOffsetTime(LevelSettingsObject::get()->m_songOffset).c_str(), (std::string)PlayLayer::get()->m_level->getAudioFileName().c_str(), CrystalClient::getRenderPath(true).c_str() + "newrender.mp4", std::to_string(renderTime).c_str(), CrystalClient::getRenderPath(true) + "new.mp4".c_str()).c_str());
				//(std::string)m_level->getAudioFileName()
				std::fstream idklmao;
				idklmao.open("geode/mods/log.txt", std::ios::app);
				//idklmao << CrystalClient::renderVideo();
				//geode::dirs::getTempDir()
				std::string songname;
			}
			PlayLayer::onQuit();
		}
	}

	void togglePracticeMode(bool p) {
		if (playerBools[17]) {
			if (!m_isPracticeMode && p) {
				// receate function without the music restart
				m_isPracticeMode = p;
				m_UILayer->toggleCheckpointsMenu(p);
				PlayLayer::startMusic();
				this->stopActionByTag(18);
				//if (p) stopActionByTag(0x12);
			} else {
				PlayLayer::togglePracticeMode(p);
			}
		}
		else {
			PlayLayer::togglePracticeMode(p);
		}
	}

	void resume() {
		PlayLayer::resume();
		if (pausecountdown) freezeCount = true;
		if (pausecountdown) g_pauseCount->setOpacity(255);
	}

	void toggleFlipped(bool one, bool two) {
		if (!playerBools[36]) {
			PlayLayer::toggleFlipped(one, two);
		}
	}

	void startGame() {
		PlayLayer::startGame();
		//CrystalClient::get()->arrangeText(13);
		if (guiBools[1]) {
			FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
		}
	}

	void setupSmartSP() {
		
	}

    static inline tulip::HitboxNode* drawer;

	bool init(GJGameLevel* gl) {
		//leftDisplay = 0;
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (playerBools[24]) {
			rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_startPosIndex = -1;
			g_startPoses = {};
			
		}
		if (playerBools[27]) {
			CPrightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			CPleftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_checkpointText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_checkpointIndex = -1;
			g_checkpointsIG = {};
			
		}
		if (guiBools[0]) {
			g_message = CCLabelBMFont::create(message, "bigFont.fnt");
		}
		if (guiBools[3]) {
			g_jumps = CCLabelBMFont::create("Total Jumps: 0", "bigFont.fnt");
		}
		if (guiBools[6]) {
			g_atts = CCLabelBMFont::create("Attempts: 0", "bigFont.fnt");
		}
		if (guiBools[8]) {
			g_run = CCLabelBMFont::create("Run from ???", "bigFont.fnt");
		}
		if (guiBools[7]) {
			g_bestRun = CCLabelBMFont::create("Best Run: 0 to 0", "bigFont.fnt");
		}
		if (guiBools[12]) {
			g_levelInfo = CCLabelBMFont::create("Unnamed (No ID)", "bigFont.fnt");
		}
		if (guiBools[2]) {
			g_clicks = CCLabelBMFont::create("?? Clicks", "bigFont.fnt");
			clickscount = 0;
		}
		if (guiBools[4]) {
			g_cheating = CCLabelBMFont::create("Not Cheating", "bigFont.fnt");
		}
		if (guiBools[11]) {
			g_tatts = CCLabelBMFont::create("Global Atts: ??", "bigFont.fnt");
		}
		if (guiBools[5]) {
			g_death = CCLabelBMFont::create("Last Death: ???", "bigFont.fnt");
		}
		if (guiBools[10]) {
			font = CCLabelBMFont::create("Noclip Deaths: ???", "bigFont.fnt");
		}
		if (guiBools[9]) {
			text = CCLabelBMFont::create("100%", "bigFont.fnt");
		}
		if (guiBools[15]) {
			g_macro = CCLabelBMFont::create("Playing: 0/0", "bigFont.fnt");
		}
		if (pausecountdown) {
			g_pauseCount = CCLabelBMFont::create("Not Paused", "goldFont.fnt");
		}
        drawer = tulip::HitboxNode::create();

		ss = 0;
		PlayLayer::init(gl);

		noclipRed = CCSprite::createWithSpriteFrameName("block005b_05_001.png");
		noclipRed->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2});
		noclipRed->setScale(1000.0f);
		noclipRed->setColor(ccc3(255,0,0));
		noclipRed->setOpacity(0);
		noclipRed->setZOrder(1000);
		m_UILayer->addChild(noclipRed);

        m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = playerBools[6];
		drawer->m_drawTrail = playerBools[8];
		s_onlyHitboxes = false;
		if (s_showOnDeath) s_drawOnDeath = false;

		frame = 0;

		if (bypassBools[9]) {
			//gl->savePercentage(100, false, 100, 100, true);
		}
		
		if (playerBools[24]) {
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
			g_startPosText->setScale(0.5);
			g_startPosText->setAnchorPoint({0, 0.5});
			g_startPosText->setOpacity(50);
			rightButton->::Main::setPosition(220 , corner - 275);
			rightButton->setScale(0.5);
			rightButton->setAnchorPoint({0, 0.5});
			rightButton->setOpacity(50);
			leftButton->::Main::setPosition(310 , corner - 275);
			leftButton->setRotation(180);
			leftButton->setScale(0.5);
			leftButton->setAnchorPoint({0, 0.5});
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
		if (playerBools[27]) {
			g_checkpointText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				//g_checkpointText->setPosition(245 , corner - 275);
			}
			g_checkpointText->setScale(0.5);
			g_checkpointText->setAnchorPoint({0, 0.5});
			g_checkpointText->setOpacity(50);
			CPrightButton->::Main::setPosition(220 , corner - 275);
			CPrightButton->setScale(0.5);
			CPrightButton->setAnchorPoint({0, 0.5});
			CPrightButton->setOpacity(50);
			CPleftButton->::Main::setPosition(310 , corner - 275);
			CPleftButton->setRotation(180);
			CPleftButton->setScale(0.5);
			CPleftButton->setAnchorPoint({0, 0.5});
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
		if (playerBools[12]) {
			m_percentLabel->setPositionX(259.638);
		}
		if (guiBools[0]) {
			//setAnchoredPosition(g_message, std::distance(item_names, std::find(item_names, item_names + 13, "Custom Message")));
			//g_tatts->setPosition(5 , corner - 55);
			g_message->setScale(0.4);
			g_message->setAnchorPoint({0, 0.5});
			g_message->setOpacity(100);
			addChild(g_message, 1001);
		}
		if (guiBools[4]) {
			//setAnchoredPosition(g_cheating, std::distance(item_names, std::find(item_names, item_names + 13, "Cheat Indicator")));
			//g_cheating->setPosition(5 , corner - 10);
			g_cheating->setScale(0.4);
			g_cheating->setAnchorPoint({0, 0.5});
			g_cheating->setOpacity(100);
			addChild(g_cheating, 1001);
		}
		if (guiBools[8]) {
			//setAnchoredPosition(g_run, std::distance(item_names, std::find(item_names, item_names + 13, "Run From")));
			//g_run->setPosition(5 , corner - 70);
			g_run->setScale(0.4);
			g_run->setAnchorPoint({0, 0.5});
			g_run->setOpacity(100);
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from: %.0lf%%", start);
			g_run->setString(str);

			addChild(g_run, 1000);
		}
		if (guiBools[3]) {
			//setAnchoredPosition(g_jumps, std::distance(item_names, std::find(item_names, item_names + 13, "Jumps")));
			//g_tatts->setPosition(5 , corner - 55);
			g_jumps->setScale(0.4);
			g_jumps->setAnchorPoint({0, 0.5});
			g_jumps->setOpacity(100);
			std::string po = "Total Jumps:" + std::to_string(gl->m_jumps);
			g_jumps->setString(po.c_str());
			addChild(g_jumps, 1001);
		}
		if (guiBools[11]) {
			//setAnchoredPosition(g_tatts, std::distance(item_names, std::find(item_names, item_names + 13, "Total Attempts")));
			//g_tatts->setPosition(5 , corner - 55);
			g_tatts->setScale(0.4);
			g_tatts->setAnchorPoint({0, 0.5});
			g_tatts->setOpacity(100);
			std::string at = "Global Atts:" + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
			addChild(g_tatts, 1001);
		}
		if (guiBools[5]) {
			//setAnchoredPosition(g_death, std::distance(item_names, std::find(item_names, item_names + 13, "Last Death")));
			//g_death->setPosition(5 , corner - 130);
			g_death->setScale(0.4);
			g_death->setAnchorPoint({0, 0.5});
			g_death->setOpacity(100);
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death:%.0lf%%", start);
			g_death->setString(str);

			addChild(g_death, 1000);
		}
		if (guiBools[10]) {
			//setAnchoredPosition(font, std::distance(item_names, std::find(item_names, item_names + 13, "Noclip Deaths")));
			//g_tatts->setPosition(5 , corner - 160);
			font->setScale(0.4);
			font->setAnchorPoint({0, 0.5});
			font->setOpacity(100);
			addChild(font, 1001);
		}
		if (guiBools[6]) {
			//setAnchoredPosition(g_atts, std::distance(item_names, std::find(item_names, item_names + 13, "Attempts Display")));
			//g_atts->setPosition(5 , corner - 40);
			g_atts->setScale(0.4);
			g_atts->setAnchorPoint({0, 0.5});
			g_atts->setOpacity(100);
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);

			addChild(g_atts, 1000);
		}
		if (guiBools[7]) {
			//setAnchoredPosition(g_bestRun, std::distance(item_names, std::find(item_names, item_names + 13, "Best Run")));
			//g_bestRun->setPosition(5 , corner - 85);
			g_bestRun->setScale(0.4);
			g_bestRun->setAnchorPoint({0, 0.5});
			g_bestRun->setOpacity(100);
			bestEnd = 0;
			bestStart = 0;
			bestEnd2 = 0;
			bestStart2 = 0;
			bestStart = (m_player1->getPositionX() / m_levelLength) * 100;
			addChild(g_bestRun, 1001);
		}
		if (guiBools[12]) {
			//setAnchoredPosition(g_levelInfo, std::distance(item_names, std::find(item_names, item_names + 13, "Level Name and ID")));
			std::string display;
			g_levelInfo->setScale(0.4);
			g_levelInfo->setAnchorPoint({0, 0.5});
			g_levelInfo->setOpacity(100);
			std::string levelName = gl->m_levelName;
			std::string levelAuthor = gl->m_creatorName;
			std::string levelID = std::to_string(gl->m_levelID);
			/*if (hideID) {
				levelID = "--------";
			} else */ if (levelID<"22" && levelID>"0" || levelID == "3" || levelID == "4" || levelID == "5" || levelID == "6" || levelID == "7" || levelID == "8" || levelID == "9") {
				levelAuthor = "RobTop"; // this wasnt working from Polargeist (3) to Cycles (9) so i had to do that lmao
			} else if (levelID == "0") {
				levelID = "Copy";
			}
			//if (author) {
				//display = levelName + " by " + levelAuthor + " (" + levelID + ")";
			//} else {
				display = levelName + " (" + levelID + ")";
			//}
			g_levelInfo->setString(display.c_str());
			addChild(g_levelInfo, 1001);
		}
		if (guiBools[2]) {
			//setAnchoredPosition(g_clicks, std::distance(item_names, std::find(item_names, item_names + 13, "CPS and Clicks")));
			//g_clicks->setPosition(5 , corner - 115);
			g_clicks->setScale(0.4);
			g_clicks->setAnchorPoint({0, 0.5});
			g_clicks->setOpacity(100);
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
			addChild(g_clicks, 1001);
		}
		if (guiBools[9]) {
			//setAnchoredPosition(text, std::distance(item_names, std::find(item_names, item_names + 13, "Noclip Accuracy")));
			//text->setPosition(5 , corner - 145);
			text->setAnchorPoint({0, 0.5});
			text->setTag(31403);
			text->setScale(0.4);
			text->setOpacity(100);
			addChild(text, 1000);
			frames = noclipped_frames = 0;
		}
		if (guiBools[15]) {
			//setAnchoredPosition(g_macro, std::distance(item_names, std::find(item_names, item_names + 13, "Macro Status")));
			//text->setPosition(5 , corner - 145);
			g_macro->setAnchorPoint({0, 0.5});
			g_macro->setScale(0.4);
			g_macro->setOpacity(100);
			std::string status = "Playing: 0/" + std::to_string(pushes.size());
			g_macro->setString(status.c_str());
			addChild(g_macro, 1000);
		}
		if (pausecountdown) {
			g_pauseCount->setPosition({ CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 175 });
			g_pauseCount->setAnchorPoint({0, 0.5});
			g_pauseCount->setOpacity(0);
			addChild(g_pauseCount, 1000);
		}
		CrystalClient::get()->arrangeText(13);
		return true;
	}
};

class CCDirectorVisible : public cocos2d::CCDirector {
public:
	void calculateDeltaTime() {
		CCDirector::calculateDeltaTime();
	};

	void setNextScene() {
		CCDirector::setNextScene();
	}
};

class $modify(CCDirector) {
	void drawScene() {

	FRAME_COUNTER++;

	// run full scene draw (glClear, visit) each time the counter is full
	if (FRAME_COUNTER >= DRAW_DIVIDE) {
		FRAME_COUNTER = 0;
		return CCDirector::drawScene();
	}

	auto visible_director = reinterpret_cast<CCDirectorVisible*>(this);

	if (!this->isPaused()) {
		this->getScheduler()->update(
			this->getDeltaTime()
		);
	}

	if (m_pNextScene) {
		visible_director->setNextScene();
	}
	}
};

class $(UILayer) {
	void customMod(int current) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		float tempSpeed = 1;
		if (current == 0) {
			playerBools[0] = !playerBools[0];
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
			if (playerBools[40]) {
				playerBools[40] = false;
				GJBaseGameLayer::get()->releaseButton(1,true);
			} else {
				playerBools[40] = true;
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

		for (int m = 0; m < activeMods.size(); m++) {
			if (kc == CrystalClient::shortcutKey(activeKeys[m])) {
				customMod(activeMods[m]);
			}
		}

		if (kc == KEY_F) {
			shouldUpdate = true;
			PlayLayer::get()->update(1.0/60.0);
			shouldUpdate = false;
		} else {
			UILayer::keyDown(kc);
		}
	}
};