#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/CCParticleSystem.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>

using namespace CrystalClient;

// TODO: is this really the best way to make this, nosu?

class $modify(CCParticleSystem) {
	auto resumeSystem() {
		if (!getSavedVar<bool>("no_particles")) {
			CCParticleSystem::resumeSystem();
		}
	}
};

class $modify(CCParticleSystemQuad) {
	static CCParticleSystemQuad* create(char const* t) {
		if (getSavedVar<bool>("no_particles")) {
			t = "";
		}

        return CCParticleSystemQuad::create(t);
	}
};