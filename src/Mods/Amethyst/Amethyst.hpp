#pragma once

#include "../../CrystalClient/CrystalClient.hpp"
#include <gdr/gdr.hpp>

using namespace CrystalClient;

namespace Amethyst {
    struct AmethystInput : gdr::Input {
        AmethystInput() = default;

        AmethystInput(int frame, int button, bool player2, bool down)
            : Input(frame, button, player2, down) {}   
    };

    struct AmethystMacro : gdr::Replay<AmethystMacro, AmethystInput> {
        AmethystMacro() : Replay("Amethyst", "2.0") {}
    };

    inline std::vector<uint32_t> checkpoints;
    inline uint32_t frame;

    inline AmethystMacro macro;
}