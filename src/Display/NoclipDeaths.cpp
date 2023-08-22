#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[10] = CCLabelBMFont::create("0 Deaths", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(10, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[10]->setVisible(getVar<bool>("noclip_deaths"));

        if (getTempVar<bool>("would_die") && getVar<bool>("red_on_death")) labels[10]->setColor(ccc3(255, 0, 0));
        else labels[10]->setColor(ccc3(255, 255, 255));

        std::string noclipDeaths = std::to_string(getTempVar<int>("noclip_deaths")) + " Deaths";
        if (getVar<bool>("noclip_deaths")) {
            labels[10]->setString(noclipDeaths.c_str());
        }
    }
};*/