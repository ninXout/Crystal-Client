#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void updateAttempts() {
        if (!getSavedVar<bool>("freeze_attempts")) {
			PlayLayer::updateAttempts();
		}
    }
};