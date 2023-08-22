#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[13] = CCLabelBMFont::create("00:00:00", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(13, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[13]->setVisible(getVar<bool>("clock"));

        auto t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        auto clstr = oss.str();

        if (getVar<bool>("clock")) {
            labels[13]->setString(clstr.c_str());
        }
    }
};*/