#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

bool shouldQuit = false;

class $modify(PlayLayer) {
    void onQuit() {
        if (!shouldQuit && getSavedVar<bool>("confirm_quit") && !m_hasLevelCompleteMenu) {
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
		}
        
        if (shouldQuit) {
			PlayLayer::onQuit();
		}
		
        shouldQuit = false;
    }
};