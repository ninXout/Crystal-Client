#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "PracticeFix.hpp"
#include "../../Utilities/utilities.hpp"

using namespace CrystalClient;

std::vector<FixedCheckpoint> checkpoints;

class $modify(PlayLayer) {
    CheckpointObject* markCheckpoint() {
        CheckpointObject* cp = PlayLayer::markCheckpoint();

        checkpoints.push_back(FixedCheckpoint::create(m_player1));

        return cp;
    }

    void removeCheckpoint(bool b) {
        PlayLayer::removeCheckpoint(b);

        if (checkpoints.size() > 0) checkpoints.pop_back();
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        if (m_isPracticeMode && checkpoints.size() > 0 && getSavedVar<bool>("practice_fix")) checkpoints.back().apply(m_player1);
    }
};