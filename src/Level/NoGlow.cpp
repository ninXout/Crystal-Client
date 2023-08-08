#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GameObject.hpp>

class $modify(PlayLayer) {
    void addObject(GameObject* g) {
		if (getVar<bool>("no_glow")) g->m_isGlowDisabled = true;
		PlayLayer::addObject(g);
	}	
};

class $modify(GameObject) {
    virtual void update(float dt) {
		if (getVar<bool>("no_glow")) m_isGlowDisabled = true;
        GameObject::update(dt);
    }
};