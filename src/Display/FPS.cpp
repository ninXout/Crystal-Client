#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

// Copied from mateus44/Matcool's FPS Bypass mod

double m_resetInterval;
std::chrono::time_point<std::chrono::high_resolution_clock> previous_frame, last_update;
float frame_time_sum = 0.f;
int frame_count = 0;
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[3] = CCLabelBMFont::create("60", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(3, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

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

        labels[3]->setVisible(getVar<bool>("fps_display"));

        if (getVar<bool>("fps_display")) {
            labels[3]->setString((std::to_string(fps)).c_str());
        }
    }
};*/