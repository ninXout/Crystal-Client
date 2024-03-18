#include <Geode/modify/PlayLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(PlayLayer) {
    void delayedResetLevel() {
        if (getSavedVar<bool>("instant_respawn")) return PlayLayer::resetLevel();
        PlayLayer::delayedResetLevel();
    }
};