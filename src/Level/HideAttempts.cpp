#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void update(float dt) {
        if (getVar<bool>("hide_attempts")) {
			if (getVar<bool>("hide_attempts_normal") && !m_isPracticeMode) m_attemptLabel->setVisible(false);
			if (getVar<bool>("hide_attempts_practice") && m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
        PlayLayer::update(dt);
    }
};