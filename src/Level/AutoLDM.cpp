#include "../CrystalProfile.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (getVar<bool>("auto_ldm")) {
			ok->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(ok);
	}
};