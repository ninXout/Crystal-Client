#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(5, "Attempt 1");

        if (!PlayLayer::init(gj)) return false;

        Display::updateDisplay(5);
        Display::addDisplayChildren(5, this);
        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int attempt;

        if (getSavedVar<bool>("total_attempts")) attempt = m_level->m_attempts;
        else attempt = m_currentAttempt;

        std::string attempts = "Attempt " + std::to_string(attempt);
        if (getSavedVar<bool>("attempts")) Display::getDisplay(5)->setString(attempts.c_str());
    }
};