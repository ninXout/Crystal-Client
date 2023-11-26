#include "../../CrystalClient/CrystalClient.hpp"
#include "../../Utilities/utilities.hpp"
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

bool shouldNotSaveWithBenefits() {
    if (getSavedVar<bool>("auto_safe_mode") && shouldNotSave()) return true;
    if (getSavedVar<bool>("safe_mode")) return true;
    return false;
}

class $modify(GJGameLevel) {
	void savePercentage(int percentage, bool practice, int clicks, int attemptTime, bool vfDChk) {
		if (shouldNotSaveWithBenefits()) return;
		return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, vfDChk);
	}
};

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* po, GameObject* go) {
        auto testMode = m_isTestMode;

        if (shouldNotSaveWithBenefits()) m_isTestMode = true;
        PlayLayer::destroyPlayer(po, go);

        m_isTestMode = testMode;
    }

    void levelComplete() {
        auto testMode = m_isTestMode;

        if (shouldNotSaveWithBenefits()) m_isTestMode = true;
        PlayLayer::levelComplete();

        m_isTestMode = testMode;
    }
};