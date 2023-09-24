#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "json.hpp"
#include "./Amethyst/Amethyst.hpp"
#include "../include/Plugin.hpp"
#include <imgui.h>
#include "./Icon/Icon.hpp"

using json2 = nlohmann::json;
using namespace geode::prelude;

enum LabelPos
{
	TR,
	TL,
	BR,
	BL
};

inline std::map<std::string, bool> modsMapB = {
    {"noclip_P1", true},
    {"noclip_P2", true}
};
inline std::map<std::string, int> modsMapI = {
    {"AC_pushFrame", 1},
    {"AC_releaseFrame", 1},
    {"acc_percentage_decimals", 2}
};
inline std::map<std::string, float> modsMapF = {
    {"wave_size", 2.1},
    {"opacity_wave_trail", 255},
    {"FPS", 60.0},
    {"FPS_unfocused", 15.0},
    {"display_scale", 1.0},
    {"display_opacity", 200.0},
    {"display_space", 20.0},
    {"speed", 1.0},
    {"BGcolor-red", 0.12f},
    {"BGcolor-blue", 0.12f},
    {"BGcolor-green", 0.12f},
    {"BGcolor-alpha", 1.0f},
    {"lightColor-red", 0.262715f},
    {"lightColor-blue", 0.624691f},
    {"lightColor-green", 0.818605f},
    {"lightColor-alpha", 1.0f},
    {"clickbot_volume", 100.0f}
};
inline std::map<std::string, std::string> modsMapS = {};

inline std::map<std::string, bool> TEMPmodsMapB = {};
inline std::map<std::string, int> TEMPmodsMapI = {};
inline std::map<std::string, float> TEMPmodsMapF = {
    {"target_DT", 0.01666666666f}
};

template <typename T>
T getVar(std::string const& key);

template <typename T>
T* setVar(std::string const& key);

template <>
inline bool getVar<bool>(std::string const& key) {
	return modsMapB[key];
}
template <>
inline bool* setVar<bool>(std::string const& key) {
	return &modsMapB[key];
}

template <>
inline int getVar<int>(std::string const& key) {
	return modsMapI[key];
}
template <>
inline int* setVar<int>(std::string const& key) {
	return &modsMapI[key];
}

template <>
inline float getVar<float>(std::string const& key) {
	return modsMapF[key];
}
template <>
inline float* setVar<float>(std::string const& key) {
	return &modsMapF[key];
}

template <>
inline std::string getVar<std::string>(std::string const& key) {
	return modsMapS[key];
}
template <>
inline std::string* setVar<std::string>(std::string const& key) {
	return &modsMapS[key];
}

// TEMP SHIT

template <typename T>
T getTempVar(std::string const& key);

template <typename T>
T* setTempVar(std::string const& key);

template <>
inline bool getTempVar<bool>(std::string const& key) {
	return TEMPmodsMapB[key];
}
template <>
inline bool* setTempVar<bool>(std::string const& key) {
	return &TEMPmodsMapB[key];
}

template <>
inline int getTempVar<int>(std::string const& key) {
	return TEMPmodsMapI[key];
}
template <>
inline int* setTempVar<int>(std::string const& key) {
	return &TEMPmodsMapI[key];
}

template <>
inline float getTempVar<float>(std::string const& key) {
	return TEMPmodsMapF[key];
}
template <>
inline float* setTempVar<float>(std::string const& key) {
	return &TEMPmodsMapF[key];
}

inline void saveConfigToFile() {
    auto JSONobj01 = json2::object();
    JSONobj01 = modsMapB;
    auto JSONobj02 = json2::object();
    JSONobj02 = modsMapI;
    auto JSONobj03 = json2::object();
    JSONobj03 = modsMapF;
    auto JSONobj04 = json2::object();
    JSONobj04 = modsMapS;
    std::ofstream file((Mod::get()->getConfigDir() / "Config" / "GH_config-01.json").string().c_str());
    file << JSONobj01;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-02.json").string().c_str());
    file << JSONobj02;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-03.json").string().c_str());
    file << JSONobj03;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-04.json").string().c_str());
    file << JSONobj04;
    file.close();
}

inline void loadConfigFromFile() {
    std::fstream input((Mod::get()->getConfigDir() / "Config" / "GH_config-01.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj1 = json2::parse(input);
        modsMapB = JSONobj1;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-02.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj2 = json2::parse(input);
        modsMapI = JSONobj2;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-03.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj3 = json2::parse(input);
        modsMapF = JSONobj3;
    }
    input.close();
    input.open((Mod::get()->getConfigDir() / "Config" / "GH_config-04.json").string().c_str());
    if (input.is_open()) {
        auto JSONobj4 = json2::parse(input);
        modsMapS = JSONobj4;
    }
    input.close();
}

// should move to a utils file

inline double getPercentage() {
    if (!PlayLayer::get()) return 0;

    double ret = ((PlayLayer::get()->m_player1->getPositionX()) / PlayLayer::get()->m_levelLength) * 100;
    if (ret < 0) ret = 0;
    if (ret > 100) ret = 100;

    return ret;
}

inline ImVec4 VarToIV4(std::string key) {
    float newr = getVar<float>(key + "-red");
    float newg = getVar<float>(key + "-blue");
    float newb = getVar<float>(key + "-green");
    float newa = getVar<float>(key + "-alpha");
    return ImVec4(newr, newg, newb, newa);
}