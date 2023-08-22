#include "../CrystalProfile.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (getVar<bool>("verify")) ok->m_isVerified = true;
		return EditLevelLayer::create(ok);
	}
};