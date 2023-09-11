#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool shouldQuit = false;

class $modify(PlayLayer) {
    void onQuit() {
        if (!shouldQuit && getVar<bool>("confirm_quit") && !m_hasLevelCompleteMenu && getTempVar<bool>("should_popup")) {
			geode::createQuickPopup(
				"Confirm Quit",
				"Are you sure you would like to Quit?",
				"Cancel", "Quit",
				[this](auto, bool btn2) {
					if (btn2) {
                        shouldQuit = true;
						PlayLayer::onQuit();
					}
				}
			);
		} else if (getVar<bool>("load_from_last_CP") && getTempVar<bool>("should_quit")) {
			PlayLayer::onQuit();
		} else if (!getVar<bool>("load_from_last_CP")) {
			PlayLayer::onQuit();
		}
		
        shouldQuit = false;
    }
};