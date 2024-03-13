#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(CLPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(13, "00:00:00");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(13);
        Display::addDisplayChildren(13, this);

        this->schedule(schedule_selector(CLPlayLayer::updateClock));
        return true;
    }

    void updateClock(float dt) {
        auto t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        auto clstr = oss.str();

        if (getSavedVar<bool>("clock")) Display::getDisplay(13)->setString(clstr.c_str());
    }
};