#include "../CrystalProfile.hpp"
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/PlayerObject.hpp>

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (getVar<bool>("solid_wave")) m_isSolid = true;
		HardStreak::updateStroke(f);
	}
};

class $modify(PlayerObject) {
    void update(float spe) {		
		if (m_waveTrail && getVar<bool>("solid_wave")) {
			m_waveTrail->setBlendFunc(getBlendFunc());
		}
		PlayerObject::update(spe);
	}
};