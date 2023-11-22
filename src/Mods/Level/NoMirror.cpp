#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void toggleFlipped(bool one, bool two) {
		if (!getSavedVar<bool>("no_mirror")) PlayLayer::toggleFlipped(one, two);
	}
};