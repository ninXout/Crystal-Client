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
#include <Geode/Enums.hpp>
#include <vector>
#include "HitboxNode.hpp"
#include "imgui.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <numbers>
#include <dirent.h>
#include "amethyst.hpp"

cocos2d::CCScene* gui;

USE_GEODE_NAMESPACE();

using namespace tulip;
using namespace geode::cocos;

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

float rDir = -0.05;
float gDir = 0.05;
float bDir = -0.05;

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

//uint16_t unicode = (uint16_t)H;

bool hack;
int cl = 0;

// The Hacks
std::vector<int> guiReorderInt = { 
    1, //d (still need text input)
    2, //d
    3, //d
    4, //d
    5, //d
    6, //d
    7, //d
    8, //d
    9, //d
    10, //d
    11, //d
    12, //d
    13, //d
};
const char* newGuiReorder[14] = {};

bool drawDivide;
int FRAME_COUNTER;
int DRAW_DIVIDE = 1;
bool DRAW_SCENE;
float gridSize = 30;

bool shouldUpdate = false;


float speedhack = 1;
bool noclip;
bool deathEffect;
bool particles;
bool progressBar;
bool accpercentage;
bool nopulse;
float pulse = 2;
bool freecopy;
bool unlockall;
bool hideatts;
bool hidepracatts;
bool safe;
bool pracmusic = true;
bool rainP1;
bool rainP2;
bool rainP1wave;
bool rainP2wave;
bool respawn;
char speedhack2;
bool startpos;
bool slider = true;
bool objlimit = true;
bool customobjlimit = true;
bool customlimit = true;
bool invis;
bool verify;
bool anticheat;
bool moon;
bool speed;
bool autoclick;
int clickframe;
int clickRel;
int clickPush;
bool drawTrail = true;
bool noLimitTrail = false;
bool onDeath = true;
bool onlyHitbox;
bool restartWithR;
bool fps;
bool levelinfo;
bool clicks;
bool jumps;
bool editorkey;
bool plugin;
bool zoomhack;
float zoom = 1;
float v_tracking;
bool layout;
bool ldm;
bool randomLoop;
bool cheater;
bool ignoreESC;
bool noglow;
bool mirror;
bool anykey;
bool solidwave;
bool samedual;
bool complete;
bool uncomplete;
bool framestep;
bool stepready = false;
bool noTrans;
bool noRot;
bool totalAtts;
bool lastDeath;
bool instantdeath;
bool dualcontrol;
bool notrail;
bool nospike;
bool forcefade;
bool forceenter;
bool accuracy;
bool unfocusmute;
bool freeze;
bool autoKill;
int autoresetnum;
bool autoreset;
char message[64];
bool customMessage;
bool clickreset;
bool nodim;
bool noclipDeaths;
bool author;
bool hideID;
float rainbowspeed = 5;
bool scrollzoom;
bool noclipP1;
bool noclipP2;
bool lastCheckpoint;
int customR1;
int customG1;
int customB1;
int customR2;
int customG2;
int customB2;
bool customColor;
bool confirmQuit;
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

cocos2d::_ccColor3B col;
cocos2d::_ccColor3B colInverse;

int waitframe;

// Display
int leftDisplay = -1;

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

// Rendering
bool showing = false;
bool dev;
bool initimgui;

static inline bool s_onlyHitboxes = false;
static inline bool s_showOnDeath = false;
static inline bool s_drawOnDeath = false;
static inline bool s_noLimitTrail = false;
static inline tulip::HitboxNode* s_drawer = nullptr;
bool editorHitbox;
bool turnonHitbox;

void fps_shower_init();

bool clickready = true;
bool clickready2 = true;
cocos2d::ccColor3B secondary;
cocos2d::ccColor3B primary;

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

int theme = 1;

// Keybindings
std::vector<const char*> bindMods = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
std::vector<const char*> bindKeys = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Up Arrow", "Down Arrow", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Backspace", "Tab", "Enter", "Shift", "Control", "Alt", "Caps Lock", "Escape", "Space" };
std::vector<cocos2d::enumKeyCodes> keyCodes = {
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_ArrowUp,
        KEY_ArrowDown,
        KEY_ArrowLeft,
        KEY_ArrowRight,
        KEY_Zero,
        KEY_One,
        KEY_Two,
        KEY_Three,
        KEY_Four,
        KEY_Five,
        KEY_Six,
        KEY_Seven,
        KEY_Eight,
        KEY_Nine,
        KEY_Backspace,
        KEY_Tab,
        KEY_Enter,
        KEY_Shift,
        KEY_Control,
        KEY_Alt,
        KEY_CapsLock,
        KEY_Escape,
        KEY_Space
};

const char* keybindings[48];
const char* modbindings[10];

std::vector<std::pair<cocos2d::enumKeyCodes, int>> bindvector;

std::vector<unsigned int> activeKeys;
std::vector<unsigned int> activeMods;

const char* macroTypes[] = { "No Player Physics", "Physics on Click", "Physics every Frame" };
static int currentMacroType = 0;

static int currentKey;
static int currentMod;
static ImGuiComboFlags flags = 0;
const char* preview = "Pick A Keybind";

int keybinds;

const char* keys[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "Up Arrow", "Down Arrow", "1", "2", "3", "4", "5" };
const char* mods[] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
static int key_current;
static int mod_current;
const char* keys2[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5" };
const char* mods2[] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
static int key_current2;
static int mod_current2;
const char* keys3[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5" };
const char* mods3[] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
static int key_current3;
static int mod_current3;
const char* keys4[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5" };
const char* mods4[] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
static int key_current4;
static int mod_current4;
const char* keys5[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5" };
const char* mods5[] = { "Noclip", "Suicide", "Restart Level", "Speedhack", "Hitbox Viewer", "AutoClicker", "Switcher Left", "Switcher Right", "Player 1", "Player 2", "Place Checkpoint", "Remove Checkpoint" };
static int key_current5;
static int mod_current5;
cocos2d::enumKeyCodes customKey;
cocos2d::enumKeyCodes customKey2;
cocos2d::enumKeyCodes customKey3;
cocos2d::enumKeyCodes customKey4;
cocos2d::enumKeyCodes customKey5;

// Variable Changer
const char* variables[] = { "Level Name", "Level Description", "Level Author", "Attempts", "Jumps", "Percentage" };
static int variable_index;
bool applyVC;
bool FloatString;
char stringVC[64];
float floatVC;

// NONG Switcher
char replaceWith[64];
char replacing[64];
bool EnableNONGLoader;
std::string findsong;
std::string replacesong;
std::vector<std::string> NONGs;
bool manualNONG;
static int item_current_idx = 0;
const char* items[] = { "None", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty" };

std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
float frame_time_sum = 0.f;
int frame_count = 0;
int bypass = 60;
bool applybypass;
double g_fps = 60.0;
double time_since = 0;