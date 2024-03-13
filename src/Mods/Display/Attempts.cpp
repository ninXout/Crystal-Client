#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

int tempAttempt = 1;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(5, "Attempt 1");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(5);
        Display::addDisplayChildren(5, this);

        tempAttempt = 1;
        return true;
    }

    void resetLevel() {
        tempAttempt++;

        PlayLayer::resetLevel();

        int attempt;

        if (getSavedVar<bool>("total_attempts")) attempt = m_level->m_attempts;
        else attempt = tempAttempt;

        std::string attempts = "Attempt " + std::to_string(attempt);
        if (getSavedVar<bool>("attempts")) Display::getDisplay(5)->setString(attempts.c_str());
    }
};