#pragma once

#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

struct AmethystAction {
    bool player1;
    int frame; // total dt * 240 (until i introduce bypass)
    int button;
    bool pressed;
};

namespace Amethyst {
    inline std::vector<AmethystAction> actions;
    inline std::vector<float> checkpoints;
    inline float totalDT;
}