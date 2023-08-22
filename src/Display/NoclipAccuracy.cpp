#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[9] = CCLabelBMFont::create("100%", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(9, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[9]->setVisible(getVar<bool>("noclip_accuracy"));

        char accString[20];
        float accuracy = ((float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames")) * 100;

        if (getTempVar<bool>("would_die") && getVar<bool>("red_on_accuracy")) labels[9]->setColor(ccc3(255, 0, 0));
        else labels[9]->setColor(ccc3(255, 255, 255));

        sprintf(accString, "%.2f%%", accuracy);
        if (getVar<bool>("noclip_accuracy")) {
            labels[9]->setString(accString);
        }
    }
};*/