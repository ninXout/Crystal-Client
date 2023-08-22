#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(13, "00:00:00");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(13);
        Display::get()->addDisplayChildren(13, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(13);

        auto t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        auto clstr = oss.str();

        if (getVar<bool>("clock")) Display::get()->getDisplay(13)->setString(clstr.c_str());
    }
};