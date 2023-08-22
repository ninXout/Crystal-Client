#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

// Copied from mateus44/Matcool's FPS Bypass mod

double m_resetInterval;
std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
float frame_time_sum = 0.f;
int frame_count = 0;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(3, "60");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(3);
        Display::get()->addDisplayChildren(3, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        Display::get()->updateDisplay(3);

        const auto now = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<float> diff = now - previous_frame;
        frame_time_sum += diff.count();
        frame_count++;

        int fps;

        if (std::chrono::duration<float>(now - last_update).count() > 1.0f) {
            last_update = now;
            fps = static_cast<int>(std::roundf(static_cast<float>(frame_count) / frame_time_sum));
            frame_time_sum = 0.f;
            frame_count = 0;
        }

        previous_frame = now;

        if (getVar<bool>("fps_display")) Display::get()->getDisplay(3)->setString((std::to_string(fps)).c_str());
    }
};