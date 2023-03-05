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
#include <Geode/modify/CCScheduler.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
#include <Geode/modify/UILayer.hpp>
#include <Geode/modify/ObjectToolbox.hpp>
#include <Geode/modify/LevelTools.hpp>
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

/*

	Some Documentation (because this code is awful to read as of rn):
	CrystalClient::toggle turns off and on the menu
	CrystalClient::applyTheme makes the colors and shapes work
	CrystalClient::drawPages is where the imgui is
	CrystalClient::saveMods and CrystalClient::loadMods are self explanatory
	CrystalClient::arrangeText rearranges the display text correctly


*/

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace crystal {
    std::vector<const char*> playerHacks = { // player hacks comments are wrong
        "Noclip Player 1", //playerBools[0]
        "Noclip Player 2", //playerBools[1]
        "Rainbow Icon P1", //playerBools[2]
        "Rainbow Icon P2", //playerBools[3]
        "Rainbow Wave Trail", //playerBools[4]
        "Same Color Dual", //playerBools[5]
        "Show Hitboxes on Death", //playerBools[6]
        "Show Hitboxes", //playerBools[7]
        "Show Hitbox trail", //playerBools[8]
        "Show Hitboxes in Editor", //playerBools[9]
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
        "Force Dont Fade", //playerBools[37]
        "Force Dont Enter", //playerBools[38]
        "Layout Mode", //playerBools[39]
        "AutoClicker", //playerBools[40]
        "Smart StartPos", //playerBools[41]
        "Practice Bug Fix", //playerBools[42]
        "Hide Pause Menu", //playerBools[43]
    };
    bool playerBools[45] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,};
    std::vector<const char*> globalHacks = { 
        "FPS Bypass",
        "Speedhack",
        "Safe Mode",
        "No Transition",
        "No Rotation",
        "Auto Safe Mode",
        "Auto Deafen",
        "Transparent BG"
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
        "Level Edit", //d
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
        "Hide ID", //d
        "Show Author", //d
        "Macro Status", //d
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
    float LightColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float DarkColour[4];
    float VeryLightColour[4];

    ImVec4 RGBAtoIV4(float rgb[4]) {
        float newr = rgb[0];
        float newg = rgb[1];
        float newb = rgb[2];
        float newa = rgb[3];
        return ImVec4(newr, newg, newb, newa);
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
    bool g_toReset;

    int completepos;
    int pauseZorder;

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
    static int noclip_deaths = 0;
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

    // Amethyst
    bool record;
    bool replay;
    bool deltaLock;
    char macroname[25];
    int frame;
    std::list<int> pushes;
    std::vector<float> Pxpos;
    std::vector<float> Pypos;
    std::vector<float> Paccel;
    std::list<int> releases;
    std::vector<float> Rxpos;
    std::vector<float> Rypos;
    std::vector<float> Raccel;
    std::vector<float> xpos;
    std::vector<float> ypos;
    std::vector<float> accel;
    std::vector<int> CPoffset;
    std::vector<float> CPaccel;
    std::vector<float> CProt;
    int offset;
    int pushIt;
    int releaseIt;
    int posIt;
    float yAccel;
    bool clickBot;
    bool pushing;
    const char* macroTypes[] = { "No Player Physics", "Physics on Click", "Physics every Frame" };
    static int currentMacroType = 0;

    // FPS Display
    std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
    float frame_time_sum = 0.f;
    int frame_count = 0;
    int bypass = 60;
    bool applybypass;
    double g_fps = 60.0;
    double time_since = 0;

    // Display
    bool attempts;
    CCLabelBMFont* g_atts;
    bool percentcustom;
    float percentXpos = 100;
    float percentYpos = 100;
    float percentScale = 0.25;
    float percentOpac = 255;
    int clickscount;

    CCLabelBMFont* g_run;
    CCLabelBMFont* g_bestRun;
    bool currentRun;
    bool bestRun;
    int bestEnd = 0;
    int bestStart = 0;
    int bestEnd2 = 0;
    int bestStart2 = 0;
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

    // Rainbow Icons
    cocos2d::_ccColor3B col;
    cocos2d::_ccColor3B colInverse;

    // Grid Size
    float gridSize = 30;

    // Draw Divide
    bool drawDivide;
    int FRAME_COUNTER;
    int DRAW_DIVIDE = 1;
    bool DRAW_SCENE;

    //uint16_t unicode = (uint16_t)H;

    bool hack;
    int cl = 0;
}