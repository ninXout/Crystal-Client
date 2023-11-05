#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"
#include "../../Utilities/utilities.hpp"

int bestStart = 0;
int bestEnd = 0;
int currentStart = 0;
int currentEnd = 0;

int repeats = 0;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(8, "Best Run: 0%");

        bestStart = bestEnd = currentStart = currentEnd = repeats = 0;

        if (!PlayLayer::init(gj)) return false;

        Display::arrangeDisplay(8);
        Display::addDisplayChildren(8, this);
        return true;
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
        if (repeats <= 1) repeat = "";
        else repeat = " x" + std::to_string(repeats);

        std::string bestRun;
        if (bestStart == 0) bestRun = "Best Run: " + std::to_string(bestEnd) + "%" + repeat;
        else bestRun = "Best Run: " + std::to_string(bestStart) + "-" + std::to_string(bestEnd) + "%" + repeat;
        
        if (getSavedVar<bool>("best_run")) Display::getDisplay(8)->setString(bestRun.c_str());
    }
};