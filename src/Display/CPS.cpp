#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Display.hpp"

std::chrono::time_point<std::chrono::high_resolution_clock> previousFrame, lastUpdate;
float timeSum = 0.f;
int clicksCount = 0;

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
        
        const auto now = std::chrono::high_resolution_clock::now();

		const std::chrono::duration<float> diff = now - previousFrame;
		timeSum += diff.count();

        if (std::chrono::duration<float>(now - lastUpdate).count() > 1.0f) {
            lastUpdate = now;
            const auto cps = static_cast<int>(std::roundf(static_cast<float>(clicksCount) / timeSum));
            timeSum = 0.f;
            clicksCount = 0;
            if (getVar<bool>("cps_display")) Display::get()->getDisplay(2)->setString(std::to_string(cps).c_str());
        }

		previousFrame = now;
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        
        clicksCount = 0;
    }
};

class $modify(GJBaseGameLayer) {
    void pushButton(int i, bool b) {
        GJBaseGameLayer::pushButton(i, b);

        clicksCount++;
    }
};