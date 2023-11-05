#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

int clickframe;

class $modify(PlayLayer) {
    void checkCollisions(PlayerObject* p, float idk) {
        if (getSavedVar<bool>("autoclicker")) {
            clickframe++;
            if (clickframe == getSavedVar<int>("AC_pushFrame")) {
                if (getSavedVar<bool>("AC_player1")) GJBaseGameLayer::get()->pushButton(1, true);
                if (getSavedVar<bool>("AC_player2")) GJBaseGameLayer::get()->pushButton(1, false);
            }
            if (clickframe >= (getSavedVar<int>("AC_pushFrame") + getSavedVar<int>("AC_releaseFrame"))) {
                if (getSavedVar<bool>("AC_player1")) GJBaseGameLayer::get()->releaseButton(1, true);
                if (getSavedVar<bool>("AC_player2")) GJBaseGameLayer::get()->releaseButton(1, false);
                clickframe = 0;
            }
        }
        PlayLayer::checkCollisions(p, idk);
    }
};