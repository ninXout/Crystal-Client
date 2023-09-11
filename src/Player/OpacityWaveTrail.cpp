#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

GLubyte waveTrailOpacity;

class $modify(PlayerObject) {
    void update(float dt) {		
		if (m_waveTrail) {
			waveTrailOpacity = getVar<float>("opacity_wave_trail");
			m_waveTrail->setOpacity(waveTrailOpacity);
		}

		PlayerObject::update(dt);
	}
};