#pragma once
#include <Geode/Geode.hpp>
#include "../CrystalProfile.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

struct CheckpointData {
    float xpos;
    float ypos;
    float rot;
    double yaccel;
    double xaccel;
    double jump_accel;
    bool isUpsideDown;
    float vehicle_size;
    float player_speed;
    GameObject* snapped_obj;
    bool holding;
    bool justHeld;
    bool holding2;
    bool justHeld2;
    bool sliding;
    bool rising;
    bool robotJump;
    void apply(PlayerObject* player) {
        player->setRotation(rot);
        player->m_position.x = xpos;
        player->m_position.y = ypos;
        player->m_yVelocity = yaccel;
        player->m_xVelocity = xaccel;
        player->m_jumpAccel = jump_accel;
        player->m_isUpsideDown = isUpsideDown;
        player->m_vehicleSize = vehicle_size;
        player->m_playerSpeed = player_speed;
        player->m_objectSnappedTo = snapped_obj;
        player->m_isHolding = holding;
        player->m_hasJustHeld = justHeld;
        player->m_isHolding2 = holding2;
        player->m_hasJustHeld2 = justHeld2;
        player->m_isSliding = sliding;
        player->m_isRising = rising;
        player->m_canRobotJump = robotJump;
    }
};

CheckpointData store(PlayerObject* player);

enum ButtonState {
    NONE,
    PUSH,
    RELEASE
};

class AmethystMacro {
    public:
        struct AmethystFrame {
            float xpos;
            float ypos;
            float rot;
            double accel;
            ButtonState state;
            void apply(PlayerObject* player) {
                player->m_yVelocity = accel;
                player->m_position.x = xpos;
                player->m_position.y = ypos;
                player->getRotation() = rot;
            }
        };

        static AmethystMacro createFromFile(const char* filename, bool legacy);
        void updateReplay(float dt);
        void resetActions();
        void addAction(bool player);
        void saveToFile(const char* filename);

    protected:
        std::vector<AmethystFrame> P1frames;
        std::vector<AmethystFrame> P2frames;
        std::vector<CheckpointData> P1checkpoints;
        std::vector<CheckpointData> P2checkpoints;

        int currentP1index = 0;
        int currentR1index = 0;
        int currentP2index = 0;
        int currentR2index = 0;
        float currentFrame = 0;

        bool P1pushing = false;
        bool P2pushing = false;
};

namespace AmethystReplay {
    struct AmethystFrame {
        float xpos;
        float ypos;
        double accel;
        void apply(PlayerObject* player) {
            player->m_yVelocity = accel;
            player->m_position.x = xpos;
            player->m_position.y = ypos;
        }
    };

    static inline std::vector<float> P1pushes;
    static inline std::vector<float> P1releases;
    static inline std::vector<float> P2pushes;
    static inline std::vector<float> P2releases;
    static inline std::vector<int> P1pushesINT;
    static inline std::vector<int> P1releasesINT;
    static inline std::vector<int> P2pushesINT;
    static inline std::vector<int> P2releasesINT;
    static inline std::vector<float> checkpointFrames;
    static inline std::vector<CheckpointData> P1checkpoints;
    static inline std::vector<CheckpointData> P2checkpoints;

    static inline int currentP1index = 0;
    static inline int currentR1index = 0;
    static inline int currentP2index = 0;
    static inline int currentR2index = 0;
    static inline float currentFrame = 0;
    static inline int currentTXTFrame = 0;

    static inline bool P1pushing = false;
    static inline bool P2pushing = false;

    void resetActions();
    void updateAmethyst();
    void addAction(bool push);
    AmethystFrame create();
}

namespace Clickbot {
    std::string pickRandomClick();
    std::string pickRandomSoftClick();
    std::string pickRandomRelease();
    std::string pickRandomSoftRelease();

    static inline bool firstClick = false;
    static inline std::chrono::system_clock::time_point start, now;
    static inline std::chrono::duration<double> cycleTime;
    static inline bool inited = false;

    static inline FMOD::System* system;
    static inline FMOD::Channel* clickChannel;
    static inline FMOD::Sound* clickSound;
    static inline FMOD::Channel* releaseChannel;
    static inline FMOD::Sound* releaseSound;

    static inline FMOD::Channel* noiseChannel;
    static inline FMOD::Sound* noiseSound;
}