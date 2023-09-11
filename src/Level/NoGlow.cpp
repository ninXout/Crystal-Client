#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GameObject.hpp>

class $modify(PlayLayer) {
    void addObject(GameObject* g) {
		if (getVar<bool>("no_glow")) g->m_isGlowDisabled = true;
		PlayLayer::addObject(g);
	}	
};