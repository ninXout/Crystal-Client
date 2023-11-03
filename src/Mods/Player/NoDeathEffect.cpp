#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayerObject.hpp>

using namespace CrystalClient;

class $modify(PlayerObject) {
	void playDeathEffect() {
		if (!getSavedVar<bool>("no_death_effect")) {
			PlayerObject::playDeathEffect();
		}
	}
};