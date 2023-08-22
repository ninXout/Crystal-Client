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

inline std::map<std::string, bool> modsMapB = {};
inline std::map<std::string, int> modsMapI = {};
inline std::map<std::string, float> modsMapF = {};

inline std::map<std::string, bool> TEMPmodsMapB = {};
inline std::map<std::string, int> TEMPmodsMapI = {};
inline std::map<std::string, float> TEMPmodsMapF = {};

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
    std::ofstream file((Mod::get()->getConfigDir() / "Config" / "GH_config-01.json").string().c_str());
    file << JSONobj01;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-02.json").string().c_str());
    file << JSONobj02;
    file.close();
    file.open((Mod::get()->getConfigDir() / "Config" / "GH_config-03.json").string().c_str());
    file << JSONobj03;
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
}

// should move to a utils file

inline double getPercentage() {
    if (!PlayLayer::get()) return 0;

    return ((PlayLayer::get()->m_player1->getPositionX() - 50) / PlayLayer::get()->m_levelLength) * 100;
}

// Legacy shit just incase

struct CrystalProfile {
    bool noclip = false;
    bool noclipP1 = true;
    bool noclipP2 = true;
    bool tintOnDeath = true;
    bool resetOnAccuracy = false;
    bool resetOnDeath = false;
    float resetAcc = 0;
    int resetDeath = 0;
    bool deathEffect = false;
    bool instantdeath = false;
    bool autoreset = false;
    float autoresetnum = 0;
    bool hitboxMultiply = false;
    float multiplySolids = 1;
    float multiplyHazards = 1;
    float multiplySpecial = 1;
    bool respawnfix = false;
    bool practiceorbfix = false;
    bool nopulse = false;
    float trailsize = 0;
    bool solidwave = false;
    bool invisibleplayer = false;

    bool customPlayerColor = false;
    bool customWaveColor = false;
    bool rainbowIcon = false;
    bool rainbowP1 = false;
    bool rainbowP2 = false;
    bool rainbowP1wave = false;
    bool rainbowP2wave = false;
    float rainbowspeed = 0;
    bool rainbowGlowP1 = false;
    bool rainbowGlowP2 = false;
    bool samedual = false;
    bool solidGlow = false;


    bool P1Color1 = false;
    bool P1Color2 = false;
    bool P1Glow = false;
    bool P1Regular = false;
    bool P1Wave = false;

    bool P2Color1 = false;
    bool P2Color2 = false;
    bool P2Glow = false;
    bool P2Regular = false;
    bool P2Wave = false;


    std::array<bool, 30> iconEffects;

    // the rest of the colors get stupid so heres some notation

    /*
    
        P = player
        C = color
        G = glow
        W = wave trail
        R = regular trail
        E = effect color

        For example: FadeP1C1E2 == Fade Color 1 for Player 1 Second Player Color

    */

