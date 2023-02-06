#include "hackpro.hpp"

class $modify(PauseLayer) {
	void keyDown(cocos2d::enumKeyCodes key) {
		if (key == KEY_Escape) {
			if (!playerBools[18]) {
				PauseLayer::keyDown(key);
			}
		} else {
			PauseLayer::keyDown(key);
		}
	}
};