#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

// Copied from camila314 and alk1m123's FPS Shower mod

int frames;
double accumulate;
double resetInterval;
int lastTime;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(3, "60");

        if (!PlayLayer::init(gj)) return false;

        frames = accumulate = resetInterval = lastTime = 0;

        Display::get()->arrangeDisplay(3);
        Display::get()->addDisplayChildren(3, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(3);

        ++frames;
        accumulate += dt;

        if (accumulate > resetInterval) {
            float framerate = frames / accumulate;
            framerate = round(framerate * 10) / 10;
            frames = 0;
            accumulate = 0;

            std::string FPSstring = std::to_string(static_cast<int>(framerate));

            if (getVar<bool>("fps_display") && lastTime != static_cast<int>(m_time)) {
                Display::get()->getDisplay(3)->setString(FPSstring.c_str());
                lastTime = static_cast<int>(m_time);
            }
        }
    }
};