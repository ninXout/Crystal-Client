#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void checkCollisions(PlayerObject* p, float g) {
		if (getVar<bool>("anticheat")) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
			m_inlineCalculatedKickTime = 0.0;
			m_accumulatedKickCounter = 0;
			m_kickCheckDeltaSnapshot = (float)std::time(nullptr);
		}

        PlayLayer::checkCollisions(p, g);
    }
};