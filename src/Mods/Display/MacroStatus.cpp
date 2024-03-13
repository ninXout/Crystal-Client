#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(ATPlayLayer, PlayLayer) {
    bool init(GJGameLevel* gj, bool p1, bool p2) {
        Display::setDefaultDisplay(12, "Not using Amethyst");

        if (!PlayLayer::init(gj, p1, p2)) return false;

        Display::updateDisplay(12);
        Display::addDisplayChildren(12, this);

        this->schedule(schedule_selector(ATPlayLayer::updateMacroStatus));
        return true;
    }

    void updateMacroStatus(float dt) {
        std::string status;
        if (getSavedVar<bool>("macro_status")) {
            if (getSavedVar<bool>("AT_replay") && !getSavedVar<bool>("AT_render")) {
                status = "Playing: " + std::to_string(getTempVar<int>("current-ATstatus-index")) + "/" + std::to_string(getTempVar<int>("current-ATstatus-size")) + " (Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame")) + ")";
                Display::getDisplay(12)->setString(status.c_str());
            } else if (getSavedVar<bool>("AT_record")) {
                status = "Recording: Macro Frame " + std::to_string(getTempVar<int>("current-ATstatus-frame"));
                Display::getDisplay(12)->setString(status.c_str());
            } else if (getSavedVar<bool>("AT_replay") && getSavedVar<bool>("AT_render")) {
                status = "Rendering: Video Frame " + std::to_string((int)(getTempVar<float>("frames") * 60));
                Display::getDisplay(12)->setString(status.c_str());
            } else {
                Display::getDisplay(12)->setString("Not using Amethyst");
            }
        }
    }
};