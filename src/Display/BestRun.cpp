#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

int bestStart = 0;
int bestEnd = 0;
int currentStart = 0;
int currentEnd = 0;

int repeats = 0;

/*class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[8] = CCLabelBMFont::create("From 0%", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(8, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[8]->setVisible(getVar<bool>("best_run"));
    }

    void destroyPlayer(PlayerObject* p, GameObject* g) {
        currentEnd = getPercentage();
        PlayLayer::destroyPlayer(p, g);
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        currentStart = getPercentage();
        if ((currentEnd - currentStart) > (bestEnd - bestStart)) {
            repeats = 0;
            bestStart = currentStart;
            bestEnd = currentEnd;
        } else if (currentEnd == bestEnd && currentStart == bestStart) {
            repeats++;
        }

        std::string repeat;
        if (repeats == 0) repeat = "";
        else repeat = " x" + std::to_string(repeats);

        std::string bestRun;
        if (bestStart == 0) bestRun = "Best Run: " + std::to_string(bestEnd) + "%" + repeat;
        else bestRun = "Best Run: " + std::to_string(bestStart) + "-" + std::to_string(bestEnd) + "%" + repeat;
        
        if (getVar<bool>("best_run")) {
            labels[8]->setString(bestRun.c_str());
        }
    }
};*/