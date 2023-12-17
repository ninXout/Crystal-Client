#include "Icon.hpp"

using namespace Icon;

cocos2d::ccColor3B Icon::getEffectColor(bool player2, Type tp, Effect eft) {
    float red, green, blue = 0.f;

    if (eft == RAINBOW) {
        red = red + rDir;
        green = green + gDir;
        blue = blue + bDir;

        if (red >= 255 || red <= 0) { rDir = rDir * -1; }
        if (green >= 255 || green <= 0) { gDir = gDir * -1; }
        if (blue >= 255 || blue <= 0) { bDir = bDir * -1; }
    } else if (eft == FADE) {
        
    }



    return ccc3(red, green, blue);
}