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
    return (getSavedVar<bool>("noclip") || (getSavedVar<float>("speed") != 1 && getSavedVar<bool>("speedhack")) || getSavedVar<bool>("no_mirror") || getSavedVar<bool>("framestep") || 
            getSavedVar<bool>("autoclicker") || getSavedVar<bool>("layout_mode") || getSavedVar<bool>("AT_record") || getSavedVar<bool>("AT_replay") || getSavedVar<float>("FPS") > 360.0 ||
            getSavedVar<bool>("jump_hack"));
}