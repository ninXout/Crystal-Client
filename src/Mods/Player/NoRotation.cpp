#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayerObject.hpp>

using namespace CrystalClient;

class $modify(PlayerObject) {
    virtual void setRotation(float degrees) {
        if (getSavedVar<bool>("no_rotation")) {
            degrees = 0.0;
        }

        PlayerObject::setRotation(degrees);
	}
};