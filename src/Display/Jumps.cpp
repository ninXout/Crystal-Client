#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[6] = CCLabelBMFont::create("0 Jumps", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(6, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[6]->setVisible(getVar<bool>("jumps"));

        int jump;

        if (getVar<bool>("total_jumps")) jump = m_level->m_jumps;
        else jump = m_attemptJumpCount;

        std::string jumps = std::to_string(jump) + " Jumps";
        if (getVar<bool>("jumps")) {
            labels[6]->setString(jumps.c_str());
        }
    }
};*/