#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
    void update(float spe) {
        PlayerObject::setVisible(!getVar<bool>("invis_player"));
		PlayerObject::update(spe);
	}
};