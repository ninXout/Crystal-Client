#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(5, "Attempt 1");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(5);
        Display::get()->addDisplayChildren(5, this);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int attempt;

        if (getVar<bool>("total_attempts")) attempt = m_level->m_attempts;
        else attempt = m_currentAttempt;

        std::string attempts = "Attempt " + std::to_string(attempt);
        if (getVar<bool>("attempts")) Display::get()->getDisplay(5)->setString(attempts.c_str());
    }
};