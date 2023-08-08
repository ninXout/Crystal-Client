#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		if (getVar<bool>("acc_percentage")) {
			double percent = (m_player1->getPositionX() / m_levelLength) * 100;
			if (percent > 100.00) percent = 100.00;
            if (percent < 0.00) percent = 0.00;
			char str[64];
            std::string format = "%." + std::to_string(getVar<int>("acc_percentage_decimals")) + "lf%%";
			sprintf(str, format.c_str(), percent);
			m_percentLabel->setString(str);
		}
	}
};