#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/EndLevelLayer.hpp>

CCLayer* endLayer;

struct LoadFromLastCP : Modify<LoadFromLastCP, EndLevelLayer> {
	void onLastCP(CCObject* sender) {
		*setTempVar<bool>("should_quit") = false;
		endLayer->keyBackClicked();
		if (PlayLayer::get()->m_checkpoints != nullptr) {
		#ifdef GEODE_IS_MACOS
			PlayLayer::get()->loadLastCheckpoint();
		#else
			// geode itself should define this function imo..
			auto* pl = PlayLayer::get();
			if (pl->m_checkpoints->count()) {
				pl->loadFromCheckpoint(static_cast<CheckpointObject*>(pl->m_checkpoints->lastObject()));
			}
		#endif
		}
		PlayLayer::get()->resetLevel();
	}

	static EndLevelLayer* create() {
		auto end = EndLevelLayer::create();
		if (getVar<bool>("load_from_last_CP") && PlayLayer::get()->m_isPracticeMode) {
			auto layer = static_cast<CCLayer*>(end->getChildren()->objectAtIndex(0));
        	auto menu = static_cast<CCMenu*>(layer->getChildren()->objectAtIndex(9));
			auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
			auto button = CCMenuItemSpriteExtra::create(buttonSprite, end, menu_selector(LoadFromLastCP::onLastCP));

			*setTempVar<bool>("should_popup") = false;
			*setTempVar<bool>("should_quit") = true;
			endLayer = end;
			PlayLayer::get()->m_checkpoints->retain();
			button->setID("GH_load-last-cp");

			if (menu->getChildrenCount() == 2) {
				button->setPositionY(-125.0f);
				menu->addChild(button);

			} else if (menu->getChildrenCount() == 3) {
				auto layout = RowLayout::create();
				layout->setAxisAlignment(AxisAlignment::Center);
				layout->setAutoScale(true);
				layout->setAxisReverse(true);
				layout->setGap(17.0f);

				menu->setPositionY(34.0f);
				menu->setLayout(layout);
				menu->addChild(button);
				menu->updateLayout(true);
			}
		}

		return end;
	}
};

class $modify(PlayLayer) {
	void resetLevel() {
		PlayLayer::resetLevel();

		*setTempVar<bool>("should_popup") = true;
		*setTempVar<bool>("should_quit") = true;
	}

	virtual void update(float dt) {
		PlayLayer::update(dt);

		m_checkpoints->retain();
	}

	void onQuit() {
		if ((getVar<bool>("load_from_last_CP") && getTempVar<bool>("should_quit")) || !getVar<bool>("load_from_last_CP")) {
			PlayLayer::onQuit();
		}
	}
};