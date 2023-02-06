#include "hackpro.hpp"

class $(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		if (bypassBools[6]) {
			g->m_passwordSeed = 20; // it can be anything
			g->m_passwordRand = g->m_passwordSeed + 1;
		}

		if (playerBools[20]) {
			g->m_lowDetailModeToggled = true;
		}
		
		//getNONGs();
		//findsong = std::to_string(level->m_songID);

		return LevelInfoLayer::create(g);
	}
};