#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[4] = CCLabelBMFont::create("0/0", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(4, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[4]->setVisible(getVar<bool>("last_death"));
    }

    void resetLevel() {
        double deathPercent = getPercentage();

        PlayLayer::resetLevel();
        std::string lastDeath = std::to_string((int)deathPercent);
        if (getVar<bool>("last_death")) {
            labels[4]->setString(lastDeath.c_str());
        }
    }
};*/