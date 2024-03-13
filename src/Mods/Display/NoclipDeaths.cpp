#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(NDPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(10, "0 Deaths");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(10);
        Display::addDisplayChildren(10, this);

        this->schedule(schedule_selector(NDPlayLayer::updateDeaths));
        return true;
    }

    void updateDeaths(float dt) {
        if (getTempVar<bool>("would_die") && getSavedVar<bool>("red_on_death")) Display::getDisplay(10)->setColor(ccc3(255, 0, 0));
        else Display::getDisplay(10)->setColor(ccc3(255, 255, 255));

        std::string noclipDeaths = std::to_string(getTempVar<int>("noclip_deaths")) + " Deaths";
        if (getSavedVar<bool>("noclip_deaths")) Display::getDisplay(10)->setString(noclipDeaths.c_str());
    }
};