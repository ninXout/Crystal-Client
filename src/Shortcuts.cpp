#include "Shortcuts.hpp"
#include "CrystalProfile.hpp"
#include "Hitbox/HitboxNode.hpp"
#include "Level/StartPosSwitcher.hpp"
#include "CrystalClient/CrystalClient.hpp"
#include "Renderer/Screenshot.hpp"

bool pushing = false;

Shortcuts* Shortcuts::get() {
    static auto inst = new Shortcuts;
    return inst;
}

void Shortcuts::pushKeybind(Keybind key) {
    keybinds.push_back(key);
}

void Shortcuts::pushVariable(VarChange var) {
    variables.push_back(var);
}

void Shortcuts::executeBinds(int current, bool down, bool global) {
    if (!PlayLayer::get() || ((current == 8 || current == 9) && !GJBaseGameLayer::get())) return;
    if (global) {
        switch (current) {
            case 0:
                if (down) *setVar<bool>("noclip") = !getVar<bool>("noclip");
                break;
            case 1:
                if (down) PlayLayer::get()->destroyPlayer(PlayLayer::get()->m_player1, nullptr);
                break;
            case 2:
                if (down) PlayLayer::get()->resetLevel();
                break;
            case 3:
                if (down) {
                    if (getVar<float>("speed") != 1.0) {
                        CCDirector::sharedDirector()->getScheduler()->setTimeScale(1);
                    } else {
                        CCDirector::sharedDirector()->getScheduler()->setTimeScale(getVar<float>("speed"));
                    }
                }
                break;
            case 4:
                if (down) s_drawer->setVisible(!s_drawer->isVisible());
                break;
            case 5:
                if (down) {
                    if (getVar<bool>("autoclicker")) {
                        *setVar<bool>("autoclicker") = false;
                        GJBaseGameLayer::get()->releaseButton(1,true);
                        GJBaseGameLayer::get()->releaseButton(1,false);
                    } else {
                        *setVar<bool>("autoclicker") = true;
                    }
                }
                break;
            case 8:
                if (down && !pushing) GJBaseGameLayer::get()->pushButton(1, true);
                else if (!down && pushing) GJBaseGameLayer::get()->releaseButton(1, true);
                break;
            case 9:
                if (down && !pushing) GJBaseGameLayer::get()->pushButton(1, false);
                else if (!down && pushing) GJBaseGameLayer::get()->releaseButton(1, false);
                break;
            case 10:
                if (PlayLayer::get()->m_isPracticeMode && down) PlayLayer::get()->markCheckpoint();
                break;
            case 11:
                if (PlayLayer::get()->m_isPracticeMode && down) PlayLayer::get()->removeLastCheckpoint();
                break;
            case 13:
                if (getVar<bool>("framestep") && down) {
                    *setTempVar<bool>("should_update") = true;
                    CCDirector::sharedDirector()->getScheduler()->update(1.f / getVar<float>("FPS"));
                    *setTempVar<bool>("should_update") = false;
                }
                break;
            case 14:
            #ifdef GEODE_IS_MACOS
                if (down) Screenshot::create().saveImage(false);
            #endif
                break;
        }
    } else {
        switch (current) {
            case 6:
                if (down && getVar<bool>("startpos_switch")) updateIndex(false);
                break;
            case 7:
                if (down && getVar<bool>("startpos_switch")) updateIndex(true);
                break;
        }
    }
}

void Shortcuts::refreshKeybinds(bool save) {
    if (!save) {
        keybinds.clear();
        for (int i = 0; i < getVar<int>("keybindsSize"); i++) {
            std::string modkey = "keybind_key-" + std::to_string(i);
            std::string keykey = "keybind_mod-" + std::to_string(i);
            keybinds.push_back({getVar<int>(keykey), getVar<int>(modkey)});
        }
    } else {
        *setVar<int>("keybindsSize") = keybinds.size();
        for (int i = 0; i < keybinds.size(); i++) {
            std::string modkey = "keybind_key-" + std::to_string(i);
            std::string keykey = "keybind_mod-" + std::to_string(i);
            *setVar<int>(modkey) = keybinds[i].activeMod;
            *setVar<int>(keykey) = keybinds[i].activeKey;
        }
    }
}

void Shortcuts::updateKeybinds(enumKeyCodes key, bool down, bool global) {
    for (int i = 0; i < keybinds.size(); i++) {
        if (key == CrystalClient::shortcutKey(keybinds[i].activeKey)) executeBinds(keybinds[i].activeMod, down, global);
    }
}

void Shortcuts::updateVariables() {
    for (int i = 0; i < variables.size(); i++) {
        switch (variables[i].activeVar) {
            case 0:
                PlayLayer::get()->m_player1->m_gravity = variables[i].activeValue;
                break;
            case 1:
                PlayLayer::get()->m_player1->m_xVelocity = variables[i].activeValue;
                break;
            case 2:
                PlayLayer::get()->m_player1->m_yVelocity = variables[i].activeValue;
                break;
            case 3:
                PlayLayer::get()->m_player1->m_position.x = variables[i].activeValue;
                break;
            case 4:
                PlayLayer::get()->m_player1->m_position.y = variables[i].activeValue;
                break;
            case 5:
                PlayLayer::get()->m_player1->m_jumpAccel = variables[i].activeValue;
                break;
            case 6:
                PlayLayer::get()->m_player1->m_vehicleSize = variables[i].activeValue;
                break;
            case 7:
                PlayLayer::get()->m_player1->m_waveTrail->setOpacity(variables[i].activeValue);
                break;
        }
    }
}

#include <Geode/modify/CCKeyboardDispatcher.hpp>

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        if (down && key == KEY_Tab) {
            CrystalClient::get()->toggle();
            return true;
        }

        Shortcuts::get()->updateKeybinds(key, down, true);

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};

#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        Shortcuts::get()->updateVariables();
    }
};

#include <Geode/modify/UILayer.hpp>

class $modify(UILayer) {
    void keyDown(cocos2d::enumKeyCodes key) {
        Shortcuts::get()->updateKeybinds(key, true, false);

        UILayer::keyDown(key);
    }
};

#include <Geode/modify/GJBaseGameLayer.hpp>

class $modify(GJBaseGameLayer) {
    void pushButton(int i, bool pl) {
        GJBaseGameLayer::pushButton(i, pl);
        pushing = true;
    }

    void releaseButton(int i, bool pl) {
        GJBaseGameLayer::releaseButton(i, pl);
        pushing = false;
    }
};