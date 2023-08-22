#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(6, "0 Jumps");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(6);
        Display::get()->addDisplayChildren(6, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(6);

        int jump;

        if (getVar<bool>("total_jumps")) jump = m_level->m_jumps;
        else jump = m_attemptJumpCount;

        std::string jumps = std::to_string(jump) + " Jumps";
        if (getVar<bool>("jumps")) Display::get()->getDisplay(6)->setString(jumps.c_str());
    }
};