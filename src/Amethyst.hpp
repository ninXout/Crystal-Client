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
                mbo(double, player, 0x760) = accel;
                player->setPositionX(xpos);
                player->setPositionX(ypos);
            }
        };

        struct CheckpointData {
            //float xpos;
            //float ypos;
            float rot;
            double accel;
            void apply(PlayerObject* player) {
                //mbo(float, player, 0x7c8) = xpos;
                //mbo(float, player, 0x7cc) = ypos;
                mbo(double, player, 0x760) = accel;
                //player->setPositionX(xpos);
                //player->setPositionX(ypos);
                player->setRotation(rot);
            }
        };

        static std::vector<AmethystFrame> frames;
        static AmethystFrame create();
        static CheckpointData store();
};