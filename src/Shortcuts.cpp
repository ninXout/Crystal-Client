#include "Shortcuts.hpp"
#include "CrystalProfile.hpp"
#include "Hitbox/HitboxNode.hpp"
#include <Geode/modify/PlayLayer.hpp>

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

void Shortcuts::executeBinds(int current, bool down) {
    //auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
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
            if (down) GJBaseGameLayer::get()->pushButton(1, true);
            else GJBaseGameLayer::get()->releaseButton(1, true);
            break;
        case 9:
            if (down) GJBaseGameLayer::get()->pushButton(1, false);
            else GJBaseGameLayer::get()->releaseButton(1, false);
            break;
        case 10:
            if (PlayLayer::get()->m_isPracticeMode && down) PlayLayer::get()->markCheckpoint();
            break;
        case 11:
            if (PlayLayer::get()->m_isPracticeMode && down) PlayLayer::get()->removeLastCheckpoint();
            break;

    }
}

void Shortcuts::updateKeybinds(enumKeyCodes key, bool down) {
    for (int i = 0; i < keybinds.size(); i++) {
        if (key == CrystalClient::shortcutKey(keybinds[i].activeKey)) executeBinds(keybinds[i].activeMod, down);
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
        }
    }
}

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        Shortcuts::get()->updateKeybinds(key, down);

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};

class $modify(PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        Shortcuts::get()->updateVariables();
    }
};