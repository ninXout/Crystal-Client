#include "Display.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "../../Utilities/utilities.hpp"

class $modify(CIPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(0, ".");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(0);
        Display::addDisplayChildren(0, this);

        this->schedule(schedule_selector(CIPlayLayer::updateCheatIndicator));
        return true;
    }

    void updateCheatIndicator(float dt) {
        if (getSavedVar<bool>("cheat_indicator")) Display::getDisplay(0)->setColor(shouldNotSave() ? ccc3(255, 0, 0) : ccc3(0, 255, 0));
    }
};