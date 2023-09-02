#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>

float leftOver = 0.f;
bool disableRender;

class $modify(CCScheduler) {
    void update(float dt) {
        if (!PlayLayer::get()) return CCScheduler::update(dt);
        if (!getTempVar<bool>("gameStarted")) return CCScheduler::update(dt);

        float unfocusedDT;
        float speedhack = this->getTimeScale();

        if (getVar<bool>("AT_record") || getVar<bool>("AT_replay")) {
            *setTempVar<float>("target_DT") = 1.f / getVar<float>("FPS") / speedhack;
            unfocusedDT = (1.f / getVar<float>("FPS_unfocused")) / speedhack;
        } else {
            *setTempVar<float>("target_DT") = (1.f / getVar<float>("FPS")) * speedhack;
            unfocusedDT = (1.f / getVar<float>("FPS_unfocused")) * speedhack;
        }

        if (getVar<bool>("Unfocused_FPS") && getTempVar<bool>("should_unfocus_fps")) {
            CCApplication::sharedApplication()->setAnimationInterval(unfocusedDT);
            CCScheduler::update(unfocusedDT);
        } else if (getVar<bool>("FPS_bypass") || getVar<bool>("AT_record") || getVar<bool>("AT_replay")) {
            disableRender = true;

            const int times = std::min(static_cast<int>((dt + leftOver) / getTempVar<float>("target_DT")), 150);

            for (int i = 0; i < times; i++) {
                if (i == times - 1) {
                    disableRender = false;
                }
                CCScheduler::update(getTempVar<float>("target_DT"));
            }
            leftOver += dt - getTempVar<float>("target_DT") * times;
        } else {
            CCScheduler::update(dt);
        }
    }
};

class $modify(PlayLayer) {
    void updateVisibility() {
		if (!disableRender) PlayLayer::updateVisibility();
	}

    void startGame() {
        PlayLayer::startGame();
        CCApplication::sharedApplication()->setAnimationInterval(getTempVar<float>("target_DT"));
    }
};