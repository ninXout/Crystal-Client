#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayerObject.hpp>

using namespace CrystalClient;

class $modify(PlayerObject) {
    void update(float spe) {
        PlayerObject::setVisible(!getSavedVar<bool>("invis_player"));
		PlayerObject::update(spe);
	}
};