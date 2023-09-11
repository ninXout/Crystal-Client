#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayerObject.hpp>

class $modify(PlayerObject) {
    virtual void setRotation(float degrees) {
        if (getVar<bool>("no_rotation")) {
            degrees = 0.0;
        }

        PlayerObject::setRotation(degrees);
	}
};