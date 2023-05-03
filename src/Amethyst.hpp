#pragma once
#include <Geode/Geode.hpp>
#include "CrystalProfile.hpp"

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
    void apply(PlayerObject* player) {
        player->setRotation(rot);
        player->m_position.x = xpos;
        player->m_position.y = ypos;
        player->m_yAccel = yaccel;
        player->m_xAccel = xaccel;
        player->m_jumpAccel = jump_accel;
        player->m_isUpsideDown = isUpsideDown;
        player->m_vehicleSize = vehicle_size;
        player->m_playerSpeed = player_speed;
    }
};

CheckpointData store();

namespace AmethystReplay {
    struct AmethystFrame {
        float xpos;
        float ypos;
        double accel;
        void apply(PlayerObject* player) {
            player->m_yAccel = accel;
            player->m_position.x = xpos;
            player->m_position.y = ypos;
        }
    };

    static inline std::vector<int> pushes;
    static inline std::vector<int> releases;
    static inline std::vector<AmethystReplay::AmethystFrame> pushData;
    static inline std::vector<AmethystReplay::AmethystFrame> releaseData;
    static inline std::vector<AmethystReplay::AmethystFrame> framesData;
    static inline std::vector<CheckpointData> checkpoints;
    static inline std::vector<int> checkpointFrames;
    static inline std::vector<int> FrameOffset;

    static inline int currentPindex = 0;
    static inline int currentRindex = 0;
    static inline int currentIndex = 0;
    static inline int currentFrame = 0;
    static inline int currentOffset = 0;

    static inline bool pushing = false;

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