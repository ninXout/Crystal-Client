#include "hackpro.hpp"

class $modify(GJGameLevel) {
	void savePercentage(int i, bool b, int i2, int i3, bool b2) {
		if (!safe) {
			GJGameLevel::savePercentage(i, b, i2, i3, true);
		}
		if (uncomplete) {
			GJGameLevel::savePercentage(0, false, 0, 0, true);
		}
	}
};