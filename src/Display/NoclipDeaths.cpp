#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(10, "0 Deaths");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(10);
        Display::get()->addDisplayChildren(10, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        if (getTempVar<bool>("would_die") && getVar<bool>("red_on_death")) Display::get()->getDisplay(10)->setColor(ccc3(255, 0, 0));
        else Display::get()->getDisplay(10)->setColor(ccc3(255, 255, 255));

        std::string noclipDeaths = std::to_string(getTempVar<int>("noclip_deaths")) + " Deaths";
        if (getVar<bool>("noclip_deaths")) Display::get()->getDisplay(10)->setString(noclipDeaths.c_str());
    }
};