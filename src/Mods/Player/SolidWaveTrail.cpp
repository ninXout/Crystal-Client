#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace CrystalClient;

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (getSavedVar<bool>("solid_wave")) m_isSolid = true;
		HardStreak::updateStroke(f);
	}
};

class $modify(PlayerObject) {
    void update(float spe) {		
		if (m_waveTrail && getSavedVar<bool>("solid_wave")) {
			m_waveTrail->setBlendFunc(getBlendFunc());
		}
		PlayerObject::update(spe);
	}
};