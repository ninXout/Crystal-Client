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

        macro.author = GJAccountManager::sharedState()->m_username;
	    macro.description = "Recorded with Amethyst";
        macro.gameVersion = 2.200;
        macro.levelInfo.id = gj->m_levelID;
        macro.levelInfo.name = gj->m_levelName;

        if (getSavedVar<bool>("AT-record")) macro.inputs.clear();

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        actionsIndex = 0;

        if (getSavedVar<bool>("AT-replay")) {
            Amethyst::totalTime = 0.f;
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, true);
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, false);
        }

        if (getSavedVar<bool>("AT-record") && m_isPracticeMode) {
            totalTime = checkpoints.back();

            while (macro.inputs.size() > 0 && macro.inputs.back().frame >= static_cast<uint32_t>(totalTime * (double)240.f)) {
                log::debug("removed at {}", macro.inputs.back().frame);
                macro.inputs.pop_back();
            }
        }
    }

    CheckpointObject* markCheckpoint() {
        CheckpointObject* cp = PlayLayer::markCheckpoint();

        checkpoints.push_back(Amethyst::totalTime);

        return cp;
    }

    void removeCheckpoint(bool b) {
        PlayLayer::removeCheckpoint(b);

        if (checkpoints.size() > 0) checkpoints.pop_back();
    }
};

class $modify(GJBaseGameLayer) {
    void handleButton(bool push, int button, bool player1) {
        GJBaseGameLayer::handleButton(push, button, player1);

        if (getSavedVar<bool>("AT-record")) {
            macro.inputs.push_back(AmethystInput(static_cast<uint32_t>(totalTime * (double)240.f), button, !player1, push));
            log::debug("recorded at {}", static_cast<uint32_t>(totalTime * (double)240.f));
        }
    }

    void update(float dt) {
        GJBaseGameLayer::update(dt);

        Amethyst::totalTime += dt;
        //log::debug("current frame: {}", (int)(Amethyst::totalTime * 240.f));

        if (getSavedVar<bool>("AT-replay") && macro.inputs.size() > 0) {
            if (macro.inputs[actionsIndex].frame <= static_cast<uint32_t>(totalTime * (double)240.f)) {
                GJBaseGameLayer::handleButton(macro.inputs[actionsIndex].down, macro.inputs[actionsIndex].button, !macro.inputs[actionsIndex].player2);
                log::debug("played at {}", macro.inputs[actionsIndex].frame);
                actionsIndex++;
            }
        }
    }
};