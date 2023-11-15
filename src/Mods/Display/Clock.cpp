#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(13, "00:00:00");

        if (!PlayLayer::init(gj)) return false;

        Display::updateDisplay(13);
        Display::addDisplayChildren(13, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        auto t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        auto clstr = oss.str();

        if (getSavedVar<bool>("clock")) Display::getDisplay(13)->setString(clstr.c_str());
    }
};