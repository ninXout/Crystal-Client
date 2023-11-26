#pragma once

#include "../Mods/Display/Display.hpp"

using namespace CrystalClient;

inline double getPercentage() {
    if (!PlayLayer::get()) return 0;

    double ret = ((PlayLayer::get()->m_player1->getPositionX()) / PlayLayer::get()->m_levelLength) * 100;
    if (ret < 0) ret = 0;
    if (ret > 100) ret = 100;

    return ret;
}

inline bool shouldNotSave() {
    return ((getSavedVar<bool>("safe_mode") && !getSavedVar<bool>("auto_safe_mode")) || (getSavedVar<bool>("safe_mode") && getSavedVar<bool>("auto_safe_mode") && Display::getDisplay(0)->getColor() == ccc3(255,0,0)));
}