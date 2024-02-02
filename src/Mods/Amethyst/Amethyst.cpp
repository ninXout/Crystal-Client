#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "Amethyst.hpp"

bool tempPracticeMode = false;
int actionsIndex = 0;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool b1, bool b2) {
        if (!PlayLayer::init(gj, b1, b2)) return false;

        Amethyst::checkpoints.clear();
        tempPracticeMode = false;
        Amethyst::totalDT = 0.f;

        return true;
    }

    void postUpdate(float dt) { //until GJBaseGameLayer::update
        PlayLayer::postUpdate(dt);

        Amethyst::totalDT += dt;

        if (getSavedVar<bool>("AT-replay")) {
            if (Amethyst::actions[actionsIndex].frame <= (Amethyst::totalDT * 240.f)) {
                handleButton(Amethyst::actions[actionsIndex].pressed, Amethyst::actions[actionsIndex].button, Amethyst::actions[actionsIndex].player1);
                actionsIndex++;
            }
        }
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        actionsIndex = 0;

        if (getSavedVar<bool>("AT-record") && tempPracticeMode) {
            Amethyst::totalDT = Amethyst::checkpoints.back();

            while (Amethyst::actions.back().frame > (Amethyst::totalDT * 240.f)) Amethyst::actions.pop_back();
        }
    }
};

class $modify(PauseLayer) {
    void onPracticeMode(cocos2d::CCObject* obj) {
        PauseLayer::onPracticeMode(obj);

        tempPracticeMode = !tempPracticeMode;
    }
};

class $modify(GJBaseGameLayer) {
    void handleButton(bool push, int button, bool player1) {
        GJBaseGameLayer::handleButton(push, button, player1);

        if (getSavedVar<bool>("AT-record")) Amethyst::actions.push_back({player1, static_cast<int>(Amethyst::totalDT * 240.f), button, push});
    }
};

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool idk) {
        if (down && key == KEY_Z && tempPracticeMode && PlayLayer::get() && getSavedVar<bool>("AT-record")) {
            Amethyst::checkpoints.push_back(Amethyst::totalDT);
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        } 

        if (down && key == KEY_X && tempPracticeMode && PlayLayer::get() && getSavedVar<bool>("AT-record")) {
            Amethyst::checkpoints.pop_back();
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        } 

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
    }
};