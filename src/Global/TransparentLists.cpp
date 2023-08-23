#include "../CrystalProfile.hpp"
#include <Geode/modify/CCLayerColor.hpp>

class $modify(CCLayerColor) {
	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (getVar<bool>("transparent_lists")) {
			return CCLayerColor::initWithColor(ccc4(0, 0, 0, 0), 0, 0);
		} else {
			return CCLayerColor::initWithColor(yk, f1, f2);
		} 
	}
};