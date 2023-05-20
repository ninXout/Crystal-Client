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
    GameObject* snapped_obj;
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
    }
};

CheckpointData store(PlayerObject* player);

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
    static inline std::vector<float> checkpointFrames;
    static inline std::vector<CheckpointData> P1checkpoints;
    static inline std::vector<CheckpointData> P2checkpoints;

    static inline int currentP1index = 0;
    static inline int currentR1index = 0;
    static inline int currentP2index = 0;
    static inline int currentR2index = 0;
    static inline float currentFrame = 0;

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