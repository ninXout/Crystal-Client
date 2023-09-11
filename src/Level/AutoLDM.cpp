#include "../CrystalProfile.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* level) {
		if (getVar<bool>("auto_ldm")) {
			level->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(level);
	}
};

class $modify(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* level) {
		if (getVar<bool>("auto_ldm")) {
			level->m_lowDetailModeToggled = true;
		} 
		return LevelInfoLayer::create(level);
	}
};