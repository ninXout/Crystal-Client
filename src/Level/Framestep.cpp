#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool shouldUpdate = false;

class $modify(PlayLayer) {
    void update(float dt) {
        if (!getVar<bool>("framestep") || (getVar<bool>("framestep") && shouldUpdate)) PlayLayer::update(dt);
    }
};