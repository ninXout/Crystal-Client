#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[12] = CCLabelBMFont::create("Not using Amethyst", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(12, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[12]->setVisible(getVar<bool>("macro_status"));

        std::string status;
        if (getVar<bool>("macro_status")) {
            if (getVar<bool>("AT_replay") && !getVar<bool>("AT_render")) {
                //status = "Playing: " + std::to_string(currentP1index) + "/" + std::to_string(P1pushes.size()) + " (Frame " + std::to_string((int)(m_time * profile.TPS)) + ")";
                //labels[12]->setString(status.c_str());
            } else if (getVar<bool>("AT_record")) {
                status = "Recording: Macro Frame " + std::to_string((int)(m_time * getVar<float>("TPS")));
                labels[12]->setString(status.c_str());
            } else if (getVar<bool>("AT_replay") && getVar<bool>("AT_render")) {
                status = "Rendering: Video Frame " + std::to_string((int)(m_time * 60));
                labels[12]->setString(status.c_str());
            } else {
                labels[12]->setString("Not using Amethyst");
            }
        }
    }
};*/