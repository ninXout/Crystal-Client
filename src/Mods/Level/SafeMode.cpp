#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"
#include "../../Utilities/utilities.hpp"

using namespace CrystalClient;

class $modify(GJGameLevel) {
    void savePercentage(int p0, bool p1, int p2, int p3, bool p4) {
        if (getSavedVar<bool>("safe_mode")) {
            if (getSavedVar<bool>("auto_safe_mode") && !shouldNotSave()) GJGameLevel::savePercentage(p0,p1,p2,p3,p4);
        } else GJGameLevel::savePercentage(p0,p1,p2,p3,p4);
    }
};

class $modify(PlayLayer) {
    void showNewBest(bool p0, int p1, int p2, bool p3, bool p4, bool p5) {
        if (getSavedVar<bool>("safe_mode")) {
            if (getSavedVar<bool>("auto_safe_mode") && !shouldNotSave()) PlayLayer::showNewBest(p0,p1,p2,p3,p4,p5);
        } else PlayLayer::showNewBest(p0,p1,p2,p3,p4,p5);
    }

    void levelComplete() {
        if (getSavedVar<bool>("safe_mode")) {
            if (getSavedVar<bool>("auto_safe_mode")) shouldNotSave() ? PlayLayer::onQuit() : PlayLayer::levelComplete();
            else if (!getSavedVar<bool>("auto_safe_mode")) PlayLayer::onQuit();
        } else PlayLayer::levelComplete();
    }
};