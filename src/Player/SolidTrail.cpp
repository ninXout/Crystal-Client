#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
    void update(float spe) {		
		if (m_regularTrail && getVar<bool>("solid_trail")) {
			m_regularTrail->setBlendFunc(getBlendFunc());
		}

		PlayerObject::update(spe);
	}
};