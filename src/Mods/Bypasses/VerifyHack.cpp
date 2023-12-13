#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

using namespace CrystalClient;

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* gl) {
		if (getSavedVar<bool>("verify")) gl->m_isVerified = true;
		return EditLevelLayer::create(gl);
	}
};