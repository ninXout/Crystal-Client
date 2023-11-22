#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace CrystalClient;

class $modify(PauseLayer) {
    void keyDown(cocos2d::enumKeyCodes key) {
		if (key != KEY_Escape || (key == KEY_Escape && !getSavedVar<bool>("ignore_esc"))) {
			PauseLayer::keyDown(key);
		}
	}
};