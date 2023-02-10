#include <Geode/Geode.hpp>
#include <Geode/Modify.hpp>
#include <vector>
#include "imgui-cocos.hpp"
#include "HitboxNode.hpp"
#include "imgui.h"
#include <Geode/fmod/fmod.hpp>
#include <Geode/fmod/fmod.h>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <list>
#include <algorithm>
#include <thread>
#include <chrono>
#include <numbers>
#include <Geode/utils/fetch.hpp>
#include <dirent.h>

bool purchase = false;
bool water = false;
int framing;

USE_GEODE_NAMESPACE();

// StartPos Switcher
std::vector<std::pair<StartPosObject*, CCPoint>> g_startPoses;
int g_startPosIndex;
CCLabelBMFont* g_startPosText;
bool g_toReset;

int completepos;

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

// The Hacks
float speedhack = 1;
bool noclip;
bool deathEffect = true;
bool particles = true;
bool progressBar = true;
bool accpercentage = true;
bool nopulse;
float pulse = 2;
bool freecopy = true;
bool unlockall = true;
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
int leftDisplay;

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
bool recording;
bool replay;
bool amethyst;
char macroname[25];
std::vector<float> push;
std::vector<float> rel;
std::vector<float> pos;
std::vector<float> relpos;
int pushIterate = 1;
int releaseIterate = 1;
int posIterate = 1;
bool clickBot;
bool smoothFrames;
bool pushing;
int macrowait;
std::filesystem::path macroPath = std::filesystem::current_path() / "Crystal" / "Amethyst" / "Macros";
const char* macrosList[] = { "None", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty" };
std::vector<std::string> macroVector;
static int macro_current_idx = 0;
double yAccelP1;
double yAccelP2;

int theme = 1;

// Keybindings
int keybinds;

const char* keys[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Arrow", "Right Arrow", "1", "2", "3", "4", "5" };
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