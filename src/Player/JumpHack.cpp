#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
	void pushButton(PlayerButton p0) {
		if (getVar<bool>("jump_hack")) {
			PlayerObject::bumpPlayer(0.75f, 1);
		}

		PlayerObject::pushButton(p0);
	}
};