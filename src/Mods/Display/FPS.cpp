#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

#include <time.h>   // clock
#include <stdio.h>  // snprintf

// Copied from camila314 and alk1m123's FPS Shower mod

int frames;
double accumulate;
double resetInterval;
int lastTime;

clock_t deltaTime = 0;
unsigned int FPSframes = 0;
double frameRate = 30;
double averageFrameTimeMilliseconds = 33.333;

double clockToMilliseconds(clock_t ticks){
    return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(3, "60/60 FPS/TPS");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(3);
        Display::addDisplayChildren(3, this);
        return true;
    }

    void update(float dt) {
        clock_t beginFrame = clock();

        PlayLayer::update(dt);

        clock_t endFrame = clock();

        deltaTime += endFrame - beginFrame;
        FPSframes++;

        //if you really want FPS
        if (clockToMilliseconds(deltaTime) > 1000.0) {
            frameRate = (double)FPSframes * 0.5 + frameRate * 0.5;
            FPSframes = 0;
            deltaTime -= CLOCKS_PER_SEC;
            averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);
        }

        ++frames;
        accumulate += dt;

        if (accumulate > resetInterval) {
            float framerate = frames / accumulate;
            framerate = round(framerate * 10) / 10;
            frames = 0;
            accumulate = 0;

            std::string FPSstring = std::to_string(frameRate) + "/" + std::to_string(static_cast<int>(framerate)) + " FPS/TPS";

            if (getSavedVar<bool>("fps_display") && lastTime != static_cast<int>(m_time)) {
                Display::getDisplay(3)->setString(FPSstring.c_str());
                lastTime = static_cast<int>(m_time);
            }
        }
    }
};