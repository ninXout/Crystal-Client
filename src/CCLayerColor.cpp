#include "hackpro.hpp"

class $modify(CCLayerColor) {
	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::create(yk);
		}
	}

	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0), f1, f2);
		} else {
			return CCLayerColor::create(yk, f1, f2);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::initWithColor(yk);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0), 0, 0);
		} else {
			return CCLayerColor::initWithColor(yk, f1, f2);
		}
	}
};