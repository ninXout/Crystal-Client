#pragma once

#include <Geode/Geode.hpp>
#include <imgui.h>
#include "../Utilities/json.hpp"

using namespace geode::prelude;

// TODO: this saving system kind of sucks, fix it

namespace CrystalClient {
    inline std::map<std::string, bool> modsMapB = {
        {"noclip_P1", true},
        {"noclip_P2", true},
        {"AC_player1", true},
        {"AC_player2", true}
    };
    inline std::map<std::string, int> modsMapI = {
        {"AC_pushFrame", 1},
        {"AC_releaseFrame", 1},
        {"acc_percentage_decimals", 2},
        {"noclip_acc_decimals", 2},
    };
    inline std::map<std::string, float> modsMapF = {
        {"wave_size", 2.1},
        {"opacity_wave_trail", 255},
        {"FPS", 60.0},
        {"TPS", 60.0},
        {"FPS_unfocused", 15.0},
        {"display_scale", 1.0},
        {"display_opacity", 200.0},
        {"display_space", 20.0},
        {"speed", 1.0},
        {"BGcolor-red", 0.113725f},
        {"BGcolor-green", 0.113725f},
        {"BGcolor-blue", 0.188235f},
        {"BGcolor-alpha", 1.0f},
        {"lightColor-red", 0.262715f},
        {"lightColor-green", 0.624691f},
        {"lightColor-blue", 0.818605f},
        {"lightColor-alpha", 1.0f},
        {"clickbot_volume", 100.0f},
        {"noclipColor-red", 1.0f},
        {"noclipColor-green", 0.0f},
        {"noclipColor-blue", 0.0f},
        {"noclipColor-alpha", 1.0f},
    };
    inline std::map<std::string, std::string> modsMapS = {};
    inline std::map<int, int> modsMapKEY = {};

    inline std::map<std::string, bool> TEMPmodsMapB = {};
    inline std::map<std::string, int> TEMPmodsMapI = {};
    inline std::map<std::string, float> TEMPmodsMapF = {
        {"target_DT", 0.01666666666f}
    };

    void saveConfig();
    void loadConfig();

    template <typename T>
    T getSavedVar(std::string const& key);

    template <typename T>
    T* setSavedVar(std::string const& key);

    template <typename T>
    T getTempVar(std::string const& key);

    template <typename T>
    T* setTempVar(std::string const& key);

    ImVec4 VarToIV4(std::string key);
    ccColor3B VarToCC3B(std::string key);
    ccColor4B VarToCC4B(std::string key);
}