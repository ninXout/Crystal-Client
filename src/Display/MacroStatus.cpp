#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(12, "Not using Amethyst");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(12);
        Display::get()->addDisplayChildren(12, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        std::string status;
        if (getVar<bool>("macro_status")) {
            if (getVar<bool>("AT_replay") && !getVar<bool>("AT_render")) {
                status = "Playing: " + std::to_string(getTempVar<int>("current-ATstatus-index")) + "/" + std::to_string(getTempVar<int>("current-ATstatus-size")) + " (Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame")) + ")";
                Display::get()->getDisplay(12)->setString(status.c_str());
            } else if (getVar<bool>("AT_record")) {
                status = "Recording: Macro Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame"));
                Display::get()->getDisplay(12)->setString(status.c_str());
            } else if (getVar<bool>("AT_replay") && getVar<bool>("AT_render")) {
                status = "Rendering: Video Frame " + std::to_string((int)(m_time * 60));
                Display::get()->getDisplay(12)->setString(status.c_str());
            } else {
                Display::get()->getDisplay(12)->setString("Not using Amethyst");
            }
        }
    }
};