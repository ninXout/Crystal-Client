#include "../CrystalProfile.hpp"
#include <Geode/modify/LevelTools.hpp>
#include <Geode/modify/PauseLayer.hpp>

class $modify(LevelTools) {
	static bool verifyLevelIntegrity(gd::string mg, int de) {
		if (getVar<bool>("load_failed") || getVar<bool>("level_edit")) return true;
		return LevelTools::verifyLevelIntegrity(mg, de);
	}
};

class $modify(PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (getVar<bool>("level_edit")) {
			auto editorSprite = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
			auto menu = static_cast<CCMenu*>(pause->getChildByID("center-button-menu"));
			auto editorButton = CCMenuItemSpriteExtra::create(editorSprite, pause, menu_selector(PauseLayer::goEdit));

			if (menu->getChildrenCount() != 5) {
				editorButton->setPosition({-212.25f, 0.0f});
				editorButton->setScale(0.8f);
				editorButton->setAnchorPoint({0.5f, 0.5f});

				menu->setPosition({325.0f, 130.0f});
				menu->addChild(editorButton);
				menu->updateLayout();
			}
		}
		return pause;
	}
};