#include "HidePause.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		thelayer = PauseLayer::create(isPaused);
		if (getVar<bool>("hide_pause")) thelayer->setVisible(false);
		return thelayer;
	}
};

class $modify(PlayLayer) {
	bool init(GJGameLevel* gj) {
		*setTempVar<bool>("is-paused") = false;
		if (!PlayLayer::init(gj)) return false;
		return true;
	}

	void pauseGame(bool uh) {
		PlayLayer::pauseGame(uh);
		*setTempVar<bool>("is-paused") = true;
	}

	void resume() {
		PlayLayer::resume();
		*setTempVar<bool>("is-paused") = false;
	}
};