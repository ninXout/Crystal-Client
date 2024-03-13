#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include "Display.hpp"

#include <time.h>   // clock
#include <stdio.h>  // snprintf

// Half copied from camila314 and alk1m123's FPS Shower mod

float lastTime;

int frames;
float accumulate;
double resetInterval;

int FPSframes;
float FPSaccumulate;
float FPSframerate = 0.f;

class $modify(CCScheduler) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("CCScheduler::update", 99);
    }

    void update(float dt) {
        CCScheduler::update(dt);

        ++FPSframes;
        FPSaccumulate += dt;

        if (FPSaccumulate > resetInterval) {
            FPSframerate = FPSframes / FPSaccumulate;
            FPSframerate = round(FPSframerate * 10) / 10;
            FPSframes = 0;
            FPSaccumulate = 0;
        }
    }
};

class $modify(FPSPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(3, "60/60 FPS/TPS");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(3);
        Display::addDisplayChildren(3, this);

        this->schedule(schedule_selector(FPSPlayLayer::updateFPS));
        return true;
    }

    void updateFPS(float dt) {
        ++frames;
        accumulate += dt;

        if (accumulate > resetInterval) {
            float framerate = frames / accumulate;
            framerate = round(framerate * 10) / 10;
            frames = 0;
            accumulate = 0;

            std::string FPSstring = std::to_string(static_cast<int>(FPSframerate)) + "/" + std::to_string(static_cast<int>(framerate)) + " FPS/TPS";

            if (getSavedVar<bool>("fps_display") && lastTime != static_cast<int>(getTempVar<float>("frames"))) {
                Display::getDisplay(3)->setString(FPSstring.c_str());
                lastTime = static_cast<int>(getTempVar<float>("frames"));
            }
        }
    }
};