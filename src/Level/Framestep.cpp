#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void onQuit() {
        *setTempVar<bool>("gameStarted") = false;
        PlayLayer::onQuit();
    }
};