#pragma once
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

class Amethyst {
    public:
        struct AmethystFrame {
            float xpos;
            float ypos;
            double accel;
            void apply(PlayerObject* player) {
                //mbo(float, player, 0x7c8) = xpos;
                //mbo(float, player, 0x7cc) = ypos;
                player->m_yAccel = accel;
                player->m_position.x = xpos;
                player->m_position.y = ypos;
            }
        };

        struct CheckpointData {
            float xpos;
            float ypos;
            float rot;
            double accel;
            void apply(PlayerObject* player) {
                player->setRotation(rot);
                player->m_yAccel = accel;
                player->m_position.x = xpos;
                player->m_position.y = ypos;
            }
        };

        static std::vector<AmethystFrame> frames;
        static AmethystFrame create();
        static CheckpointData store();
};

namespace Clickbot {
    std::string pickRandomClick();
    std::string pickRandomSoftClick();
    std::string pickRandomRelease();
    std::string pickRandomSoftRelease();

    static inline bool firstClick = false;
    static inline std::chrono::system_clock::time_point start, now;
    static inline std::chrono::duration<double> cycleTime;

    static inline FMOD::System* system;
    static inline FMOD::Channel* clickChannel;
    static inline FMOD::Sound* clickSound;
    static inline FMOD::Channel* releaseChannel;
    static inline FMOD::Sound* releaseSound;

    static inline FMOD::Channel* noiseChannel;
    static inline FMOD::Sound* noiseSound;
}