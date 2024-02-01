#include <Geode/modify/GameManager.hpp>
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