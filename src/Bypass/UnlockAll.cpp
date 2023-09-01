#include "../CrystalProfile.hpp"
#include <Geode/modify/GameManager.hpp>

struct UnlockAll : Modify<UnlockAll, GameManager> {
    static void onModify(auto& self) { 
		(void)self.setHookPriority("GameManager::isColorUnlocked", 0x10000);
		(void)self.setHookPriority("GameManager::isIconUnlocked", 0x10000);
	}

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