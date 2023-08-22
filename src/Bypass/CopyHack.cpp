#include "../CrystalProfile.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		auto layer = LevelInfoLayer::create(g);
		if (getVar<bool>("copy_hack")) g->m_password = 1;

		return layer;
	}
};