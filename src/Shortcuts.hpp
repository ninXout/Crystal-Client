#pragma once

#include "Includes.hpp"

namespace Shortcuts {
    struct Keybind {
        int activeKey;
        int activeMod;
    };
};

using namespace Shortcuts;

static inline const char* keybindings[48] = { "Space Bar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "Backspace", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape" };
static inline const char* modbindings[13] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint", "Toggle Crystal Menu" };
static inline std::vector<Keybind> keybinds;
static inline int currentKey = 0;
static inline int currentMod = 0;
static inline void saveKeybinds();
static inline void loadKeybinds();

template<>
struct json::Serialize<Keybind> {
    static json::Value to_json() {
        auto ret = json::Object();
        auto array = json::Array();
        for (auto key : keybinds) {
            auto obj = json::Object();
            obj["activeKey"] = key.activeKey;
            obj["activeMod"] = key.activeMod;
            array.push_back(obj);
        }
        ret["keybinds"] = array;
        return ret;
    }
};

void saveKeybinds() {
    /*
    std::fstream jsonOutFile;
	jsonOutFile.open(geode::Mod::get()->getSaveDir().append("GH_shortcuts.json"), std::ios::out);
	jsonOutFile << json::Serialize<Keybind>::to_json().dump();
	jsonOutFile.close();
    */
}

void loadKeybinds() {
    /*
    std::fstream jsonOutFile;
	jsonOutFile.open(geode::Mod::get()->getSaveDir().append("GH_shortcuts.json"));
    keybinds.clear();
    std::stringstream buffer;
    buffer << jsonOutFile.rdbuf();
    jsonOutFile.close();

    auto json = json::parse(std::string_view(buffer.str()));
    auto array = json["keybinds"].as_array();

    for (auto thing : array) {
        keybinds.push_back(thing);
    }
	jsonOutFile.close();
    */
}

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