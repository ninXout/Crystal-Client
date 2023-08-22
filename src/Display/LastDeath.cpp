#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(4, "Last Death: 0%");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(4);
        Display::get()->addDisplayChildren(4, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(4);
    }

    void resetLevel() {
        double deathPercent = getPercentage();

        PlayLayer::resetLevel();

        std::string lastDeath = std::to_string((int)deathPercent);
        if (getVar<bool>("last_death")) Display::get()->getDisplay(4)->setString(lastDeath.c_str());
    }
};