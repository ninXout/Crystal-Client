#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PauseLayer.hpp>

using namespace CrystalClient;

class $modify(MyPauseLayer, PauseLayer) {
	static PauseLayer* create(bool isPaused) {
		auto pause = PauseLayer::create(isPaused);
		if (getSavedVar<bool>("platformer_practice")) {
			auto editorSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
			auto menu = static_cast<CCMenu*>(pause->getChildByID("center-button-menu"));
			auto editorButton = CCMenuItemSpriteExtra::create(editorSprite, pause, menu_selector(MyPauseLayer::practiceMode));

			editorButton->setID("platformer-practice"_spr);

			if (menu->getChildrenCount() == 4 && PlayLayer::get()->m_player1->m_isPlatformer) {
				editorButton->setPosition({-200.25f, 0.0f});
				editorButton->setContentSize({62.0f, 65.0f});

				editorSprite->setPosition({31.0f, 32.5f});

				menu->setPosition({325.5f, 130.0f});
				menu->addChild(editorButton);
				menu->updateLayout();
			}
		}
		return pause;
	}

	void practiceMode(CCObject*) {
		PlayLayer::get()->togglePracticeMode(!PlayLayer::get()->m_isPracticeMode);
	}
};