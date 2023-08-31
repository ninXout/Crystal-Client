#include "../CrystalProfile.hpp"
#include <Geode/modify/AppDelegate.hpp>

bool willEnterBackground = false; // No Pause on Unfocus
bool shouldMute = false; // Mute on Unfocus

struct Unfocus : Modify<Unfocus, AppDelegate> {
	static void onModify(auto& self) { 
		(void)self.setHookPriority("AppDelegate::applicationWillResignActive", 0x10000);
		(void)self.setHookPriority("AppDelegate::applicationWillBecomeActive", 0x10000);
		(void)self.setHookPriority("AppDelegate::pauseGame", 0x10000);
	}

	virtual void applicationWillResignActive() {
		shouldMute = true;
		willEnterBackground = true;
		*setTempVar<bool>("should_unfocus_fps") = true;
		AppDelegate::applicationWillResignActive();
		willEnterBackground = false;
	}

	virtual void applicationWillBecomeActive() {
        shouldMute = false;
		*setTempVar<bool>("should_unfocus_fps") = false;
        AppDelegate::applicationWillBecomeActive();
    }

	void pauseGame() {
		if (!willEnterBackground || !getVar<bool>("no_pause_unfocus")) {
			AppDelegate::pauseGame();
		}

		if (shouldMute && getVar<bool>("mute_unfocus")) {
            GameSoundManager::sharedManager()->stopBackgroundMusic();
        }
	}
};