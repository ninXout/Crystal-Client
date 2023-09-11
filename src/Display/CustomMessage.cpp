#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(1, "N/A");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(1);
        Display::get()->addDisplayChildren(1, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        if (getVar<bool>("custom_message")) Display::get()->getDisplay(1)->setString(getVar<std::string>("message").c_str());
    }
};