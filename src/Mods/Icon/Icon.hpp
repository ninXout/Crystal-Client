#pragma once

#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

namespace Icon {
    enum Effect {
        NONE,
        STATIC,
        FADE,
        RAINBOW
    };

    enum Type {
        PLAYER1,
        PLAYER2,
        WAVE,
        REGULAR,
        GLOW
    };

    cocos2d::ccColor3B getEffectColor(bool player2, Type tp, Effect eft);

    inline float rDir = -1;
    inline float gDir = 1;
    inline float bDir = -1;
}