#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/CCLayerColor.hpp>

using namespace CrystalClient;

class $modify(CCLayerColor) {
	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (getSavedVar<bool>("transparent_lists")) return CCLayerColor::initWithColor(ccc4(0, 0, 0, 0), 0, 0);
		return CCLayerColor::initWithColor(yk, f1, f2);
	}
};