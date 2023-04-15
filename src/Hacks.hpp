#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/CCLayerColor.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/AchievementNotifier.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GameObject.hpp>
#include <Geode/modify/GameSoundManager.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/UILayer.hpp>
#include <Geode/modify/ObjectToolbox.hpp>
#include <Geode/modify/LevelTools.hpp>
#include <Geode/loader/Dirs.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <numbers>
#include <dirent.h>
#include "HitboxNode.hpp"
#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>
#include <CoreServices/CoreServices.h>
#include "Amethyst.hpp"
#include <Geode/fmod/fmod.hpp>
#include "globalBP.h"
#include <stdio.h>

#pragma once

/*

	Some Documentation (because this code is awful to read as of rn):
	CrystalClient::toggle turns off and on the menu
	CrystalClient::applyTheme makes the colors and shapes work
	CrystalClient::drawPages is where the imgui is
	CrystalClient::saveMods and CrystalClient::loadMods are self explanatory
	CrystalClient::arrangeText rearranges the display text correctly
    CrystalClient::getMod accesses the mods from the vectors
    CrystalClient::setMod changes them

*/

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

void fps_shower_init();

std::vector<const char*> playerHacks = { // player hacks comments are wrong
        "Noclip", //playerBools[0]
        //"Noclip Player 2", //playerBools[1]
        "Rainbow Icon P1", //playerBools[2]
        "Rainbow Icon P2", //playerBools[3]
        "Rainbow Wave Trail", //playerBools[4]
        "Same Color Dual", //playerBools[5]
        "Show Hitboxes on Death", //playerBools[6]
        "Show Hitboxes", //playerBools[7]
        "Show Hitbox Trail", //playerBools[8]
        "Show Hitboxes in Editor", //playerBools[9]
        "Coin Finder",
        "Disable Death Effect", //playerBools[10]
        "Disable Particles", //playerBools[11]
        "Disable Progressbar", //playerBools[12]
        "Accurate Percentage", //playerBools[13]
        "No Wave Pulse", //playerBools[14]
        "Hide Attempts", //playerBools[15]
        "Hide Attempts in Practice Mode", //playerBools[16]
        "Practice Music Hack", //playerBools[17]
        "Ignore ESC", //playerBools[18]
        "Confirm Quit", //playerBools[19]
        "Auto LDM", //playerBools[20]
        "Instant Death Respawn", //playerBools[21]
        "Flipped Dual Controls", //playerBools[22]
        "Mirrored Dual Controls", //playerBools[23]
        "StartPos Switcher", //playerBools[24]
        "Respawn Bug Fix", //playerBools[25]
        "Practice Orb Bugfix", //playerBools[26]
        "Checkpoint Switcher", //playerBools[27]
        "Solid Wave Trail",//playerBools[28]
        "Frame Stepper", //playerBools[29]
        "Load from Last Checkpoint", //playerBools[30]
        "Auto Reset", //playerBools[31]
        "Invisible Player", //playerBools[32]
        "No Trail", //playerBools[33]
        "No Glow", //playerBools[34]
        "No Spikes", //playerBools[35]
        "No Mirror", //playerBools[36]
        "Freeze Attempts",
        //"Force Dont Fade", //playerBools[37]
        //"Force Dont Enter", //playerBools[38]
        "Layout Mode", //playerBools[39]
        "AutoClicker", //playerBools[40]
        "Hide Pause Menu", //playerBools[41]
    };
    bool playerBools[45] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,};
    std::vector<const char*> globalHacks = { 
        "FPS Bypass",
        "Speedhack",
        "Safe Mode",
        "No Transition",
        "No Rotation",
        "Safe Mode",
        "Auto Deafen",
        "Mute on Unfocus",
        "Unfocused FPS",
    };
    bool globalBools[30] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, };
    std::vector<const char*> bypassHacks = { 
        "Anticheat Bypass", //d
        "Unlock All", //d
        "Object Limit Bypass", //d
        "Custom Object Object Limit Bypass", //d
        "Custom Object Limit Bypass", //d
        "Verify Bypass", //d
        "Copy Bypass", //d
        "Slider Bypass", //d
        "Editor Zoom Bypass", //d
        "Instant Complete", //d
        "Load Failed Bypass", //d
    };
    bool bypassBools[30] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, };
    std::vector<const char*> guiHacks = { 
        "Custom Message", //d (still need text input)
        "FPS Display", //d
        "CPS and Clicks", //d
        "Jumps", //d
        "Cheat Indicator", //d
        "Last Death", //d
        "Attempts Display", //d
        "Best Run", //d
        "Run From", //d
        "Noclip Accuracy", //d (still need reset accuracy)
        "Noclip Deaths", //d
        "Total Attempts", //d
        "Level Name and ID", //d
        "Macro Status", //d
        "Pause Countdown", //d
    };
    bool guiBools[30] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, };
    const char* item_names[13] = {
        "Custom Message", //d (still need text input)
        "CPS and Clicks", //d
        "Jumps", //d
        "Cheat Indicator", //d
        "Last Death", //d
        "Attempts Display", //d
        "Best Run", //d
        "Run From", //d
        "Noclip Accuracy", //d (still need reset accuracy)
        "Noclip Deaths", //d
        "Total Attempts", //d
        "Level Name and ID", //d
        "Macro Status", //d
    };

    float rDir = -0.05;
    float gDir = 0.05;
    float bDir = -0.05;

    float BGColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float LightColour[4] = { 0.262715f,
                            0.624691f,
                            0.818605f,
                            1.0f };
    float DarkColour[4];
    float VeryLightColour[4];

    bool customPLcolor;
    bool customWaveColor;
    bool customGlowColor;

    float Player1Col[4];
    float Player2Col[4];

    float Player1Wave[4];
    float Player2Wave[4];

    float Player1Glow[4];
    float Player2Glow[4];

    cocos2d::_ccColor3B Player1CC3;
    cocos2d::_ccColor3B Player2CC3;

    CCSprite* noclipRed;
    int opacity = 100;

    ImVec4 RGBAtoIV4(float rgb[4]) {
        float newr = rgb[0];
        float newg = rgb[1];
        float newb = rgb[2];
        float newa = rgb[3];
        return ImVec4(newr, newg, newb, newa);
    }

    ImVec4 CC3toIV4(cocos2d::_ccColor3B col) {
        float newr = col.r / 255;
        float newg = col.g / 255;
        float newb = col.b / 255;
        float newa = 1;
        return ImVec4(newr, newg, newb, newa);
    }
    
    cocos2d::_ccColor3B RGBAtoCC3(float vec[4]) {
        cocos2d::_ccColor3B ret;
        ret.r = vec[0] * 255;
        ret.g = vec[1] * 255;
        ret.b = vec[2] * 255;
        return ret;
    }

    ImFont* m_defaultFont  = nullptr;
    ImFont* m_smallFont    = nullptr;
    ImFont* m_monoFont     = nullptr;
    ImFont* m_boxFont      = nullptr;

    bool hasSetupFonts = false;

    // StartPos Switcher
    std::vector<std::pair<StartPosObject*, CCPoint>> g_startPoses;
    int g_startPosIndex;
    CCLabelBMFont* g_startPosText;

    // Customization
    bool sameAsAccent;
    bool RGBAccent;
    bool borders;
    bool rounded;

    // Checkpoint Switcher
    bool cpswitch;
    std::vector<PlayerCheckpoint*> g_checkpointsIG;
    std::vector<CCPoint> g_checkpointsPos;
    int g_checkpointIndex;
    bool load;
    CCLabelBMFont* g_checkpointText;
    CCSprite* CPrightButton;
    CCSprite* CPleftButton;

    // Noclip Accuracy
    static float frames, noclipped_frames = 0;
    bool completed = false;
    static float limitframes = 0;
    CCLabelBMFont* text;
    float percent;
    bool lenient;
    float killaccuracy;
    bool finished;
    bool resetaccuracy;
    bool would_die;

    // Noclip Deaths
    int noclip_deaths = 0;
    CCLabelBMFont* font;
    int deathwait;

    // Respawn
    int smoothOut = 0;

    // Practice Orb Bugfix
    std::vector<GameObject*> g_activated_objects;
    std::vector<GameObject*> g_activated_objects_p2; // amazing
    std::vector<std::pair<size_t, size_t>> g_orbCheckpoints;
    bool practiceOrb;

    // Smart Start Pos
    std::vector<GameObject*> gravityPortals;
    std::vector<GameObject*> gamemodePortals;
    std::vector<GameObject*> mirrorPortals;
    std::vector<GameObject*> miniPortals;
    std::vector<GameObject*> dualPortals;
    std::vector<GameObject*> speedChanges;
    std::vector<GameObject*> coins;
    std::vector<StartPosObject*> SPs;
    std::vector<bool> willFlip;
    
    // Hitbox Visualizer
    static inline bool s_onlyHitboxes = false;
    static inline bool s_showOnDeath = false;
    static inline bool s_drawOnDeath = false;
    static inline bool s_noLimitTrail = false;
    static inline tulip::HitboxNode* s_drawer = nullptr;
    bool editorHitbox;
    bool turnonHitbox;

    // Variable Changer
    const char* playerVars[7] = { "Gravity", "X Acceleration", "Y Acceleration", "X Position", "Y Position", "Jump Acceleration", "Vehicle Size" };
    const char* levelVars[4] = { "Level Name", "Level Author", "Level ID", "Level Song" };
    static int currentVar = 0;
    static float changeValue = 0;
    std::vector<int> playerVariables;
    std::vector<float> playerValues;

    // Amethyst
    bool record;
    bool replay;
    bool rendering;
    bool withAudio;
    bool deltaLock;
    char macroname[25];
    int frame;
    int newFrame;
    float musicOffset;
    int replayFPS;
    std::vector<int> pushes;
    std::vector<int> releases;
    std::vector<Amethyst::AmethystFrame> pushData;
    std::vector<Amethyst::AmethystFrame> releaseData;
    std::vector<Amethyst::AmethystFrame> frameData;
    std::vector<Amethyst::CheckpointData> checkpointData;
    std::vector<int> CPoffset;
    std::vector<int> FrameOffset;
    int offset;
    int FRoffset;
    int pushIt;
    int releaseIt;
    int posIt;
    int lastFrame;
    bool clickBot;
    bool pushing;
    const char* macroTypes[3] = { "No Player Physics", "Physics on Click", "Physics every Frame" };
    static int currentMacroType = 0;
    double renderTime;
    inline extern bool inited = false;
    float clickVolume = 500;
    int timeRate;

    static int currentKey = 0;
    static int currentMod = 0;

    std::vector<int> activeKeys;
    std::vector<int> activeMods;

    const char* keybindings[48] = { "Space Bar", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "Backspace", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape" };
    const char* modbindings[13] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint", "Toggle Crystal Menu" };

    // Auto-Deafen
    bool notDeafened = true;
    double deafenPercent = 100;

    // FPS Display
    int bypass = 60;
    double time_since;
    float tps = 60;
    bool tpsBypass;
    bool g_disable_render = false;
    float g_left_over = 0.f;
    float fps_left_over = 0.f;

    // Display
    bool attempts;
    CCLabelBMFont* g_atts;
    bool percentcustom;
    int clickscount;
    int releasecount;

    CCLabelBMFont* g_run;
    CCLabelBMFont* g_bestRun;
    bool currentRun;
    bool bestRun;
    int bestEnd;
    int bestStart;
    int bestEnd2;
    int bestStart2;
    std::string display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);

    CCLabelBMFont* g_levelInfo;
    CCLabelBMFont* g_clicks;
    CCLabelBMFont* g_jumps;
    CCLabelBMFont* g_cheating;
    CCLabelBMFont* g_tatts;
    CCLabelBMFont* g_death;
    CCLabelBMFont* g_message;
    CCLabelBMFont* g_macro;

    CCSprite* rightButton;
    CCSprite* leftButton;

    // AutoClicker
    int clickframe;
    int clickRel;
    int clickPush;

    // Unorganized
    float pulse = 2;
    float zoom = 1;
    float v_tracking;
    bool framestep;
    bool stepready = false;
    int autoresetnum;
    bool autoreset;
    char message[64];
    bool customMessage;
    float rainbowspeed = 5;
    bool shouldQuit;
    bool overrideFL;
    bool settingRefresh;
    bool instantmaybe;
    bool macroStatus;
    bool classicspeed;
    std::string bad;
    bool pausecountdown;
    bool freezeCount;
    int countdown;
    CCLabelBMFont* g_pauseCount;
    bool inputmirror;
    float speedhack = 1;
    bool shouldUpdate = false;
    float newDT;
    bool author;
    bool hideID;
    bool lastDeath;

    // Rainbow Icons
    cocos2d::_ccColor3B col;
    cocos2d::_ccColor3B colInverse;

    // Macro Buffer
    std::vector<cocos2d::CCRect> newQueue;
    bool macroBuffer;

    // Grid Size
    float gridSize = 30;

    // Draw Divide
    double frame_remainder = 0;
    int target_fps = 60;
    int frame_counter = 0;
    bool drawDivide = false;

    //uint16_t unicode = (uint16_t)H;

    bool hack;
    int cl = 0;

    int ss = 0;

    bool specialAccess;

    bool noclipP1;
    bool noclipP2;
    bool tintOnDeath;

/*
    bool noclip;
    bool rainbowP1;
    bool rainbowP2;
    bool rainbowP1wave;
    bool rainbowP2wave;

    bool samedual;

    bool hitboxes;
    bool onDeath; // Hitboxes on Death
    bool drawTrail;
    bool inEditor;

    bool deathEffect;
    bool particles;
    bool progressBar;
    bool accpercentage;

    bool nopulse;
    bool hideatts;
    bool hidepracticeatts;

    bool pracmusic;
    bool ignoreESC;
    bool confirmQuit;
    bool autoldm;

    bool instantdeath;
    bool flippedcontrol;
    bool mirrorcontrol;

    bool startpos;
    bool respawnfix;
    bool practiceorbfix;

    bool checkpointswitch;
    bool solidwave;
    bool framestep;

    bool lastCheckpoint;
    bool autoreset;
    bool invisibleplayer;

    bool noglow;
    bool nospike;
    bool mirror;
    bool layout;

    bool autoclick;
    */