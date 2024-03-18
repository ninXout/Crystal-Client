#include <Geode/modify/CCScheduler.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

float leftOver = 0.f;

class $modify(CCScheduler) {
    void update(float dt) {
		CCScheduler::update(dt * (getSavedVar<bool>("speedhack") ? getSavedVar<float>("speed") : 1.f));
    }
};