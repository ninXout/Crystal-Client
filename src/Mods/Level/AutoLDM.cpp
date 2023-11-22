#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace CrystalClient;

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* level) {
		if (getSavedVar<bool>("auto_ldm")) {
			level->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(level);
	}
};

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* level) {
		if (getSavedVar<bool>("auto_ldm")) {
			level->m_lowDetailModeToggled = true;
		} 
		return LevelInfoLayer::create(level);
	}
};