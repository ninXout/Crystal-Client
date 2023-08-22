#include "../CrystalProfile.hpp"
#include <Geode/modify/GameManager.hpp>

class $modify(GameManager) {
    bool isIconUnlocked(int a, IconType b) {
        auto icon = GameManager::isIconUnlocked(a,b);
        if (setVar<bool>("unlock_all")) {
            return true;
        } else {
            return icon;
        }
    } 

    bool isColorUnlocked(int a, bool b) {
        auto color = GameManager::isColorUnlocked(a,b);
        if (setVar<bool>("unlock_all")) {
            return true;
        } else {
            return color;
        }
    }
};