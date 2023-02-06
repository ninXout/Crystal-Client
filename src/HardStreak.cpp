#include "hackpro.hpp"

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (playerBools[14]) m_pulseSize = pulse;
		if (playerBools[28]) m_isSolid = true;
		if (playerBools[4] && PlayLayer::get()) this->setColor(col);
		if (playerBools[28]) this->setBlendFunc(getBlendFunc());
		HardStreak::updateStroke(f);
	}
};