#include "../CrystalProfile.hpp"
#include "Display.hpp"

bool isCheating() {
    return (getVar<bool>("noclip") || getVar<float>("speed") != 1 && getVar<bool>("speedhack") || getVar<bool>("no_mirror") || getVar<bool>("framestep") || 
            getVar<bool>("autoclicker") || getVar<bool>("layout_mode") || getVar<bool>("AT_record") || getVar<bool>("AT_replay") || getVar<float>("FPS") > 360.0 ||
            getVar<bool>("jump_hack"));
}

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(0, ".");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(0);
        Display::get()->addDisplayChildren(0, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        if (getVar<bool>("cheat_indicator")) Display::get()->getDisplay(0)->setColor(isCheating() ? ccc3(255, 0, 0) : ccc3(0, 255, 0));
    }
};