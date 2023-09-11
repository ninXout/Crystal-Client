#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void updateAttempts() {
        if (!getVar<bool>("freeze_attempts")) {
			PlayLayer::updateAttempts();
		}
    }
};