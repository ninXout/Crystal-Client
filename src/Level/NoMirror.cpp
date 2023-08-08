#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void toggleFlipped(bool one, bool two) {
		if (!getVar<bool>("no_mirror")) PlayLayer::toggleFlipped(one, two);
	}
};