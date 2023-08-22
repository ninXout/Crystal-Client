#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool isCheating() {
    return (getVar<bool>("noclip") || getVar<float>("speed") < 1 || getVar<bool>("no_mirror") || getVar<bool>("framestep") || getVar<bool>("autoclicker") || getVar<bool>("layout_mode") || getVar<bool>("AT_record") || getVar<bool>("AT_replay") || getVar<float>("FPS") > 360.0 || getVar<float>("TPS") > 360.0);
}
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[0] = CCLabelBMFont::create(".", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(0, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[0]->setVisible(getVar<bool>("cheat_indicator"));

        if (getVar<bool>("cheat_indicator")) {
            labels[0]->setColor(isCheating() ? ccc3(255, 0, 0) : ccc3(0, 255, 0));
        }
    }
};*/