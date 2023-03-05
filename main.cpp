#include "platform/platform.hpp"
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "CrystalClient.hpp"
#include "Hacks.hpp"
#include <imgui.h>
#include "ImGui.hpp"

USE_GEODE_NAMESPACE();

using namespace crystal;


void CrystalClient::toggle() {
    auto platform = reinterpret_cast<PlatformToolbox*>(PlayLayer::get());
    if (!m_visible) {
        platform->showCursor();
    }
    if (m_visible) {
		CrystalClient::get()->saveMods();
        if (PlayLayer::get() && !PlayLayer::get()->m_isPaused && !PlayLayer::get()->m_hasLevelCompleteMenu) {
			platform->hideCursor();
			//CrystalClient::get()->arrangeText(13);
		}
    }
    this->show(!m_visible);
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
        ImGui::Checkbox(playerHacks[i], &playerBools[i]);
        if (i == 14) ImGui::InputFloat("Wave Trail Size", &pulse, 0.01f, 10.00f, "%.2f");
        if (i == 40) {
            ImGui::SliderInt("Push Frames", &clickPush, 1, 20);
            ImGui::SliderInt("Release Frames", &clickRel, 1, 20);
        }
    }
    ImGui::End();
    ImGui::Begin("Display");
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
    for (int i = 0; i < guiHacks.size(); i++) {
        if (i != 9 && i != 2) ImGui::Checkbox(guiHacks[i], &guiBools[i]);
        if (i == 0) ImGui::InputTextWithHint("Message", "Custom Message", message, IM_ARRAYSIZE(message));
        if (i == 2) {
            if (ImGui::TreeNode("CPS and Clicks"))
            {
                ImGui::Checkbox("CPS and Clicks", &guiBools[i]);
                //ImGui::Checkbox("Reset clicks each attempt", &clickreset);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
        if (i == 9) {
            if (ImGui::TreeNode("Noclip Accuracy"))
            {
                ImGui::Checkbox("Noclip Accuracy", &guiBools[i]);
                ImGui::Checkbox("Increased Leniency", &lenient);
                ImGui::InputFloat("Kill at Accuracy", &killaccuracy, 0.00f, 99.99f, "%.2f");
                ImGui::Checkbox("Reset at Accuracy", &resetaccuracy);
                ImGui::Separator();
                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
    ImGui::Begin("Customization");
    ImGui::ColorEdit4("Accent Color", LightColour);
    ImGui::ColorEdit4("Base Color", BGColour);
    ImGui::Checkbox("Base Color Same As Accent Color", &sameAsAccent);
    ImGui::Checkbox("RGB Accent Color", &RGBAccent);
    ImGui::Checkbox("Borders", &borders);
    ImGui::Checkbox("Rounded Windows", &rounded);
    ImGui::End();
    ImGui::Begin("Bypasses");
    ImGui::InputFloat("Editor Grid Size", &gridSize, 0.001f, 1000.000f, "%.3f");
    for (int i = 0; i < bypassHacks.size(); i++) {
        ImGui::Checkbox(bypassHacks[i], &bypassBools[i]);
    }
    ImGui::End();
    ImGui::Begin("Global");
    ImGui::InputInt("FPS Bypass", &bypass, 0, 1000);
    ImGui::InputFloat("Speedhack", &speedhack, 0.001f, 10.000f, "%.3f");
    CCDirector::sharedDirector()->getScheduler()->setTimeScale(speedhack);
    cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.0 / bypass);
    ImGui::InputInt("Draw Divide", &DRAW_DIVIDE, 0, 10);
    ImGui::End();
    ImGui::Begin("Amethyst [BETA]");
    ImGui::Checkbox("Record", &record);
	ImGui::SameLine();
    ImGui::Checkbox("Replay", &replay);
	ImGui::Checkbox("ClickBot", &clickBot);
	ImGui::SameLine();
	ImGui::Checkbox("Delta Lock", &deltaLock);
    ImGui::Combo("Macro Type", &currentMacroType, macroTypes, IM_ARRAYSIZE(macroTypes));
    ImGui::InputTextWithHint("Macro Name", "Macro Name", macroname, IM_ARRAYSIZE(macroname));
    if (ImGui::Button("Save Macro")) {
        std::string filename = "Crystal/Amethyst/Macros/" + (std::string)macroname + ".thyst";
        std::fstream myfile(filename.c_str(), std::ios::app);
        myfile << pushes.size();
        myfile << "\n";
        for (float val : pushes)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << releases.size();
        myfile << "\n";
        for (float val : releases)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << Pxpos.size();
        myfile << "\n";
        for (float val : Pxpos)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << Pypos.size();
        myfile << "\n";
        for (float val : Pypos)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << Paccel.size();
        myfile << "\n";
        for (float val : Paccel)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
		myfile << Rxpos.size();
        myfile << "\n";
        for (float val : Rxpos)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << Rypos.size();
        myfile << "\n";
        for (float val : Rypos)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
        myfile << Raccel.size();
        myfile << "\n";
        for (float val : Raccel)
        {
            myfile << std::setprecision(6) << std::fixed << val;
            myfile << "\n";
        }
    }
	ImGui::SameLine();
    if (ImGui::Button("Load Macro")) {
        std::string line;
        std::string filename = "Crystal/Amethyst/Macros/" + (std::string)macroname + ".thyst";
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
                getline(file, line);
                Pxpos.insert(Pxpos.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                Pypos.insert(Pypos.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                Paccel.insert(Paccel.end(), stof(line));
            }
			getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                Rxpos.insert(Rxpos.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                Rypos.insert(Rypos.end(), stof(line));
            }
            getline(file, line);
            len = stoi(line);
            for (int lineno = 1; lineno <= len; lineno++) {
                getline(file, line);
                Raccel.insert(Raccel.end(), stof(line));
            }
            file.close();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear Macro")) {
        pushes.clear();
        releases.clear();
        Pxpos.clear();
        Pypos.clear();
        Paccel.clear();
        Rxpos.clear();
        Rypos.clear();
        Raccel.clear();
        xpos.clear();
        ypos.clear();
        accel.clear();
        CPoffset.clear();
        CPaccel.clear();
        CProt.clear();
    }
    ImGui::End();
    ImGui::Begin("Keybinds");
    //ImGui::Combo("Keybind", &currentKey, keybindings, IM_ARRAYSIZE(keybindings));
    //ImGui::Combo("Mod to Switch", &currentMod, modbindings, IM_ARRAYSIZE(modbindings));
    if (ImGui::Button("Add Keybind")) {
        //activeKeys.push_back(currentKey);
        //activeMods.push_back(currentMod);
    }
    ImGui::End();
    ImGui::Begin("Shortcuts");
    //ImGui::Checkbox("Enable NONG Loader", &EnableNONGLoader);
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
}

void CrystalClient::saveMods() {
    std::ofstream clear("Crystal/modconfig.cmp");
    clear << "";
    clear.close();
    std::fstream config("Crystal/modconfig.cmp", std::ios::app);
    config << LightColour[0] << '\n';
    config << LightColour[1] << '\n';
    config << LightColour[2] << '\n';
    config << LightColour[3] << '\n';
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
    std::fstream config("Crystal/modconfig.cmp", std::ios::in);
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
	if (guiBools[0]) {
		setAnchoredPosition(g_message, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Custom Message")));
	}
	if (guiBools[4]) {
		setAnchoredPosition(g_cheating, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Cheat Indicator")));
	}
	if (guiBools[8]) {
		setAnchoredPosition(g_run, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Run From")));
	}
	if (guiBools[3]) {
		setAnchoredPosition(g_jumps, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Jumps")));
	}
	if (guiBools[11]) {
		setAnchoredPosition(g_tatts, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Total Attempts")));
	}
	if (guiBools[5]) {
		setAnchoredPosition(g_death, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Last Death")));
	}
	if (guiBools[10]) {
		setAnchoredPosition(font, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Noclip Deaths")));
	}
	if (guiBools[6]) {
		setAnchoredPosition(g_atts, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Attempts Display")));
	}
	if (guiBools[7]) {
		setAnchoredPosition(g_bestRun, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Best Run")));
	}
	if (guiBools[12]) {
		setAnchoredPosition(g_levelInfo, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Level Name and ID")));
	}
	if (guiBools[2]) {
		setAnchoredPosition(g_clicks, std::distance(item_names, std::find(item_names, item_names + arrayLength, "CPS and Clicks")));
	}
	if (guiBools[9]) {
		setAnchoredPosition(text, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Noclip Accuracy")));
	}
	if (guiBools[15]) {
		setAnchoredPosition(g_macro, std::distance(item_names, std::find(item_names, item_names + arrayLength, "Macro Status")));
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
        if (down && key == KEY_Tab) {
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

		if (m_player1) {
			float xp = m_player1->getPositionX();

			for (int s = sectionForPos(xp) - 10; s < sectionForPos(xp) + 10; ++s) {
				if (s < 0) continue;
				if (s >= m_sectionObjects->count()) break;
				auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
				for (size_t i = 0; i < this->getAllObjects()->count(); ++i) {
					auto obj = static_cast<GameObject*>(this->getAllObjects()->objectAtIndex(i));

					if (s_onlyHitboxes) obj->setOpacity(0);

					if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
					if (!obj->m_active) continue;

					drawer->drawForObject(obj);
				}
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
			s_drawer->clear();
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
			//ok->m_isVerifiedRand = 11;
			//ok->m_isVerifiedSeed = 10;
		}	
		if (playerBools[20]) {
			ok->m_lowDetailModeToggled = true;
		} 
		if (bypassBools[10]) cl = 1;
		return EditLevelLayer::create(ok);
	}

	bool init(GJGameLevel* ed) {
            EditLevelLayer::init(ed);
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
		return true;
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
			Pxpos.insert(Pxpos.end(), m_player1->getPositionX());
			Pypos.insert(Pypos.end(), m_player1->getPositionY());
			Paccel.insert(Paccel.end(), yAccel);
			auto clickInPush = std::find(pushes.begin(), pushes.end(), frame) != pushes.end();
			auto clickInRelease = std::find(releases.begin(), releases.end(), frame) != releases.end();

			if (!clickInPush) {
				pushes.insert(pushes.end(), frame);
			}
			if (clickInRelease) releases.remove(frame);
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
			Rxpos.insert(Rxpos.end(), m_player1->getPositionX());
			Rypos.insert(Rypos.end(), m_player1->getPositionY());
			Raccel.insert(Raccel.end(), yAccel);
			auto clickInRelease = std::find(releases.begin(), releases.end(), frame) != releases.end();
			auto clickInPush = std::find(pushes.begin(), pushes.end(), frame) != pushes.end();

			if (!clickInRelease) {
				releases.insert(releases.end(), frame);
			}
			if (clickInPush) pushes.remove(frame);
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
		if (playerBools[28]) { 
			m_isSolid = true;
			this->setBlendFunc(kCCBlendFuncDisable);
			this->setOpacity(255);
		}
		if (playerBools[4] && PlayLayer::get()) this->setColor(col);
		HardStreak::updateStroke(f);
	}
};

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		if (bypassBools[6]) {
			//g->m_passwordSeed = 20; // it can be anything
			//g->m_passwordRand = g->m_passwordSeed + 1;
		}

		if (playerBools[20]) {
			g->m_lowDetailModeToggled = true;
		}
		
		//getNONGs();
		//findsong = std::to_string(level->m_songID);

		if (bypassBools[10]) cl = 0;

		return LevelInfoLayer::create(g);
	}

	bool init(GJGameLevel* level) {
       		LevelInfoLayer::init(level);
    	if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
        return true;
 	}
};

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (playerBools[43]) pause->setVisible(false);
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
		if (playerBools[28]) {
			auto fadeOut = CCFadeOut::create(0.01);
			m_regularTrail->runAction(fadeOut);
		}
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
		CCScheduler::update(f3);
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
		}
		/*
		if (DrawGridLayer::get()) {
			DrawGridLayer::get()->m_activeGridNodeSize = gridSize;
			DrawGridLayer::get()->m_gridSize = gridSize;
		}
		*/
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
		switch (g->m_objectID) {
					case 10:
					case 11:
						gravityPortals.push_back(g);
						break;
					case 12:
					case 13:
					case 47:
					case 111:
					case 660:
					case 745:
					case 1331:
						gamemodePortals.push_back(g);
						break;
					case 45:
					case 46:
						mirrorPortals.push_back(g);
						break;
					case 99:
					case 101:
						miniPortals.push_back(g);
						break;
					case 286:
					case 287:
						dualPortals.push_back(g);
						break;
					case 200:
					case 201:
					case 202:
					case 203:
					case 1334:
						speedChanges.push_back(g);
						break;
				}
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
			if (CPoffset.size() == 0) CPoffset.push_back(0);
			offset = CPoffset.back();

			//mbo(float, GJBaseGameLayer::get()->m_player1, 0x7c8) = CPxpos.back();

			frame = (int)(m_time * 60) + offset;

			while (pushes.back() >= frame && pushes.size() != 0) {
				Pxpos.pop_back();
				Pypos.pop_back();
				Paccel.pop_back();
				pushes.pop_back();
			}

			while (releases.back() >= frame && releases.size() != 0) {
				Rxpos.pop_back();
				Rypos.pop_back();
				Raccel.pop_back();
				releases.pop_back();
			}

			if (pushing) {
				auto clickInPush = std::find(pushes.begin(), pushes.end(), frame) != pushes.end();
				auto clickInRelease = std::find(releases.begin(), releases.end(), frame) != releases.end();
				if (!clickInPush) pushes.insert(pushes.end(), frame);
				if (clickInRelease) releases.remove(frame);
			}

			mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = CPaccel.back();
			//mbo(float, GJBaseGameLayer::get()->m_player1, 0x7cc) = CPypos.back();
			GJBaseGameLayer::get()->m_player1->setRotation(CProt.back());
		} else {
			frame = 0;
			offset = 0;
			pushIt = releaseIt = posIt = 0;
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
		if (frames>20 && guiBools[10]) {
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
		if (playerBools[0]) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (playerBools[1]) {
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

			PlayLayer::checkCollisions(p, g);

            if (p == m_player1) {
			    drawer->addToPlayer1Queue(m_player1->getObjectRect());
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
		}

		if (m_player1) {
			if (playerBools[2]) m_player1->setColor(col);
			if (playerBools[3]) m_player1->setSecondColor(colInverse);
			if (playerBools[33]) m_player1->m_waveTrail->setVisible(false);
			//if (m_player1->m_waveTrail)
				//if (rainP1wave) m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			if (playerBools[3]) m_player2->setColor(colInverse);
			if (playerBools[2]) m_player2->setSecondColor(col);
			// if (playerBoolsm_player2->m_waveTrail)
				//if (rainP2wave) m_player2->m_waveTrail->setColor(colInverse);
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
		if (deltaLock) {
			auto dir = CCDirector::sharedDirector();

			float spf = (float)dir->getAnimationInterval();
			float tScale = dir->getScheduler()->getTimeScale();

			f4 = spf * tScale;
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
		m_percentLabel->setPositionX(percentXpos);
		m_percentLabel->setPositionY(percentYpos);
		m_percentLabel->setScale(percentScale);
		m_percentLabel->setOpacity(percentOpac);
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
					if (!freezeCount) PlayLayer::update(f4);
				}
			}
		}

		auto p1 = GJBaseGameLayer::get()->m_player1;
		auto p2 = GJBaseGameLayer::get()->m_player2;

		frame = (int)(m_time * 60) + offset;

		yAccel = (*reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(GJBaseGameLayer::get()->m_player1) + 0x760));

		if (replay && pushes.size() > 0) {
			if (std::find(pushes.begin(), pushes.end(), frame) != pushes.end()) {
				if (currentMacroType == 1) {
					//mbo(float, GJBaseGameLayer::get()->m_player1, 0x7c8) = Pxpos[pushIt];
					mbo(float, GJBaseGameLayer::get()->m_player1, 0x7cc) = Pypos[pushIt];
					mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = Paccel[pushIt];
				}
				GJBaseGameLayer::get()->pushButton(1, true);
				pushIt++;
			}

			if (std::find(releases.begin(), releases.end(), frame) != releases.end()) {
				if (currentMacroType == 1) {
					//mbo(float, GJBaseGameLayer::get()->m_player1, 0x7c8) = Rxpos[releaseIt];
					mbo(float, GJBaseGameLayer::get()->m_player1, 0x7cc) = Rypos[releaseIt];
					mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = Raccel[releaseIt];
				}
				GJBaseGameLayer::get()->releaseButton(1, true);
				releaseIt++;
			}
		}
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
		CPoffset.push_back(frame);
		CPaccel.push_back(yAccel);
		CProt.push_back(GJBaseGameLayer::get()->m_player1->getRotation());
		//std::get<std::deque<int>>(Player1Data["Checkpoints"]).insert(std::get<std::deque<int>>(Player1Data["Checkpoints"]).end(), frame);
	}

	void removeLastCheckpoint() {
		if (playerBools[26]) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		CPoffset.pop_back();
		CPaccel.pop_back();
		CProt.pop_back();
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

	void onQuit() {
		FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (!shouldQuit && playerBools[19] && !m_hasLevelCompleteMenu && !CCDirector::sharedDirector()->getKeyboardDispatcher()->getShiftKeyPressed()) {
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
		if (playerBools[41]) {
			for (int c = 0; c < PlayLayer::get()->m_objects->count(); c++) {
				GameObject* g = reinterpret_cast<GameObject*>(PlayLayer::get()->m_objects->objectAtIndex(c));
				
			}
		}

		if (playerBools[41]) {
			//willFlip.resize(gravityPortals.size());
			for (StartPosObject* startPos : SPs) {
		for (int i = 0; i < gravityPortals.size(); i++)
		{
			if (gravityPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gravityPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				willFlip.push_back(gravityPortals[i]->m_objectID == 11);
		}
		//startPos->m_levelSettings->m_startDual = GJBaseGameLayer::get()->m_levelSettings->m_startDual;
		for (int i = 0; i < dualPortals.size(); i++)
		{
			if (dualPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (dualPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				startPos->m_levelSettings->m_startDual = (dualPortals[i]->m_objectID == 286);
		}
		//startPos->m_levelSettings->m_startMode = GJBaseGameLayer::get()->m_levelSettings->m_startMode;
		for (size_t i = 0; i < gamemodePortals.size(); i++)
		{
			if (gamemodePortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gamemodePortals[i]->getPositionX() - 10 < startPos->getPositionX())
			{
				switch (gamemodePortals[i]->m_objectID)
				{
				case 12:
					//startPos->m_levelSettings->m_startMode = 0;
					break;
				case 13:
					//startPos->m_levelSettings->m_startMode = 1;
					break;
				case 47:
					//startPos->m_levelSettings->m_startMode = 2;
					break;
				case 111:
					//startPos->m_levelSettings->m_startMode = 3;
					break;
				case 660:
					//startPos->m_levelSettings->m_startMode = 4;
					break;
				case 745:
					//startPos->m_levelSettings->m_startMode = 5;
					break;
				case 1331:
					//startPos->m_levelSettings->m_startMode = 6;
					break;
				}
			}
		}
		//startPos->m_levelSettings->m_startMini = GJBaseGameLayer::get()->m_levelSettings->m_startMini;
		for (size_t i = 0; i < miniPortals.size(); i++)
		{
			if (miniPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (miniPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				startPos->m_levelSettings->m_startMini = miniPortals[i]->m_objectID == 101;
		}

		//startPos->m_levelSettings->m_startSpeed = GJBaseGameLayer::get()->m_levelSettings->m_startSpeed;
		for (size_t i = 0; i < speedChanges.size(); i++)
		{
			if (speedChanges[i]->getPositionX() - 50 > startPos->getPositionX())
				break;
			if (speedChanges[i]->getPositionX() - 50 < startPos->getPositionX())
			{
				switch (speedChanges[i]->m_objectID)
				{
				case 200:
					//startPos->m_levelSettings->m_startSpeed = 0;
					break;
				case 201:
					//startPos->m_levelSettings->m_startSpeed = 1;
					break;
				case 202:
					//startPos->m_levelSettings->m_startSpeed = 2;
					break;
				case 203:
					//startPos->m_levelSettings->m_startSpeed = 3;
					break;
				case 1334:
					//startPos->m_levelSettings->m_startSpeed = 4;
					break;
				}
			}
		}
	}
		}
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

		PlayLayer::init(gl);
		setupSmartSP();

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
			percentXpos = m_percentLabel->getPositionX();
			percentYpos = m_percentLabel->getPositionY();
			percentScale = m_percentLabel->getScale();
			percentOpac = m_percentLabel->getOpacity();
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

class $modify(CCDirector) {
	void drawScene() {

	FRAME_COUNTER++;

	// run full scene draw (glClear, visit) each time the counter is full
	if (FRAME_COUNTER >= DRAW_DIVIDE) {
		FRAME_COUNTER = 0;
		return CCDirector::drawScene();
	}

	if (!this->isPaused()) {
		this->getScheduler()->update(
			this->getDeltaTime()
		);
	}

	if (m_pNextScene) {
		setNextScene();
	}
	}
};

class $(UILayer) {
/*
	void customMod(int current) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		bool hitbox = true;
		float tempSpeed = 1;
		if (current == 0) {
			noclip = !noclip;
		} else if (current == 1) {
			autoKill = !autoKill;
		} else if (current == 2) {
			PlayLayer::get()->resetLevel();
		} else if (current == 3) {
			if (speedhack != 1) {
				tempSpeed = speedhack;
				speedhack = 1;
			} else {
				speedhack = tempSpeed;
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
*/
	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		if (kc == KEY_R) {
			PlayLayer::get()->resetLevel();
		} else {
			UILayer::keyDown(kc);
		}
	}
};

class $modify(CreatorLayer) {
    virtual bool init() {
            CreatorLayer::init();
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
            LeaderboardsLayer::init(state);
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
        return true;
    }
};

class $modify(LocalLevelManager) {
    bool init() {
            LocalLevelManager::init();
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
        return true;
    }
};

class $modify(LevelSearchLayer) {
    bool init() {
        	LevelSearchLayer::init();
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}
        return true;
    }
};

class $modify(LevelBrowserLayer) {
    bool init(GJSearchObject* search) {
            LevelBrowserLayer::init(search);
		if (globalHacks[8]) {
        	auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto bg = CCSprite::create("GJ_gradientBG.png");
	    	auto bgSize = bg->getTextureRect().size;
	    	
			bg->setAnchorPoint({ 0.0f, 0.0f });
	    	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	    	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
        	bg->setPosition({ -5.0f, -5.0f });
	    	bg->setColor(ccc3(255, 255, 255));
	    
        this->addChild(bg, -2);
	}

        return true;
    }
};
