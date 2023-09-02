#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "Display.hpp"
#include <mach/mach_time.h>

int clicks = 0;
int cpsclicks = 0;
std::vector<float> clicksArr;

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
        
        if (clicksArr.size() > 0) {
			float currentTime = mach_absolute_time();
			for (int i = 0; i < clicksArr.size(); i++) {
				if ((currentTime - clicksArr[i]) / 1000.0f >= 1) clicksArr.erase(clicksArr.begin() + i);
			}
		}
        std::string cpsDisplay = std::to_string(clicksArr.size()) + "/" + std::to_string(clicks);

        if (getVar<bool>("cps_display")) Display::get()->getDisplay(2)->setString(cpsDisplay.c_str());
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        
        clicks = 0;
        clicksArr.clear();
    }
};

class $modify(GJBaseGameLayer) {
    void pushButton(int i, bool b) {
        GJBaseGameLayer::pushButton(i, b);

        clicks++;
        clicksArr.push_back(mach_absolute_time());
    }
};