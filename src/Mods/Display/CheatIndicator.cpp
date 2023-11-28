#include "Display.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "../../Utilities/utilities.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(0, ".");

        if (!PlayLayer::init(gj)) return false;

        Display::updateDisplay(0);
        Display::addDisplayChildren(0, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        if (getSavedVar<bool>("cheat_indicator")) Display::getDisplay(0)->setColor(shouldNotSave() ? ccc3(255, 0, 0) : ccc3(0, 255, 0));
    }
};