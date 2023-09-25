#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
	virtual void update(float dt) {
		if (m_isDart && getVar<bool>("no_wt_behind") && !getVar<bool>("always_trail")) {
			m_regularTrail->stopStroke();
		}

		PlayerObject::update(dt);
	}
};