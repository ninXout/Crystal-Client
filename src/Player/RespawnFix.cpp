#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

// Copied from fig/FigmentBoy's Respawn Bug Fix

int smoothOut = 0;

class $modify(PlayLayer) {
    void update(float dt) {
        if (!getVar<bool>("respawn_fix") || (getVar<bool>("respawn_fix") && !smoothOut)) {
            PlayLayer::update(dt);
        } else if (getVar<bool>("respawn_fix")) {
            float time = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();
            if (smoothOut != 0 && dt - time < 1) {
                smoothOut --;
            }

            if (getVar<bool>("AMT_record") || getVar<bool>("AMT_replay")) time = dt;

            PlayLayer::update(time);
        }
    }

    void resetLevel() {
        if (getVar<bool>("respawn_fix")) {
			if (m_isTestMode || m_isPracticeMode) {
				smoothOut = 2;
			}
		}
        PlayLayer::resetLevel();
    }
};