#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(7, "From 0%");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(7);
        Display::get()->addDisplayChildren(7, this);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int from = getPercentage();

        std::string runFrom = "From " + std::to_string(from) + "%";
        if (getVar<bool>("run_from")) Display::get()->getDisplay(7)->setString(runFrom.c_str());
    }
};