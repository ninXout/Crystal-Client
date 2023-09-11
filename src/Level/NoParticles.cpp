#include "../CrystalProfile.hpp"
#include <Geode/modify/CCParticleSystem.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>

class $modify(CCParticleSystem) {
	auto resumeSystem() {
		if (!getVar<bool>("no_particles")) {
			CCParticleSystem::resumeSystem();
		}
	}
};

class $modify(CCParticleSystemQuad) {
	static CCParticleSystemQuad* create(char const* t) {
		if (getVar<bool>("no_particles")) {
			t = "";
		}

        return CCParticleSystemQuad::create(t);
	}
};