#include "ImGui.hpp"
#include "../Shortcuts.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCMouseDispatcher.hpp>
#include <Geode/modify/CCIMEDispatcher.hpp>
#include <Geode/modify/CCTouchDispatcher.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

#include <imgui.h>

using namespace geode::prelude;

using namespace Shortcuts;
using namespace Variables;
using namespace Crystal;
using namespace AmethystReplay;
using namespace Icon;

$on_mod(Unloaded) {
	ImGuiCocos::get().destroy();
}

class $modify(CCMouseDispatcher) {
    bool dispatchScrollMSG(float y, float x) {
        auto& io = ImGui::GetIO();
		static constexpr float scrollMult = 1.f / 10.f;
        io.AddMouseWheelEvent(x * scrollMult, -y * scrollMult);

        if (!io.WantCaptureMouse) {
            return CCMouseDispatcher::dispatchScrollMSG(y, x);
        }
        return true;
    }
};

class $modify(CCIMEDispatcher) {
    void dispatchInsertText(const char* text, int len) {
        auto& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {
            CCIMEDispatcher::dispatchInsertText(text, len);
        }
        std::string str(text, len);
        io.AddInputCharactersUTF8(str.c_str());
    }

    void dispatchDeleteBackward() {
        auto& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {
            CCIMEDispatcher::dispatchDeleteBackward();
        }
        // is this really how youre supposed to do this
        io.AddKeyEvent(ImGuiKey_Backspace, true);
        io.AddKeyEvent(ImGuiKey_Backspace, false);
    }
};

ImGuiKey cocosToImGuiKey(cocos2d::enumKeyCodes key) {
	switch (key) {
		case KEY_Up: return ImGuiKey_UpArrow;
		case KEY_Down: return ImGuiKey_DownArrow;
		case KEY_Left: return ImGuiKey_LeftArrow;
		case KEY_Right: return ImGuiKey_RightArrow;

		case KEY_Control: return ImGuiKey_ModCtrl;
		case KEY_Shift: return ImGuiKey_ModShift;
		case KEY_Alt: return ImGuiKey_ModAlt;
		case KEY_Enter: return ImGuiKey_Enter;

		default: return ImGuiKey_None;
	}
}

class $modify(CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        cocos2d::enumKeyCodes dispatchedkey = KEY_Tab;
		for (int m = 0; m < keybinds.size(); m++) {
			if (GJBaseGameLayer::get()) {
				if (keybinds[m].activeMod == 8 && down && !P1pushing && key == CrystalClient::shortcutKey(keybinds[m].activeKey)) {
					GJBaseGameLayer::get()->pushButton(1, true);
				} 
				if (keybinds[m].activeMod == 8 && !down && P1pushing && key == CrystalClient::shortcutKey(keybinds[m].activeKey)) {
					GJBaseGameLayer::get()->releaseButton(1, true);
				}
				if (keybinds[m].activeMod == 9 && down && !P2pushing && key == CrystalClient::shortcutKey(keybinds[m].activeKey)) {
					GJBaseGameLayer::get()->pushButton(1, false);
				} 
				if (keybinds[m].activeMod == 9 && !down && P2pushing && key == CrystalClient::shortcutKey(keybinds[m].activeKey)) {
					GJBaseGameLayer::get()->releaseButton(1, false);
				}
			}
			if (keybinds[m].activeMod == 12) {
				dispatchedkey = CrystalClient::shortcutKey(keybinds[m].activeKey);
			}
		}
        if (down && key == dispatchedkey) {
            ImGuiCocos::get().toggle();
            return true;
        }
		if (!ImGui::GetIO().WantCaptureKeyboard && !ImGuiCocos::get().isVisible()) {
			return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
		}
		const auto imKey = cocosToImGuiKey(key);
		if (imKey != ImGuiKey_None) {
			ImGui::GetIO().AddKeyEvent(imKey, down);
		}
		return false;
	}
};

enum TouchMessageType : unsigned int {
    Began = 0,
    Moved = 1,
    Ended = 2,
    Cancelled = 3
};

class $modify(CCTouchDispatcher) {
    void touches(CCSet* touches, CCEvent* event, unsigned int type) {
        auto& io = ImGui::GetIO();
        auto* touch = static_cast<CCTouch*>(touches->anyObject());
        const auto pos = ImGuiCocos::get().cocosToFrame(touch->getLocation());
        io.AddMousePosEvent(pos.x, pos.y);
        if (io.WantCaptureMouse) {
            if (type == TouchMessageType::Began || type == TouchMessageType::Moved) {
                io.AddMouseButtonEvent(0, true);
            } else {
                io.AddMouseButtonEvent(0, false);
            }
        } else {
            if (type != TouchMessageType::Moved) {
                io.AddMouseButtonEvent(0, false);
            }
            if (!ImGuiCocos::get().isVisible()) {
                CCTouchDispatcher::touches(touches, event, type);
            }
        }
    }
};

class $modify(CCEGLView) {
    void swapBuffers() {
		ImGuiCocos::get().drawFrame();
        CCEGLView::swapBuffers();
    }

#ifdef GEODE_IS_WINDOWS
    void toggleFullScreen(bool value) {
        ImGuiCocos::get().destroy();
        CCEGLView::toggleFullScreen(value);
        ImGuiCocos::get().setup();
    }
#endif
};