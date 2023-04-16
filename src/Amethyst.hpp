#pragma once
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

struct AmethystReplay {
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

    static void createFromFile(AmethystReplay* replay, char macroname[25]);
    static void saveToFile(AmethystReplay* replay, char macroname[25]);
    void newReplayFrame(bool isReplay, bool isRecord, int tps, int currentMacroType);
    void adjustFrames(int tps, bool pushing, bool record);
    void addInput(bool pushButton, bool record, bool clickBot, bool inited);
    void addCheckpoint(bool mark);

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

    int currentPindex = 0;
    int currentRindex = 0;
    int currentIndex = 0;
    int currentFrame = 0;
    int currentOffset = 0;
    std::vector<AmethystFrame> frames;
    std::vector<int> pushes;
    std::vector<AmethystFrame> pushData;
    std::vector<int> releases;
    std::vector<AmethystFrame> releaseData;
    std::vector<int> checkpointFrames;
    std::vector<CheckpointData> checkpoints;
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