#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(6, "0 Jumps");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(6);
        Display::addDisplayChildren(6, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        int jump;

        if (getSavedVar<bool>("total_jumps")) jump = m_level->m_jumps;
        else jump = m_attemptJumpCount;

        std::string jumps = std::to_string(jump) + " Jumps";
        if (getSavedVar<bool>("jumps")) Display::getDisplay(6)->setString(jumps.c_str());
    }
};