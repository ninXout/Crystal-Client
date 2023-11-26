#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace CrystalClient;

bool disableRender = false;
float leftOver = 0.f;

class $modify(CCScheduler) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("CCScheduler::update", 98);
    }

    void update(float dt) {
        float speedhack = this->getTimeScale();
        const float newdt = 1.f / getSavedVar<float>("TPS") / speedhack;

        if (getSavedVar<bool>("TPS_bypass")) {
            disableRender = true;

            const int times = std::min(static_cast<int>((dt + leftOver) / newdt), 100);
            for (int i = 0; i < times; ++i) {
                if (i == times - 1)
                    disableRender = false;
                CCScheduler::update(newdt);
            }
            leftOver += dt - newdt * times;
        } else {
            CCScheduler::update(dt);
            disableRender = false;
        }
    }
};

class $modify(PlayLayer) {
    void updateVisibility() {
        if (!disableRender) PlayLayer::updateVisibility();
    }
};