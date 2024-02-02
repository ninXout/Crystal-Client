#include <Geode/modify/CCScheduler.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

class $modify(CCScheduler) {
    void update(float dt) {
        CCScheduler::update(getSavedVar<bool>("speedhack") ? (dt * getSavedVar<float>("speed")) : dt);
    }
};