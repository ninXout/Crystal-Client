#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "Amethyst.hpp"

int actionsIndex = 0;

using namespace Amethyst;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool b1, bool b2) {
        if (!PlayLayer::init(gj, b1, b2)) return false;

        macro.author = "N/A";
	    macro.description = "N/A";

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        actionsIndex = 0;

        if (getSavedVar<bool>("AT-replay")) {
            Amethyst::checkpoints.clear();
            Amethyst::totalTime = 0.f;
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, true);
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, false);
        }

        if (getSavedVar<bool>("AT-record") && m_isPracticeMode) {
            totalTime = checkpoints.back();

            while (macro.inputs.size() > 0 && macro.inputs.back().frame >= (int)(totalTime * 60.f)) {
                log::debug("removed at {}", macro.inputs.back().frame);
                macro.inputs.pop_back();
            }
        }
    }
};

class $modify(GJBaseGameLayer) {
    void handleButton(bool push, int button, bool player1) {
        GJBaseGameLayer::handleButton(push, button, player1);

        if (getSavedVar<bool>("AT-record")) {
            macro.inputs.push_back(AmethystInput((int)(totalTime * 60.f), button, !player1, push));
            log::debug("recorded at {}", (int)(totalTime * 60.f));
        }
    }

    void update(float dt) {
        GJBaseGameLayer::update(dt);

        Amethyst::totalTime += dt;
        //log::debug("current frame: {}", (int)(Amethyst::totalTime * 60.f));

        if (getSavedVar<bool>("AT-replay") && macro.inputs.size() > 0) {
            if (macro.inputs[actionsIndex].frame >= (int)(totalTime * 60.f)) {
                GJBaseGameLayer::handleButton(macro.inputs[actionsIndex].down, macro.inputs[actionsIndex].button, !macro.inputs[actionsIndex].player2);
                log::debug("played at {}", macro.inputs[actionsIndex].frame);
                actionsIndex++;
            }
        }
    }
};

class $modify(CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool idk) {
        // temporary until i get the checkpoint stuff
        if (down && key == KEY_Z && PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && getSavedVar<bool>("AT-record")) {
            Amethyst::checkpoints.push_back(Amethyst::totalTime);
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        } 

        if (down && key == KEY_X && PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && getSavedVar<bool>("AT-record")) {
            Amethyst::checkpoints.pop_back();
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        } 

        if (down && key == KEY_L && PlayLayer::get()) {
            macro.inputs.clear();
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        }

        if (down && key == KEY_P && PlayLayer::get()) {
            PlayLayer::get()->togglePracticeMode(!PlayLayer::get()->m_isPracticeMode);
            return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
    }
};