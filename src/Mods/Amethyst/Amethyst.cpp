#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "Amethyst.hpp"

int actionsIndex = 0;
bool hasStarted = false;

using namespace Amethyst;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool b1, bool b2) {
        hasStarted = false;

        if (!PlayLayer::init(gj, b1, b2)) return false;

        macro.author = GJAccountManager::sharedState()->m_username;
	    macro.description = "Recorded with Amethyst";
        macro.gameVersion = 2.200;
        macro.levelInfo.id = gj->m_levelID;
        macro.levelInfo.name = gj->m_levelName;

        Amethyst::frame = 0.f;
        if (getSavedVar<bool>("AT-record")) macro.inputs.clear();
        if (getSavedVar<bool>("AT-replay")) {
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, true);
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, false);
        }

        return true;
    }

    void startGame() {
        PlayLayer::startGame();
        hasStarted = true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        actionsIndex = 0;

        if (getSavedVar<bool>("AT-replay")) {
            Amethyst::frame = 0.f;
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, true);
            static_cast<GJBaseGameLayer*>(PlayLayer::get())->handleButton(false, 0, false);
        }

        if (getSavedVar<bool>("AT-record") && m_isPracticeMode) {
            frame = checkpoints.back();

            while (macro.inputs.size() > 0 && macro.inputs.back().frame >= frame) {
                log::debug("removed at {}", macro.inputs.back().frame);
                macro.inputs.pop_back();
            }
        }
    }

    CheckpointObject* markCheckpoint() {
        CheckpointObject* cp = PlayLayer::markCheckpoint();

        checkpoints.push_back(Amethyst::frame);

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
            macro.inputs.push_back(AmethystInput(frame, button, !player1, push));
            log::debug("recorded at {}", frame);
        }
    }

    void processCommands(float dt) {
        GJBaseGameLayer::processCommands(dt);

        if (hasStarted) Amethyst::frame += static_cast<uint32_t>(dt * (double)macro.framerate);
        //log::debug("current game frame: {}", static_cast<uint32_t>(PlayLayer::get()->m_gameState.m_unk1e0 * (double)macro.framerate));

        if (getSavedVar<bool>("AT-replay") && macro.inputs.size() > 0) {
            if (macro.inputs[actionsIndex].frame <= (frame)) {
                GJBaseGameLayer::handleButton(macro.inputs[actionsIndex].down, macro.inputs[actionsIndex].button, !macro.inputs[actionsIndex].player2);
                log::debug("played at {}", macro.inputs[actionsIndex].frame);
                actionsIndex++;
            }
        }
    }
};