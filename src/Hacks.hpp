#include "Includes.hpp"
#include <streambuf>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

void fps_shower_init();

    CCSprite* noclipRed;
    int opacity = 100;

    ImFont* m_defaultFont  = nullptr;

    std::vector<int> GUIpositions = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15
    };

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
    std::vector<PlayerCheckpoint*> g_checkpointsIG;
    std::vector<CCPoint> g_checkpointsPos;
    int g_checkpointIndex;
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
    std::vector<GameObject*> g_activated_objects_p2;
    std::vector<std::pair<size_t, size_t>> g_orbCheckpoints;

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

    // Amethyst
    bool gameStarted;
    bool rendering;
    bool withAudio;
    int lastTime;
    float DTime;
    std::vector<AmethystReplay::AmethystFrame> stepData;

    inline int g_frameCount;
    inline double g_speedMod = 1.0;

    inline std::vector<std::function<void()>> g_updates;
    void newFPSTimer();

    const char* macroTypes[3] = { "No Player Physics", "Physics on Click", "Physics every Frame" };
    static int currentMacroType = 0;
    double renderTime;
    int timeRate;

    auto macros = Mod::get()->getConfigDir().append("Amethyst").append("Macros");
    auto cb = Mod::get()->getConfigDir().append("Amethyst").append("ClickBot");
    auto framesFol = Mod::get()->getConfigDir().append("Amethyst").append("Renderer").append("Frames");
    auto renderer = Mod::get()->getConfigDir().append("Amethyst").append("Renderer");
    auto conf = Mod::get()->getConfigDir().append("Config");

    // Auto-Deafen
    bool notDeafened = true;
    double deafenPercent = 10;

    // FPS Display
    int bypass = 60;
    double time_since;
    float tps = 60;
    bool tpsBypass;
    bool g_disable_render = false;
    float g_left_over = 0.f;
    float fps_left_over = 0.f;
    float t_left_over = 0.f;

    double m_resetInterval;
	std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
    float frame_time_sum = 0.f;
    int frame_count = 0;

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
    CCLabelBMFont* g_clock;
    CCLabelBMFont* g_fps;

    CCSprite* rightButton;
    CCSprite* leftButton;

    int nextTR = 1;
    int nextTL = 1;
    int nextBR = 1;
    int nextBL = 1;

    char themeName[32];

    const char* positionList[4] = { "Top Left", "Top Right", "Bottom Left", "Bottom Right" };

    // Rainbow Icons
    cocos2d::_ccColor3B col;
    cocos2d::_ccColor3B colInverse;

    int ss = 0;
    float g = 0;

    // AutoClicker
    int clickframe;

    // Unorganized
    float pulse = 2;
    float zoom = 1;
    float v_tracking;
    bool framestep;
    bool stepready = false;
    int autoresetnum;
    bool autoreset;
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