#include "../CrystalProfile.hpp"
#include <Geode/modify/PauseLayer.hpp>

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (getVar<bool>("hide_pause")) pause->setVisible(false);
		return pause;
	}
};