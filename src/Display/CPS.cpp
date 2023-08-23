#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Display.hpp"

int clicks = 0;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(2, "0/0");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(2);
        Display::get()->addDisplayChildren(2, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(2);
        
        int cps = 0;
        if (m_time > 0 && clicks > 0) cps = clicks / m_time;
        std::string cpsDisplay = std::to_string(cps) + "/" + std::to_string(clicks);

        if (getVar<bool>("cps_display")) Display::get()->getDisplay(2)->setString(cpsDisplay.c_str());
    }
};

class $modify(GJBaseGameLayer) {
    void pushButton(int i, bool b) {
        GJBaseGameLayer::pushButton(i, b);

        clicks++;
    }
};