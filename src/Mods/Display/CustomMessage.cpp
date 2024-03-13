#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(CMPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(1, "N/A");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(1);
        Display::addDisplayChildren(1, this);

        this->schedule(schedule_selector(CMPlayLayer::updateMessage));
        return true;
    }

    void updateMessage(float dt) {
        if (getSavedVar<bool>("custom_message")) Display::getDisplay(1)->setString(getSavedVar<std::string>("message").c_str());
    }
};