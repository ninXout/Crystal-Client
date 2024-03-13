#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(GameManager) {
    bool isIconUnlocked(int num, IconType type) {
        if (getSavedVar<bool>("iconhack")) return true;
        return GameManager::isIconUnlocked(num, type);
    }

    bool isColorUnlocked(int num, UnlockType type) {
        if (getSavedVar<bool>("iconhack")) return true;
        return GameManager::isColorUnlocked(num, type);
    }
};

class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int num) {
        if (type == UnlockType::GJItem && num == 17 && getSavedVar<bool>("practice_music")) return true;
        if (getSavedVar<bool>("iconhack")) return true;
        return GameStatsManager::isItemUnlocked(type, num);
    }
};