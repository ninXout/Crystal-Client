#include "../CrystalProfile.hpp"
#include <Geode/modify/PauseLayer.hpp>

class $modify(PauseLayer) {
    void keyDown(cocos2d::enumKeyCodes key) {
		if (key != KEY_Escape || (key == KEY_Escape && !getVar<bool>("ignore_esc"))) {
			PauseLayer::keyDown(key);
		}
	}
};