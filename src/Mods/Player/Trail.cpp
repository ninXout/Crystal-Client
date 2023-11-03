#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/CCMotionStreak.hpp>

using namespace CrystalClient;

class $modify(CCMotionStreak) {
	auto resumeStroke() {
		if (!getSavedVar<bool>("no_trail")) {
			CCMotionStreak::resumeStroke();
		}
	}

	auto stopStroke() {
		if (!getSavedVar<bool>("always_trail")) {
			CCMotionStreak::stopStroke();
		}
	}
};