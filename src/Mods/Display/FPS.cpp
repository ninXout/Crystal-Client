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

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(3, "60/60 FPS/TPS");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(3);
        Display::addDisplayChildren(3, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        ++frames;
        accumulate += dt;

        if (accumulate > resetInterval) {
            float framerate = frames / accumulate;
            framerate = round(framerate * 10) / 10;
            frames = 0;
            accumulate = 0;

            std::string FPSstring = std::to_string(static_cast<int>(FPSframerate)) + "/" + std::to_string(static_cast<int>(framerate)) + " FPS/TPS";

            if (getSavedVar<bool>("fps_display") && lastTime != static_cast<int>(m_time)) {
                Display::getDisplay(3)->setString(FPSstring.c_str());
                lastTime = static_cast<int>(m_time);
            }
        }
    }
};