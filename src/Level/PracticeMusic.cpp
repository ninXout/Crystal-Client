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

	void destroyPlayer(PlayerObject* player, GameObject* obj) {
		if (!getVar<bool>("noclip") && m_isPracticeMode && obj != m_antiCheatObject && getVar<bool>("practice_music")) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
		}
		PlayLayer::destroyPlayer(player, obj);
	}

    void togglePracticeMode(bool p) {
		if (!m_isPracticeMode && p && getVar<bool>("practice_music")) {
			m_isPracticeMode = p;
			if (!GameManager::get()->getGameVariable("0071")) m_UILayer->toggleCheckpointsMenu(p);
			PlayLayer::startMusic();
			this->stopActionByTag(18);
		} else {
			PlayLayer::togglePracticeMode(p);
		}
	} 
};