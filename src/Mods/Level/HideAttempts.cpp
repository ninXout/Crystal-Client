#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void update(float dt) {
        if (getSavedVar<bool>("hide_attempts")) {
			if (getSavedVar<bool>("hide_attempts_normal") && !m_isPracticeMode) m_attemptLabel->setVisible(false);
			if (getSavedVar<bool>("hide_attempts_practice") && m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
        PlayLayer::update(dt);
    }
};