#include <Geode/modify/PlayLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(PlayLayer) {
    bool init(GJGameLevel *gj, bool p1, bool p2) {
        if (!PlayLayer::init(gj, p1, p2)) return false;

        if (getSavedVar<bool>("instant_complete")) PlayLayer::playEndAnimationToPos({2,2});

        return true;
    }
};