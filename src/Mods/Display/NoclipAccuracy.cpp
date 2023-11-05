#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(9, "100.00%");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(9);
        Display::addDisplayChildren(9, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        char accString[20];
        float accuracy = ((float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames")) * 100;

        if (getTempVar<bool>("would_die") && getSavedVar<bool>("red_on_accuracy")) Display::getDisplay(9)->setColor(ccc3(255, 0, 0));
        else Display::getDisplay(9)->setColor(ccc3(255, 255, 255));

        std::string format = "%." + std::to_string(getSavedVar<int>("noclip_acc_decimals")) + "f%%";

        sprintf(accString, format.c_str(), accuracy);
        if (getSavedVar<bool>("noclip_accuracy")) Display::getDisplay(9)->setString(accString);
    }
};