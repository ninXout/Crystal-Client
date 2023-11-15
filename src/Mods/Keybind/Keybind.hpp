#pragma once

#include "../../CrystalClient/CrystalClient.hpp"

namespace Keybinds {
    std::string keyToString(cocos2d::enumKeyCodes);
    void pushKeybind();

    inline int currentMod = 0;

    inline const char* modbindings[5] = { "Noclip", "Restart Level", "Speedhack", "Hitbox Viewer", "Player 1"};
    inline const char* modvars[5] = { "noclip", "RESTART_LEVEL", "speedhack", "hitboxes", "PLAYER_1"};

    inline bool waitingForKeybind = false;
    inline cocos2d::enumKeyCodes currentKey = KEY_A;
    inline std::vector<std::pair<cocos2d::enumKeyCodes, int>> keybind;
}