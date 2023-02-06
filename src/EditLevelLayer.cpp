#include "hackpro.hpp"

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (bypassBools[5]) {
			ok->m_isVerifiedRand = 11;
			ok->m_isVerifiedSeed = 10;
		}	
		if (playerBools[20]) {
			ok->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(ok);
	}
};