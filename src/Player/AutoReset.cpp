#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		float percent = (m_player1->getPositionX() / m_levelLength) * 100;
		if (((float)percent == getVar<float>("auto_reset_num")) && getVar<bool>("auto_reset")) {
			resetLevel();
		}
    }
};
