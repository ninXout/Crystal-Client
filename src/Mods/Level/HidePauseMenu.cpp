#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace CrystalClient;

PauseLayer* pausemenu;

class $modify(HPMPauseLayer, PauseLayer) {
    static PauseLayer* create(bool b) {
        pausemenu = PauseLayer::create(b);
        pausemenu->schedule(schedule_selector(HPMPauseLayer::updatePauseMenu));
        return pausemenu;
    }

    void updatePauseMenu(float dt) {
        pausemenu->setVisible(!getSavedVar<bool>("hide_pause"));
    }
};