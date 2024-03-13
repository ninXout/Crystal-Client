#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(NAPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(9, "100.00%");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(9);
        Display::addDisplayChildren(9, this);

        this->schedule(schedule_selector(NAPlayLayer::updateAccuracy));
        return true;
    }

    void updateAccuracy(float dt) {
        char accString[20];
        float accuracy = ((float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames")) * 100;

        if (getTempVar<bool>("would_die") && getSavedVar<bool>("red_on_accuracy")) Display::getDisplay(9)->setColor(ccc3(255, 0, 0));
        else Display::getDisplay(9)->setColor(ccc3(255, 255, 255));

        std::string format = "%." + std::to_string(getSavedVar<int>("noclip_acc_decimals")) + "f%%";

        sprintf(accString, format.c_str(), accuracy);
        if (getSavedVar<bool>("noclip_accuracy")) Display::getDisplay(9)->setString(accString);
    }
};