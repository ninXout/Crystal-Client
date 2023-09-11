#include "../CrystalProfile.hpp"
#include <Geode/modify/GameManager.hpp>

struct UnlockAll : Modify<UnlockAll, GameManager> {
    static void onModify(auto& self) { 
		(void)self.setHookPriority("GameManager::isColorUnlocked", 1);
		(void)self.setHookPriority("GameManager::isIconUnlocked", 1);
	}

    bool isIconUnlocked(int a, IconType b) {
        auto icon = GameManager::isIconUnlocked(a,b);
        if (getVar<bool>("unlock_all")) {
            return true;
        } else {
            return icon;
        }
    } 

    bool isColorUnlocked(int a, bool b) {
        auto color = GameManager::isColorUnlocked(a,b);
        if (getVar<bool>("unlock_all")) {
            return true;
        } else {
            return color;
        }
    }
};