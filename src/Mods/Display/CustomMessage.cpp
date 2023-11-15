#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(1, "N/A");

        if (!PlayLayer::init(gj)) return false;

        Display::updateDisplay(1);
        Display::addDisplayChildren(1, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        if (getSavedVar<bool>("custom_message")) Display::getDisplay(1)->setString(getSavedVar<std::string>("message").c_str());
    }
};