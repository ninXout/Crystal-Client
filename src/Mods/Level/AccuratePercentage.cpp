#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "../../Utilities/utilities.hpp"

using namespace CrystalClient;

class $modify(PlayLayer) {
    void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		if (getSavedVar<bool>("acc_percentage")) {
            int decimals = 2;

            if (getSavedVar<int>("acc_percentage_decimals") > 30) decimals = 30;
            else decimals = getSavedVar<int>("acc_percentage_decimals");

			char str[64];
            std::string format = "%." + std::to_string(decimals) + "lf%%";
			sprintf(str, format.c_str(), getPercentage());
			m_percentLabel->setString(str);
		}
	}
};