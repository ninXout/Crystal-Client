#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Display.hpp"

std::chrono::time_point<std::chrono::high_resolution_clock> previousFrame, lastUpdate;
float timeSum = 0.f;
int clicksCount = 0;

class $modify(CPSPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(2, "0/0");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(2);
        Display::addDisplayChildren(2, this);

        this->schedule(schedule_selector(CPSPlayLayer::updateCPS));
        return true;
    }

    void updateCPS(float dt) {
        const auto now = std::chrono::high_resolution_clock::now();

		const std::chrono::duration<float> diff = now - previousFrame;
		timeSum += diff.count();

        if (std::chrono::duration<float>(now - lastUpdate).count() > 1.0f) {
            lastUpdate = now;
            const auto cps = static_cast<int>(std::roundf(static_cast<float>(clicksCount) / timeSum));
            timeSum = 0.f;
            clicksCount = 0;
            if (getSavedVar<bool>("cps_display")) Display::getDisplay(2)->setString(std::to_string(cps).c_str());
        }

		previousFrame = now;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        
        clicksCount = 0;
    }
};

class $modify(GJBaseGameLayer) {
    void handleButton(bool a, int i, bool b) {
        GJBaseGameLayer::handleButton(a, i, b);

        clicksCount++;
    }
};