    float StaticP1C1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP1C2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP2C1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP2C2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float StaticP1CG[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP2CG[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float StaticP1CW[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP2CW[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float StaticP1CR[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float StaticP2CR[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    // fade

    float FadeP1C1E1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1C1E2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1C2E1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1C2E2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float FadeP2C1E1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2C1E2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2C2E1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2C2E2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float FadeP1GE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1GE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2GE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2GE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float FadeP1WE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1WE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2WE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2WE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    float FadeP1RE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP1RE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2RE1[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float FadeP2RE2[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

    bool hitboxes = false;
    bool onDeath = false;
    bool drawTrail = false;
    bool inEditor = false;
    bool fillHitbox = false;
    float fillOpacity = 150;
    bool coinFind = false;
    bool trajectory = false;
    bool particles = false;
    bool progressBar = false;
    bool accpercentage = false;
    bool hideatts = false;
    bool hidenormalatts = false;
    bool hidepracticeatts = false;
    bool pracmusic = false;
    bool ignoreESC = false;
    bool confirmQuit = false;
    bool autoldm = false;
    bool autoSong = false;
    bool flippedcontrol = false;
    bool mirrorcontrol = false;
    bool startpos = false;
    bool checkpointswitch = false;
    bool framestep = false;
    bool lastCheckpoint = false;
    bool noglow = false;
    bool nospike = false;
    bool mirror = false;
    bool layout = false;
    bool autoclick = false;
    int ACpushframe = 1;
    int ACrelframe = 1;
    bool hidepause = false;

    bool anticheat = false;
    bool unlockAll = false;
    bool scalehack = false;
    bool objlimit = false;
    bool customobjlimit = false;
    bool verify = false;
    bool copy = false;
    bool editorZoom = false;
    bool levelEdit = false;
    bool loadfail = false;
    
    bool testmode = true;
    std::string message;
    char messageBuffer[64];
    bool customMessage = false; // all this shit has to be here even if they arent used for some fucking reason
    bool fps = false;
    bool cps = false;
    bool jumps = false;
    bool cheatIndicate = false;
    bool attempts = false;
    bool bestRun = false;
    bool runFrom = false;
    bool noclipAcc = false;
    bool noclipDeath = false;
    bool totalAtt = false;
    bool lvlData = false;
    bool macroStatus = false; // because without them json crashes (?????)
    bool tclicks = false;
    bool sclicks = false;
    bool oclicks = false;
    bool rclicks = false;
    bool tjumps = false;
    bool ajumps = false;
    bool tattoo = false;
    bool redDying = false;
    bool redDeath = false;
    bool hideID = false;
    bool author = false;
    bool clock = false;
    bool ipm = false;
    bool iat = false;
    bool ilt = false;
    bool igt = false;

    std::array<bool, 15> displays;
    std::array<LabelPos, 15> displayPositions;
    CCLabelBMFont* displayNodes[15];
    const char* displayOptions[4] = {"Top Right", "Top Left", "Bottom Right", "Bottom Left"};
    float displaySpaceF = 15.0f;
    float displayScaleF = 7.5f;
    float displayOpacityF = 20.0f;
    std::array<float, 15> displayScale;
    std::array<float, 15> displayOpacity;

    /*
    customMessage
    fps
    cps
    jumps
    cheatIndicate
    lastDeath
    attempts
    bestRun
    runFrom
    noclipAcc
    noclipDeath
    totalAtt
    lvlData
    macroStatus
    clock
    */

    bool safeMode = false;
    bool autoSafeMode = false;
    bool noTransition = false;
    bool lockCursor = false;
    bool transparentBG = false;
    bool translists = false;
    bool buttonDL = false;
    bool buttonCL = false;
    bool betterbg = false;
    bool speedhack = false;
    float speed = 1.0;
    bool FPSbypass = false;
    float FPS = 60;
    bool TPSbypass = false;
    float TPS = 60;

    bool record = false;
    bool replay = false;
    bool deltaLock = false;
    bool clickBot = false;
    float CBvolume = 100;
    char macroname[64];
    bool macroBuffer = false;
    std::vector<cocos2d::CCRect> regularPath;
    std::vector<cocos2d::CCRect> clicksPath;
    std::vector<cocos2d::CCRect> releasesPath;

    float rDir = -0.05;
    float gDir = 0.05;
    float bDir = -0.05;

    float BGColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float LightColour[4] = { 0.262715f,
                            0.624691f,
                            0.818605f,
                            1.0f };
    float TitleColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float DarkColour[4];
    float VeryLightColour[4];

    float borderRounding = 0;
    float scrollbarSize = 12;
    float scrollbarRounding = 12;

    bool RGBAccent = false;
    bool borders = false;
    bool rounded = false;
    bool titlebar = false;
    bool invisBG = false;
    bool diffTitleBar = false;

    bool renderer = false;
    bool includeAudio = true;
    bool includeDisplays = false;
    char rendername[64];

    int bitrate = 50000; //K
    int audioBitrate = 192; //K
    std::string codec = "h264";

    int ss = 0;

    int targetWidth = 3840;
    int targetHeight = 2160;
    int targetFPS = 60;

    static ImVec4 RGBAtoIV4(float rgb[4]) {
        float newr = rgb[0];
        float newg = rgb[1];
        float newb = rgb[2];
        float newa = rgb[3];
        return ImVec4(newr, newg, newb, newa);
    }
};

namespace Crystal {
    static inline CrystalProfile profile;
    void saveMods(CrystalProfile const& data);
    CrystalProfile loadMods();
}