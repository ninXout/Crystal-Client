#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(9, "100.00%");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(9);
        Display::get()->addDisplayChildren(9, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(9);

        char accString[20];
        float accuracy = ((float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames")) * 100;

        if (getTempVar<bool>("would_die") && getVar<bool>("red_on_accuracy")) Display::get()->getDisplay(9)->setColor(ccc3(255, 0, 0));
        else Display::get()->getDisplay(9)->setColor(ccc3(255, 255, 255));

        sprintf(accString, "%.2f%%", accuracy);
        if (getVar<bool>("noclip_accuracy")) Display::get()->getDisplay(9)->setString(accString);
    }
};