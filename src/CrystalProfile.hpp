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
    
    bool testmode = true;
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

    int POStestmode = 0;
    int POScustomMessage = 0;
    int POSfps = 0;
    int POScps = 0;
    int POSjumps = 0;
    int POScheatIndicate = 0;
    int POSlastDeath = 0;
    int POSattempts = 0;
    int POSbestRun = 0;
    int POSrunFrom = 0;
    int POSnoclipAcc = 0;
    int POSnoclipDeath = 0;
    int POStotalAtt = 0;
    int POSlvlData = 0;
    int POSmacroStatus = 0;
    int POSpauseCountdown = 0;
    int POSclock = 0;
    int POSigt = 0;

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
    void saveMods(CrystalProfile const& data);
    CrystalProfile loadMods();
}