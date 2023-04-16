#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "json.hpp"

#define Crystal::profile { profile }

using json2 = nlohmann::json;

struct CrystalProfile {
    bool noclip = false;
    bool noclipP1 = false;
    bool noclipP2 = false;
    bool tintOnDeath = false;
    bool deathEffect = false;
    bool instantdeath = false;
    bool autoreset = false;
    float autoresetpercent = 0;
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
};

namespace Crystal {
    static inline CrystalProfile profile;
}

static CrystalProfile create() {
    static CrystalProfile instance;
    return instance;
}

static void saveToFile(std::string filename) {
    json2 jf;
    jf["noclip"] = profile.noclip;
    jf["noclipP1"] = profile.noclipP1;
    jf["noclipP2"] = profile.noclipP2;
    jf["tintOnDeath"] = profile.tintOnDeath;
    jf["deathEffect"] = profile.deathEffect;
    jf["instantdeath"] = profile.instantdeath;
    jf["autoreset"] = profile.autoreset;
    //float autoresetpercent = 0;
    jf["respawnfix"] = profile.respawnfix;
    jf["practiceorbfix"] = profile.practiceorbfix;
    jf["nopulse"] = profile.nopulse;
    //float trailsize = 0;
    jf["solidwave"] = profile.solidwave;
    jf["invisibleplayer"] = profile.invisibleplayer;
    jf["customPlayerColor"] = profile.customPlayerColor;
    jf["customWaveColor"] = profile.customWaveColor;
    jf["rainbowIcon"] = profile.rainbowIcon;
    jf["rainbowP1"] = profile.rainbowP1;
    jf["rainbowP2"] = profile.rainbowP2;
    jf["rainbowP1wave"] = profile.rainbowP1wave;
    jf["rainbowP2wave"] = profile.rainbowP2wave;
    //float rainbowspeed = 0;
    jf["samedual"] = profile.samedual;
    jf["hitboxes"] = profile.hitboxes;
    jf["onDeath"] = profile.onDeath;
    jf["drawTrail"] = profile.drawTrail;
    jf["inEditor"] = profile.inEditor;
    jf["particles"] = profile.particles;
    jf["progressBar"] = profile.progressBar;
    jf["accpercentage"] = profile.accpercentage;
    jf["hideatts"] = profile.hideatts;
    jf["hidenormalatts"] = profile.hidenormalatts;
    jf["hidepracticeatts"] = profile.hidepracticeatts;
    jf["pracmusic"] = profile.pracmusic;
    jf["ignoreESC"] = profile.ignoreESC;
    jf["confirmQuit"] = profile.confirmQuit;
    jf["autoldm"] = profile.autoldm;
    jf["flippedcontrol"] = profile.flippedcontrol;
    jf["mirrorcontrol"] = profile.mirrorcontrol;
    jf["startpos"] = profile.startpos;
    jf["checkpointswitch"] = profile.checkpointswitch;
    jf["framestep"] = profile.framestep;
    jf["lastCheckpoint"] = profile.lastCheckpoint;
    jf["noglow"] = profile.noglow;
    jf["nospike"] = profile.nospike;
    jf["mirror"] = profile.mirror;
    jf["layout"] = profile.layout;
    jf["autoclick"] = profile.autoclick;
    std::ofstream file(geode::Mod::get()->getSaveDir() / "GH_config.json");
    file << jf;
    file.close();
}

static CrystalProfile loadFromFile(std::string filename) {
    std::ifstream ifs(geode::Mod::get()->getSaveDir() / "GH_config.json");
    json2 newJSON = json2::parse(ifs);
    //auto newthing = newJSON.get<CrystalProfile>();
    return profile;
}