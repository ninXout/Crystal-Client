#include "../CrystalProfile.hpp"
#include "../Display/Display.hpp"
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/PlayLayer.hpp>

bool shouldNotSave() {
    return ((getVar<bool>("safe_mode") && !getVar<bool>("auto_safe_mode")) || (getVar<bool>("safe_mode") && getVar<bool>("auto_safe_mode") && Display::get()->getDisplay(0)->getColor() == ccc3(255,0,0)));
}

class $modify(GJGameLevel) {
	void savePercentage(int percentage, bool practice, int clicks, int attemptTime, bool vfDChk) {
		if (shouldNotSave()) return;
		return GJGameLevel::savePercentage(percentage, practice, clicks, attemptTime, vfDChk);
	}
};

class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* po, GameObject* go) {
        auto testMode = m_isTestMode;

        if (shouldNotSave()) m_isTestMode = true;
        PlayLayer::destroyPlayer(po, go);

        m_isTestMode = testMode;
    }

    void levelComplete() {
        auto testMode = m_isTestMode;

        if (shouldNotSave()) m_isTestMode = true;
        PlayLayer::levelComplete();

        m_isTestMode = testMode;
    }
};