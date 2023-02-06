#include "hackpro.hpp"

class $modify(CCScheduler) {
	void update(float f3) {
		if (applybypass) {
			cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.0 / bypass);
		}
		//if (!classicspeed) CCScheduler::update(f3 * speedhack);
		CCScheduler::update(f3);
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
		}
	}
};