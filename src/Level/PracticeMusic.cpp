#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void startMusic() {
		if (getVar<bool>("practice_music")) {
			auto p = m_isPracticeMode;
			m_isPracticeMode = false; // pretend there is no practice mode
			PlayLayer::startMusic();
			m_isPracticeMode = p;
		} else {
			PlayLayer::startMusic();
		}
	}

    void togglePracticeMode(bool p) {
		if (!m_isPracticeMode && p && getVar<bool>("practice_music")) {
			m_isPracticeMode = p;
			m_UILayer->toggleCheckpointsMenu(p);
			PlayLayer::startMusic();
			this->stopActionByTag(18);
		} else {
			PlayLayer::togglePracticeMode(p);
		}
	} 
};

class $modify(PlayerObject) {
    void playerDestroyed(bool idk) {
		PlayerObject::playerDestroyed(idk);
		if (getVar<bool>("practice_music")) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
		}
	}
};