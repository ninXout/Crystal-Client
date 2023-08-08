#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
	void playDeathEffect() {
		if (!getVar<bool>("no_death_effect")) {
			PlayerObject::playDeathEffect();
		}
	}
};