#pragma once

class Amethyst {
    public:
        struct AmethystFrame {
            float xpos;
            float ypos;
            double accel;
        };

        struct CheckpointData {
            float xpos;
            float ypos;
            float rot;
            double accel;
        };

        static std::vector<AmethystFrame> frames;
        static void apply(AmethystFrame frame, bool withxpos);
        static void applyCP(CheckpointData data);
        static AmethystFrame create();
        static CheckpointData store();
};