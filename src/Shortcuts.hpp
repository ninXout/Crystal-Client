#pragma once

#include "Includes.hpp"

namespace Shortcuts {
    struct Keybind {
        int activeKey;
        int activeMod;
    };
};

static inline const char* keybindings[48] = { "Space Bar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "Backspace", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape" };
static inline const char* modbindings[13] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint", "Toggle Crystal Menu" };
static inline std::vector<Shortcuts::Keybind> keybinds;
static inline int currentKey = 0;
static inline int currentMod = 0;

namespace Variables {
    struct VarChange {
        int activeVar;
        float activeValue;
    };
};

static inline const char* playerVars[7] = { "Gravity", "X Acceleration", "Y Acceleration", "X Position", "Y Position", "Jump Acceleration", "Vehicle Size" };
    static inline std::vector<Variables::VarChange> variables;
    static inline int currentVar = 0;
    static inline float currentValue = 0;