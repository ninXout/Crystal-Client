#include "../CrystalProfile.hpp"
#include <Geode/modify/CCMotionStreak.hpp>

class $modify(CCMotionStreak) {
	auto resumeStroke() {
		if (!getVar<bool>("no_trail")) {
			CCMotionStreak::resumeStroke();
		}
	}

	auto stopStroke() {
		if (!getVar<bool>("always_trail")) {
			CCMotionStreak::stopStroke();
		}
	}
};