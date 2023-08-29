#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void update(float dt) {
        if (!getVar<bool>("framestep") || (getVar<bool>("framestep") && getTempVar<bool>("should_update"))) PlayLayer::update(dt);
    }
};