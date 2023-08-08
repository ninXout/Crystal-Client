#include "../CrystalProfile.hpp"
#include <Geode/modify/HardStreak.hpp>

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (getVar<bool>("no_wave_pulse")) m_pulseSize = getVar<float>("wave_size");
		HardStreak::updateStroke(f);
	}
};