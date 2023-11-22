#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void addObject(GameObject* g) {
		if (getSavedVar<bool>("no_glow")) g->m_isGlowDisabled = true;
		PlayLayer::addObject(g);
	}	
};