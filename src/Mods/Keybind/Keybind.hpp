#pragma once

#include "../../CrystalClient/CrystalClient.hpp"

namespace Keybinds {
    std::string keyToString(cocos2d::enumKeyCodes);
    void pushKeybind();

    inline int currentMod = 0;

    inline const char* modbindings[7] = { "Noclip", "Restart Level", "Speedhack", "Hitbox Viewer", "Player 1", "Switcher Left", "Switcher Right"};
    inline const char* modvars[7] = { "noclip", "RESTART_LEVEL", "speedhack", "hitboxes", "PLAYER_1", "SWITCH_LEFT", "SWITCH_RIGHT"};

    inline bool waitingForKeybind = false;
    inline cocos2d::enumKeyCodes currentKey = KEY_A;
    inline std::vector<std::pair<cocos2d::enumKeyCodes, int>> keybind;
}