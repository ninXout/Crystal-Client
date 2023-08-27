#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>

float leftOver = 0.f;
bool disableRender;

class $modify(CCScheduler) {
    void update(float dt) {
        if (!PlayLayer::get()) return CCScheduler::update(dt);
        if (!getTempVar<bool>("gameStarted")) return CCScheduler::update(dt);

        float targetDT;
        float speedhack = this->getTimeScale();

        if (getVar<bool>("AT_record") || getVar<bool>("AT_replay")) targetDT = 1.f / getVar<float>("FPS") / speedhack;
        else targetDT = (1.f / getVar<float>("FPS")) * speedhack;

        if (getVar<bool>("FPS_bypass") || getVar<bool>("AT_record") || getVar<bool>("AT_replay")) {
            disableRender = true;

            CCApplication::sharedApplication()->setAnimationInterval(targetDT);

            const int times = std::min(static_cast<int>((dt + leftOver) / targetDT), 150);

            for (int i = 0; i < times; i++) {
                if (i == times - 1) {
                    disableRender = false;
                }
                CCScheduler::update(targetDT);
            }
            leftOver += dt - targetDT * times;
        } else {
            CCScheduler::update(dt);
        }
    }
};

class $modify(PlayLayer) {
    void updateVisibility() {
		if (!disableRender) PlayLayer::updateVisibility();
	}
};