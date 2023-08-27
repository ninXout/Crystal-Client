#include "Includes.hpp"
#include <streambuf>
#include "subprocess.hpp"
#include "./Renderer/Renderer.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

void fps_shower_init();

    //CCSprite* noclipRed;
    //int opacity = 100;

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

    CCTexture2D* renderingTexture;
    GLint m_pOldFBO;
    GLuint m_pFBO;
    GLint m_pOldRBO;

    // Customization
    bool sameAsAccent;
    bool RGBAccent;
    bool borders;
    bool rounded;

    struct A : cocos2d::CCObject {
        void restart() {
            auto pl = (PlayLayer*)this;

            pl->resetLevel();
        }
    };

    // Checkpoint Switcher
    std::vector<std::pair<CheckpointObject*, CCPoint>> g_checkpoints;
    int g_checkpointIndex;
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
    //bool would_die;
    bool dying = false;
    bool deaath = false;

    // Amethyst
    //AmethystMacro currentMacro;


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

    // Amethyst
    //bool gameStarted;
    bool rendering;
    bool withAudio;
    float DTime;
    std::vector<AmethystReplay::AmethystFrame> stepData;

    const char* macroTypes[3] = { "No Player Physics", "Physics on Click", "Physics every Frame" };
    static int currentMacroType = 0;
    double renderTime;
    int timeRate;
    int lastMacroTime;

    auto macros = Mod::get()->getConfigDir().append("Amethyst").append("Macros");
    auto cb = Mod::get()->getConfigDir().append("Amethyst").append("ClickBot");
    auto framesFol = Mod::get()->getConfigDir().append("Amethyst").append("Renderer").append("Frames");
    auto renderer = Mod::get()->getConfigDir().append("Amethyst").append("Renderer");
    auto conf = Mod::get()->getConfigDir().append("Config");
    auto betterBG = Mod::get()->getConfigDir().append("BetterBG");

    //subprocess::Popen process;

    // Auto-Deafen
    bool notDeafened = true;
    double deafenPercent = 10;

    // FPS Display
    int bypass = 60;
    double time_since;
    float tps = 60;
    bool tpsBypass;
    bool g_disable_render = false;
    float fps_left_over = 0.f;
    float t_left_over = 0.f;

    static int s_localFPS = 60;
    static int s_cascades = 0;
    static int s_skipMultiplier = 1;
    inline int g_frameCount;
    inline std::vector<std::function<void()>> g_updates;
    void newFPSTimer();

    Recorder record;

    // CPS Display
    bool holding;
    float click_time_sum = 0.f;
    int clickscount;
    int click_count;

    std::string cipy;
    std::chrono::time_point<std::chrono::high_resolution_clock> previous, last;

    // Display
    bool attempts;
    CCLabelBMFont* g_atts;
    bool percentcustom;
    int releasecount;
    float fixa = 0.0f;
    float timee = 0.0f;

    std::chrono::time_point<std::chrono::high_resolution_clock> tiem;
    bool isTiemOn = false;

    CCLabelBMFont* g_levelInfo;
    CCLabelBMFont* g_clicks;
    CCLabelBMFont* g_jumps;
    CCLabelBMFont* g_cheating;
    CCLabelBMFont* g_tatts;
    CCLabelBMFont* g_death;
    CCLabelBMFont* g_message;
    CCLabelBMFont* g_run;
    CCLabelBMFont* g_bestRun;
    CCLabelBMFont* g_macro;
    CCLabelBMFont* g_clock;
    CCLabelBMFont* g_fps;

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

    // Unorganized
    std::string image;
    float pulse = 2;
    float zoom = 1;
    float v_tracking;
    bool framestep;
    bool stepready = false;
    int autoresetnum;
    bool autoreset;
    bool customMessage;
    float rainbowspeed = 5;
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
    float newDT;
    //bool lastDeath;