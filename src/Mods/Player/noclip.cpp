#include <Geode/modify/PlayLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* p, GameObject* g) {
        if (!getSavedVar<bool>("noclip")) PlayLayer::destroyPlayer(p, g);
    }
};