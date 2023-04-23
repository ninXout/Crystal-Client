#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "json.hpp"
#include "Amethyst.hpp"

using json2 = nlohmann::json;

struct CrystalProfile {
    bool noclip = false;
    bool noclipP1 = false;
    bool noclipP2 = false;
    bool tintOnDeath = false;
    bool deathEffect = false;
    bool instantdeath = false;
    bool autoreset = false;
    float autoresetnum = 0;
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
    bool samedual = false;

    bool hitboxes = false;
    bool onDeath = false;
    bool drawTrail = false;
    bool inEditor = false;
    bool fillHitbox = true;
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
    bool verify = false;
    bool copy = false;
    bool editorZoom = false;
    bool loadfail = false;
    
    bool customMessage = false;
    char message[64];
    bool fps = false;
    bool cps = false;
    bool jumps = false;
    bool cheatIndicate = false;
    bool lastDeath = false;
    bool attempts = false;
    bool bestRun = false;
    bool runFrom = false;
    bool noclipAcc = false;
    bool noclipDeath = false;
    bool totalAtt = false;
    bool lvlData = false;
    bool macroStatus = false;
    bool pauseCountdown = false;
    bool clock = false;
    bool igt = false;

    bool RGBAccent = false;
    bool borders = false;
    bool rounded = false;

    bool noTransition = false;
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
};

namespace Crystal {
    static inline CrystalProfile profile;
    static inline void saveToFile(std::string filename);
    static inline void loadFromFile(std::string filename);
}

static inline void Crystal::saveToFile(std::string filename) {
    json2 jf;
    jf["noclip"] = Crystal::profile.noclip;
    jf["noclipP1"] = Crystal::profile.noclipP1;
    jf["noclipP2"] = Crystal::profile.noclipP2;
    jf["tintOnDeath"] = Crystal::profile.tintOnDeath;
    jf["deathEffect"] = Crystal::profile.deathEffect;
    jf["instantdeath"] = Crystal::profile.instantdeath;
    jf["autoreset"] = Crystal::profile.autoreset;
    jf["autoresetnum"] = Crystal::profile.autoresetnum;
    jf["respawnfix"] = Crystal::profile.respawnfix;
    jf["practiceorbfix"] = Crystal::profile.practiceorbfix;
    jf["nopulse"] = Crystal::profile.nopulse;
    jf["trailsize"] = Crystal::profile.trailsize;
    jf["solidwave"] = Crystal::profile.solidwave;
    jf["invisibleplayer"] = Crystal::profile.invisibleplayer;
    jf["customPlayerColor"] = Crystal::profile.customPlayerColor;
    jf["customWaveColor"] = Crystal::profile.customWaveColor;
    jf["rainbowIcon"] = Crystal::profile.rainbowIcon;
    jf["rainbowP1"] = Crystal::profile.rainbowP1;
    jf["rainbowP2"] = Crystal::profile.rainbowP2;
    jf["rainbowP1wave"] = Crystal::profile.rainbowP1wave;
    jf["rainbowP2wave"] = Crystal::profile.rainbowP2wave;
    jf["rainbowspeed"] = Crystal::profile.rainbowspeed;
    jf["samedual"] = Crystal::profile.samedual;
    jf["hitboxes"] = Crystal::profile.hitboxes;
    jf["onDeath"] = Crystal::profile.onDeath;
    jf["drawTrail"] = Crystal::profile.drawTrail;
    jf["inEditor"] = Crystal::profile.inEditor;
    jf["particles"] = Crystal::profile.particles;
    jf["progressBar"] = Crystal::profile.progressBar;
    jf["accpercentage"] = Crystal::profile.accpercentage;
    jf["hideatts"] = Crystal::profile.hideatts;
    jf["hidenormalatts"] = Crystal::profile.hidenormalatts;
    jf["hidepracticeatts"] = Crystal::profile.hidepracticeatts;
    jf["pracmusic"] = Crystal::profile.pracmusic;
    jf["ignoreESC"] = Crystal::profile.ignoreESC;
    jf["confirmQuit"] = Crystal::profile.confirmQuit;
    jf["autoldm"] = Crystal::profile.autoldm;
    jf["flippedcontrol"] = Crystal::profile.flippedcontrol;
    jf["mirrorcontrol"] = Crystal::profile.mirrorcontrol;
    jf["startpos"] = Crystal::profile.startpos;
    jf["checkpointswitch"] = Crystal::profile.checkpointswitch;
    jf["framestep"] = Crystal::profile.framestep;
    jf["lastCheckpoint"] = Crystal::profile.lastCheckpoint;
    jf["noglow"] = Crystal::profile.noglow;
    jf["nospike"] = Crystal::profile.nospike;
    jf["mirror"] = Crystal::profile.mirror;
    jf["layout"] = Crystal::profile.layout;
    jf["autoclick"] = Crystal::profile.autoclick;
    jf["ACpushframe"] = Crystal::profile.ACpushframe;
    jf["ACrelframe"] = Crystal::profile.ACrelframe;
    std::ofstream file(geode::Mod::get()->getSaveDir() / filename);
    file << jf;
    file.close();
}

