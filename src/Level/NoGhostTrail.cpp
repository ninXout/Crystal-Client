#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void toggleGhostEffect(int id) {
        if (!getVar<bool>("no_ghost")) {
        	PlayLayer::toggleGhostEffect(id);
		}
    }
};