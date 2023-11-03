#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		double percent = (m_player1->getPositionX() / m_levelLength) * 100;
		if (((float)percent >= getSavedVar<float>("auto_reset_num")) && getSavedVar<bool>("auto_reset")) {
			if (getSavedVar<bool>("reset_instead")) resetLevel();
            else destroyPlayer(m_player1, nullptr);
		}
    }
};