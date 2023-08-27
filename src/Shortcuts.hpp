#pragma once

#include "Includes.hpp"

using namespace geode::prelude;

struct VarChange {
    int activeVar;
    float activeValue;
};

struct Keybind {
    int activeKey;
    int activeMod;
};

class Shortcuts {
    public:
        static Shortcuts* get();

        void pushKeybind(Keybind);
        void pushVariable(VarChange);

        void updateVariables();
        void updateKeybinds(enumKeyCodes key, bool down, bool global);

        void executeBinds(int current, bool down, bool global);
        void refreshKeybinds(bool save);
        
        std::vector<Keybind> keybinds = {{39,6}, {40,7}};
        std::vector<VarChange> variables;

        int currentKey = 0;
        int currentMod = 0;

        const char* keybindings[48] = { "Space Bar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "Backspace", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape" };
        const char* modbindings[14] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint", "Toggle Crystal Menu", "Framestep" };

        int currentVar = 0;
        float currentValue = 0;

        const char* playerVars[7] = { "Gravity", "X Acceleration", "Y Acceleration", "X Position", "Y Position", "Jump Acceleration", "Vehicle Size" };
};

/*
namespace Shortcuts {
    struct Keybind {
        int activeKey;
        int activeMod;
    };
};

using namespace Shortcuts;

static inline const char* keybindings[48] = { "Space Bar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "Backspace", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape" };
static inline const char* modbindings[14] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint", "Toggle Crystal Menu", "Framestep" };
static inline std::vector<Keybind> keybinds = {{39,6}, {40,7}};
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
*/    