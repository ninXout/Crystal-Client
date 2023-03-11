#pragma once

class Amethyst {
    public:
        struct AmethystFrame {
            float xpos;
            float ypos;
            double accel;
        };

        static std::vector<AmethystFrame> frames;
        static void apply(AmethystFrame frame, bool withxpos);
        static AmethystFrame create();
};