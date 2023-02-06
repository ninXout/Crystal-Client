#include "hackpro.hpp"

class $modify(PlayerObject) {
	void playDeathEffect() {
		if (!playerBools[10]) {
			PlayerObject::playDeathEffect();
		}
		if (playerBools[21]) {
			PlayLayer::get()->resetLevel();
		}
		if (playerBools[17]) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
		}
	}
	void addAllParticles() {
		if (!playerBools[11]) {
			PlayerObject::addAllParticles();
		}
	}
	void update(float spe) {		
		if (m_waveTrail && playerBools[28]) {
			//m_waveTrail->setBlendFunc(getBlendFunc()); // removes the blending of it
		}
		if (playerBools[32]) {
			PlayerObject::setVisible(false);
		}
		if (moon) {
			m_gravity = 20;
		}
		PlayerObject::update(spe);
	}
	void ringJump(GameObject* ring) {
		bool a;
		bool b;
		a = ring->m_hasBeenActivated;
    	b = ring->m_hasBeenActivatedP2;
		PlayerObject::ringJump(ring);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && playerBools[26]) {
        	if (ring->m_hasBeenActivated && !a) g_activated_objects.push_back(ring);
        	if (ring->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(ring);
    	}
	}
	void saveToCheckpoint(PlayerCheckpoint* g) {
		PlayerObject::saveToCheckpoint(g);
		if (playerBools[27]) {
			g->retain();
		//g_startPoses.push_back({reinterpret_cast<CheckpointObject*>(g), g->getPosition()});
		g_checkpointsPos.push_back(g->getPosition());
        g_checkpointsIG.push_back(g);
		g_checkpointIndex += 1;
		auto label = std::to_string(g_checkpointIndex + 1) + "/" + std::to_string(g_checkpointsIG.size());
		g_checkpointText->setString(label.c_str());
		}
	}
	void playerDestroyed(bool idk) {
		PlayerObject::playerDestroyed(idk);
		s_drawOnDeath = true;
	}
	virtual void setRotation(float love) {
		if (noRot) {
			love = 0.0;
		}

		return PlayerObject::setRotation(love);
	}
};