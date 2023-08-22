#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

int clicks = 0;
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[2] = CCLabelBMFont::create("0/0", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(2, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        int cps = clicks / ((int)m_time * 60);

        labels[2]->setVisible(getVar<bool>("cps_display"));

        if (getVar<bool>("cps_display")) {
            labels[2]->setString(std::to_string(cps).c_str());
        }
    }
};

class $modify(GJBaseGameLayer) {
    void pushButton(int i, bool b) {
        GJBaseGameLayer::pushButton(i, b);

        clicks++;
    }
};*/