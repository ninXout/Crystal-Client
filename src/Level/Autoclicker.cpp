#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

int clickframe;

class $modify(PlayLayer) {
    void checkCollisions(PlayerObject* p, float idk) {
        if (getVar<bool>("autoclicker")) {
            clickframe++;
            if (clickframe == getVar<int>("AC_pushFrame")) {
                if (getVar<bool>("AC_player1")) GJBaseGameLayer::get()->pushButton(1, true);
                if (getVar<bool>("AC_player2")) GJBaseGameLayer::get()->pushButton(1, false);
            }
            if (clickframe >= (getVar<int>("AC_pushFrame") + getVar<int>("AC_releaseFrame"))) {
                if (getVar<bool>("AC_player1")) GJBaseGameLayer::get()->releaseButton(1, true);
                if (getVar<bool>("AC_player2")) GJBaseGameLayer::get()->releaseButton(1, false);
                clickframe = 0;
            }
        }
        PlayLayer::checkCollisions(p, idk);
    }
};