static inline void Crystal::loadFromFile(std::string filename) {
    std::ifstream ifs(geode::Mod::get()->getSaveDir() / filename);
    if (ifs) {
        json2 jf = json2::parse(ifs);
        Crystal::profile.noclip = jf["noclip"].get<bool>();
        Crystal::profile.noclipP1 = jf["noclipP1"].get<bool>();
        Crystal::profile.noclipP2 = jf["noclipP2"].get<bool>();
        Crystal::profile.tintOnDeath = jf["tintOnDeath"].get<bool>();
        Crystal::profile.deathEffect = jf["deathEffect"].get<bool>();
        Crystal::profile.instantdeath = jf["instantdeath"].get<bool>();
        Crystal::profile.autoreset = jf["autoreset"].get<bool>();
        Crystal::profile.autoresetnum = jf["autoresetnum"].get<float>();
        Crystal::profile.respawnfix = jf["respawnfix"].get<bool>();
        Crystal::profile.practiceorbfix = jf["practiceorbfix"].get<bool>();
        Crystal::profile.nopulse = jf["nopulse"].get<bool>();
        Crystal::profile.trailsize = jf["trailsize"].get<float>();
        Crystal::profile.solidwave = jf["solidwave"].get<bool>();
        Crystal::profile.invisibleplayer = jf["invisibleplayer"].get<bool>();
        Crystal::profile.customPlayerColor = jf["customPlayerColor"].get<bool>();
        Crystal::profile.customWaveColor = jf["customWaveColor"].get<bool>();
        Crystal::profile.rainbowIcon = jf["rainbowIcon"].get<bool>();
        Crystal::profile.rainbowP1 = jf["rainbowP1"].get<bool>();
        Crystal::profile.rainbowP2 = jf["rainbowP2"].get<bool>();
        Crystal::profile.rainbowP1wave = jf["rainbowP1wave"].get<bool>();
        Crystal::profile.rainbowP2wave = jf["rainbowP2wave"].get<bool>();
        Crystal::profile.rainbowspeed = jf["rainbowspeed"].get<float>();
        Crystal::profile.samedual = jf["samedual"].get<bool>();
        Crystal::profile.hitboxes = jf["hitboxes"].get<bool>();
        Crystal::profile.onDeath = jf["onDeath"].get<bool>();
        Crystal::profile.drawTrail = jf["drawTrail"].get<bool>();
        Crystal::profile.inEditor = jf["inEditor"].get<bool>();
        Crystal::profile.particles = jf["particles"].get<bool>();
        Crystal::profile.progressBar = jf["progressBar"].get<bool>();
        Crystal::profile.accpercentage = jf["accpercentage"].get<bool>();
        Crystal::profile.hideatts = jf["hideatts"].get<bool>();
        Crystal::profile.hidenormalatts = jf["hidenormalatts"].get<bool>();
        Crystal::profile.hidepracticeatts = jf["hidepracticeatts"].get<bool>();
        Crystal::profile.pracmusic = jf["pracmusic"].get<bool>();
        Crystal::profile.ignoreESC = jf["ignoreESC"].get<bool>();
        Crystal::profile.confirmQuit = jf["confirmQuit"].get<bool>();
        Crystal::profile.autoldm = jf["autoldm"].get<bool>();
        Crystal::profile.flippedcontrol = jf["flippedcontrol"].get<bool>();
        Crystal::profile.mirrorcontrol = jf["mirrorcontrol"].get<bool>();
        Crystal::profile.startpos = jf["startpos"].get<bool>();
        Crystal::profile.checkpointswitch = jf["checkpointswitch"].get<bool>();
        Crystal::profile.framestep = jf["framestep"].get<bool>();
        Crystal::profile.lastCheckpoint = jf["lastCheckpoint"].get<bool>();
        Crystal::profile.noglow = jf["noglow"].get<bool>();
        Crystal::profile.nospike = jf["nospike"].get<bool>();
        Crystal::profile.mirror = jf["mirror"].get<bool>();
        Crystal::profile.layout = jf["layout"].get<bool>();
        Crystal::profile.autoclick = jf["autoclick"].get<bool>();
        Crystal::profile.ACpushframe = jf["ACpushframe"].get<int>();
        Crystal::profile.ACrelframe = jf["ACrelframe"].get<int>();
    }
}