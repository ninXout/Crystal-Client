#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"
#include "../../Utilities/utilities.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(4, "Last Death: 0%");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(4);
        Display::addDisplayChildren(4, this);
        return true;
    }

    void resetLevel() {
        double deathPercent = getPercentage();

        PlayLayer::resetLevel();

        std::string lastDeath = std::string("Last Death: ") + std::to_string((int)deathPercent) + "%";
        if (getSavedVar<bool>("last_death")) Display::getDisplay(4)->setString(lastDeath.c_str());
    }
};