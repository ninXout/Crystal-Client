#include "hackpro.hpp"
#include "amethyst.hpp"

// hackpro.hpp is where all the bools for the hacks are
// dispatchKeyboardMSG is where the imgui is

cocos2d::CCScene* gui;
ImGuiNode* node;

class $modify(MainDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
		auto platform = reinterpret_cast<PlatformToolbox*>(PlayLayer::get());
		node = ImGuiNode::create([]() {
			if (showing) {
				ImGuiStyle * style = &ImGui::GetStyle();
				ImVec4* colours = ImGui::GetStyle().Colors;
				/*
  colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  style->WindowPadding                     = ImVec2(8.00f, 8.00f);
  style->FramePadding                      = ImVec2(5.00f, 2.00f);
  style->CellPadding                       = ImVec2(6.00f, 6.00f);
  style->ItemSpacing                       = ImVec2(6.00f, 6.00f);
  style->ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
  style->TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
  style->IndentSpacing                     = 25;
  style->ScrollbarSize                     = 15;
  style->GrabMinSize                       = 10;
  style->WindowBorderSize                  = 1;
  style->ChildBorderSize                   = 1;
  style->PopupBorderSize                   = 1;
  style->FrameBorderSize                   = 1;
  style->TabBorderSize                     = 1;
  style->LogSliderDeadzone                 = 4;
*/

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
	//style->WindowRounding = 12.f;
	style->FrameRounding = 4.f;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;
	style->PopupRounding = 4.f;
	style->WindowBorderSize = 1.5f;
	colours[ImGuiCol_TitleBg] = RGBAtoIV4(BGColour);
	colours[ImGuiCol_TitleBgActive] = RGBAtoIV4(BGColour);
	colours[ImGuiCol_WindowBg] = RGBAtoIV4(BGColour);
	colours[ImGuiCol_Border] = RGBAtoIV4(LightColour);
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

				ImGui::Begin("General");
				for (int i = 0; i < playerHacks.size(); i++) {
					const char* name = playerHacks[i];
					ImGui::Checkbox(name, &playerBools[i]);
					if (i == 14) ImGui::InputFloat("Wave Trail Size", &pulse, 0.01f, 10.00f, "%.2f");
					if (i == 40) {
						ImGui::SliderInt("Push Frames", &clickPush, 1, 20);
						ImGui::SliderInt("Release Frames", &clickRel, 1, 20);
					}
				}
				ImGui::End();
				ImGui::Begin("Display");
				for (int i = 0; i < guiHacks.size(); i++) {
					const char* name = guiHacks[i];
					if (i != 9 && i != 2) ImGui::Checkbox(name, &guiBools[i]);
					if (i == 0) ImGui::InputTextWithHint("Message", "Custom Message", message, IM_ARRAYSIZE(message));
					if (i == 2) {
						if (ImGui::TreeNode("CPS and Clicks"))
    					{
							ImGui::Checkbox("CPS and Clicks", &guiBools[i]);
							ImGui::Checkbox("Reset clicks each attempt", &clickreset);
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
				ImGui::Begin("Bypasses");
				for (int i = 0; i < bypassHacks.size(); i++) {
					const char* name = bypassHacks[i];
					ImGui::Checkbox(name, &bypassBools[i]);
				}
				ImGui::End();
				ImGui::Begin("Global");
				for (int i = 0; i < globalHacks.size(); i++) {
					const char* name = globalHacks[i];
					ImGui::Checkbox(name, &globalBools[i]);
					if (i == 0) ImGui::InputInt("FPS Bypass", &bypass, 0, 1000);
					if (i == 1) {
						ImGui::InputFloat("Speedhack", &speedhack, 0.001f, 10.000f, "%.3f");
						if (!classicspeed) CCDirector::sharedDirector()->getScheduler()->setTimeScale(speedhack);
					}
				}
				ImGui::End();
				ImGui::Begin("Amethyst [BETA]");
				ImGui::Checkbox("Record", &record);
				ImGui::Checkbox("Replay", &replay);
				ImGui::Checkbox("Frame Accuracy", &frameAccuracy);
				ImGui::Checkbox("ClickBot", &clickBot);
				if (ImGui::Button("Clear Macro")) {
					xpos.clear();
					ypos.clear();
					rot.clear();
					push.clear();
				}
				ImGui::End();
				ImGui::Begin("Keybinds");
				for (int n = 0; n < bindKeys.size(); n++) {
					keybindings[n] = bindKeys[n];
				}
        		for (int n = 0; n < playerHacks.size(); n++) {
					modbindings[n] = playerHacks[n];
				}
				ImGui::Combo("Keybind", &currentKey, keybindings, IM_ARRAYSIZE(keybindings));
				ImGui::Combo("Mod to Switch", &currentMod, modbindings, IM_ARRAYSIZE(modbindings));
				if (ImGui::Button("Add Keybind")) {
					//activeKeys.push_back(keyCodes[currentKey]);
					//activeMods.push_back(currentMod);
				}
				ImGui::End();
				ImGui::Begin("Shortcuts");
				ImGui::Checkbox("Enable NONG Loader", &EnableNONGLoader);
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
				if (ImGui::Button("Toggle Practice Mode")) {
					if (PlayLayer::get()) PlayLayer::get()->togglePracticeMode(PlayLayer::get()->m_isPracticeMode == false);
				}
				if (ImGui::Button("Restart Level")) {
					if (PlayLayer::get()) PlayLayer::get()->resetLevel();
				}
				ImGui::End();
			}
		});
		cocos2d::CCLayer* layer;
        if (down && key == KEY_Tab) {
            if (!showing) {
				//loadMods();
				if (node) {
					gui = CCScene::create();
					node->setZOrder(999999);
					CCSprite* shoplifting = CCSprite::create("shoplifter.jpg");
					if (shoplifting != nullptr) {
						shoplifting->setPositionX(500);
						shoplifting->setPositionY(50);
						shoplifting->setScale(0.5);
						gui->addChild(shoplifting);
					}
					gui->addChild(node);
					CCDirector::sharedDirector()->getRunningScene()->addChild(gui);
					//CCDirector::sharedDirector()->getTouchDispatcher()->decrementForcePrio(2);
				}
				platform->showCursor();
				showing = true;
			} else {
				gui->removeFromParent();
				//saveMods();
				gui = nullptr;
				if (PlayLayer::get()) platform->hideCursor();
				showing = false;
			}
            return true;
        };
		
		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
	};
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

class Patch2 : public Patch {
 public:
 	Patch2(byte_array patch, byte_array original, uintptr_t address) : Patch() {
 		m_patch = patch;
 		m_original = original;
 		m_address = (void*)address;
 		m_owner = Mod::get();
 	}

	Patch2(char patch, char original, uintptr_t address) : Patch() {
 		m_patch = {patch};
 		m_original = {original};
 		m_address = (void*)(base::get() + address);
 		m_owner = Mod::get();
 	}
};

GEODE_API void GEODE_DLL geode_load(Mod* m) {
	fps_shower_init();
		Patch2* lol = new Patch2('\xeb', '\x76', base::get() + 0x18D811);
		lol->apply();
		Patch2* lol2 = new Patch2('\xeb', '\x76', base::get() + 0x18D7D9);
		lol2->apply();


		Patch2* lol3 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x25332);
		lol3->apply();
		Patch2* lol4 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x2533f);
		lol4->apply();

		(new Patch2('\xeb', '\x7c', 0x18bfa))->apply();
		(new Patch2('\xeb', '\x7c', 0x18f25))->apply();
		(new Patch2('\xeb', '\x7c', 0x1b991))->apply();

		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x949cd))->apply();
		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x94b1d))->apply();

		(new Patch2({'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, 0x1d67c))->apply();
		(new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, 0x1d869))->apply();

		(new Patch2({'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, 0x1d72d))->apply();
}



class $modify(PlayLayer) {
	static inline HitboxNode* drawer;

	bool init(GJGameLevel* lvl) {
		drawer = HitboxNode::create();
		auto ret = PlayLayer::init(lvl);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = playerBools[6];
		drawer->m_drawTrail = playerBools[8];
		s_onlyHitboxes = playerBools[7];
		if (s_showOnDeath) s_drawOnDeath = false;
		drawer->drawCircleHitbox(ccp(PlayLayer::get()->m_player1->getPositionX() + 30, PlayLayer::get()->m_player1->getPositionY()), 25, ccc4(255, 255, 255, 255));

		return ret;
	}
	void checkCollisions(PlayerObject* player, float uhh) {
		PlayLayer::checkCollisions(player, uhh);
		if (player == m_player1) {
			drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
	}
	void resetLevel() {
		if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();
        PlayLayer::resetLevel();
    }

	void update(float dt) {
		drawer->clear();
		//drawer->addToPlayer1Queue(m_player1->getObjectRect());
		if (!freeze) {
			PlayLayer::update(dt);
		}
		if (autoKill) {
			m_isDead = true;
			PlayLayer::resetLevel();
			autoKill = false; // so it doesnt loop
		}
		if (s_showOnDeath) {
			if (!turnonHitbox) return;
			if (!s_drawOnDeath) return;
			drawer->setVisible(true);
		}		

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
/*
    	++m_frames;
        m_accumulate += dt;

        if (m_accumulate > m_resetInterval) {
            float framerate = m_frames / m_accumulate;
            framerate = round(framerate * 10) / 10;
            m_frames = 0;
            m_accumulate = 0;
            
            std::stringstream stream;
        	stream << framerate << " FPS";
            m_label->setString(stream.str().c_str());
            m_backdrop->setContentSize(getBackdropSize());
        }
		*/
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

void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
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

float g = 0;

cocos2d::_ccColor3B getRainbow(float offset) {
	float R;
	float G;
	float B;

	float hue = fmod(g + offset, 360);
	//geode::log << hue;
	float sat = 1;
	float vc = 1;
	HSVtoRGB(R, G, B, hue, sat, vc);

	cocos2d::_ccColor3B out;
	out.r = R*255;
	out.g = G*255;
	out.b = B*255;
	return out;
}