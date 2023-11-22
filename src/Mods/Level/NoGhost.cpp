#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void toggleGhostEffect(int id) {
        if (!getSavedVar<bool>("no_ghost")) {
        	PlayLayer::toggleGhostEffect(id);
		}
    }
};