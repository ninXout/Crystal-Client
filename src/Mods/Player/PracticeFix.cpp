#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "PracticeFix.hpp"
#include "../../Utilities/utilities.hpp"

using namespace CrystalClient;

std::vector<FixedCheckpoint> checkpointsP1;
std::vector<FixedCheckpoint> checkpointsP2;

class $modify(PlayLayer) {
    CheckpointObject* markCheckpoint() {
        CheckpointObject* cp = PlayLayer::markCheckpoint();

        checkpointsP1.push_back(FixedCheckpoint::create(m_player1));
        checkpointsP2.push_back(FixedCheckpoint::create(m_player2));

        return cp;
    }

    void removeCheckpoint(bool b) {
        PlayLayer::removeCheckpoint(b);

        if (checkpointsP1.size() > 0) checkpointsP1.pop_back();
        if (checkpointsP2.size() > 0) checkpointsP2.pop_back();
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        if (m_isPracticeMode && checkpointsP1.size() > 0 && getSavedVar<bool>("practice_fix") && m_player1) checkpointsP1.back().apply(m_player1);
        if (m_isPracticeMode && checkpointsP2.size() > 0 && getSavedVar<bool>("practice_fix") && m_player2) checkpointsP2.back().apply(m_player2);
    }
};