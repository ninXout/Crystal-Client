#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[7] = CCLabelBMFont::create("From 0%", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(7, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[7]->setVisible(getVar<bool>("run_from"));
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int from = getPercentage();

        std::string runFrom = "From" + std::to_string(from) + "%";
        if (getVar<bool>("run_from")) {
            labels[7]->setString(runFrom.c_str());
        }
    }
};*/