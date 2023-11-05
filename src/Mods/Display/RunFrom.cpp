#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"
#include "../../Utilities/utilities.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(7, "From 0%");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(7);
        Display::addDisplayChildren(7, this);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int from = getPercentage();

        std::string runFrom = "From " + std::to_string(from) + "%";
        if (getSavedVar<bool>("run_from")) Display::getDisplay(7)->setString(runFrom.c_str());
    }
};