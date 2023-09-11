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

			editorButton->setID("crystal-edit-button");

			if (menu->getChildrenCount() == 4 && GameManager::get()->getGameVariable("0074")) {
				editorButton->setPosition({-212.25f, 0.0f});
				editorButton->setContentSize({62.0f, 65.0f});

				editorSprite->setScale(0.8f);
				editorSprite->setPosition({31.0f, 32.5f});

				menu->setPosition({325.5f, 130.0f});
				menu->addChild(editorButton);
				menu->updateLayout();
			} else if (menu->getChildrenCount() == 3) {
				editorButton->setPosition({-175.0f, 0.0f});
				editorButton->setContentSize({62.0f, 65.0f});

				editorSprite->setScale(0.8f);
				editorSprite->setPosition({31.0f, 32.5f});

				menu->setPosition({325.5f, 130.0f});
				menu->addChild(editorButton);
				menu->updateLayout();
			}
		}
		return pause;
	}
};