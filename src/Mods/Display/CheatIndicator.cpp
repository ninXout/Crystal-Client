#include "Display.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool isCheating() {
    return (getSavedVar<bool>("noclip") || getSavedVar<float>("speed") != 1 && getSavedVar<bool>("speedhack") || getSavedVar<bool>("no_mirror") || getSavedVar<bool>("framestep") || 
            getSavedVar<bool>("autoclicker") || getSavedVar<bool>("layout_mode") || getSavedVar<bool>("AT_record") || getSavedVar<bool>("AT_replay") || getSavedVar<float>("FPS") > 360.0 ||
            getSavedVar<bool>("jump_hack"));
}

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(0, ".");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(0);
        Display::addDisplayChildren(0, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        if (getSavedVar<bool>("cheat_indicator")) Display::getDisplay(0)->setColor(isCheating() ? ccc3(255, 0, 0) : ccc3(0, 255, 0));
    }
};