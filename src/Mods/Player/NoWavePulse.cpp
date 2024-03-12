#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/HardStreak.hpp>

using namespace CrystalClient;

class $modify(HardStreak) {
	void updateStroke(float f) {
		//if (getSavedVar<bool>("no_wave_pulse")) m_pulseSize = getSavedVar<float>("wave_size");
		HardStreak::updateStroke(f);
	}
};