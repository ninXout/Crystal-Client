#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace CrystalClient;

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
        if (getSavedVar<bool>("copy_hack")) g->m_password = 1;

		auto layer = LevelInfoLayer::create(g);

		return layer;
	}
};