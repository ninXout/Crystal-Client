#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(12, "Not using Amethyst");

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(12);
        Display::addDisplayChildren(12, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        std::string status;
        if (getSavedVar<bool>("macro_status")) {
            if (getSavedVar<bool>("AT_replay") && !getSavedVar<bool>("AT_render")) {
                status = "Playing: " + std::to_string(getTempVar<int>("current-ATstatus-index")) + "/" + std::to_string(getTempVar<int>("current-ATstatus-size")) + " (Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame")) + ")";
                Display::getDisplay(12)->setString(status.c_str());
            } else if (getSavedVar<bool>("AT_record")) {
                status = "Recording: Macro Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame"));
                Display::getDisplay(12)->setString(status.c_str());
            } else if (getSavedVar<bool>("AT_replay") && getSavedVar<bool>("AT_render")) {
                status = "Rendering: Video Frame " + std::to_string((int)(m_time * 60));
                Display::getDisplay(12)->setString(status.c_str());
            } else {
                Display::getDisplay(12)->setString("Not using Amethyst");
            }
        }
    }
};