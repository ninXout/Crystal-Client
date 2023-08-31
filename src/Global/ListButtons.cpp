#include "../CrystalProfile.hpp"
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/GameLevelManager.hpp>

// Copied from camila314's DemonlistButton mod

class $modify(ModifiedSearchLayer, LevelSearchLayer) {
	virtual bool init() {
		LevelSearchLayer::init();

		if (getVar<bool>("demonlist_button") || getVar<bool>("challengelist_button")) {
			this->getChildByID("filters-title")->removeFromParentAndCleanup(true);

			this->getChildByID("quick-search-title")->removeFromParentAndCleanup(true);

			auto menu = this->getChildByID("quick-search-menu");

			auto mpos = menu->getPosition();
			menu->setPositionY(mpos.y - 17.5);

            auto bg = this->getChildByID("quick-search-bg");

            auto bsize = bg->getContentSize();
		    bg->setContentSize(CCSize(bsize.width, bsize.height + 35.0));
		}

		if (getVar<bool>("demonlist_button")) {
			auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
				return strncmp(lbl->getString(), "Trending", 8) == 0;
			})->getParent()->getParent()->getParent();

			auto button_sprite = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");

			auto demon_button = CCMenuItemSpriteExtra::create(button_sprite, this, menu_selector(ModifiedSearchLayer::onDemonList));
			auto demon_label = CCLabelBMFont::create("Demon List", "bigFont.fnt");
			auto demon_icon = CCSprite::createWithSpriteFrameName("rankIcon_all_001.png");

			demon_button->addChild(demon_label);
			demon_button->addChild(demon_icon);

			demon_label->setScale(0.55);
			demon_label->setPosition(ccp(70, 17));
			demon_icon->setPosition(ccp(140, 16));
			demon_button->setPosition(reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(0))->getPosition() + ccp(0, 35));

			menu->addChild(demon_button);
		} 
		
		if (getVar<bool>("challengelist_button")) {
			auto menu = findFirstChildRecursive<CCLabelBMFont>(this, [](CCLabelBMFont* lbl) {
				return strncmp(lbl->getString(), "Trending", 8) == 0;
			})->getParent()->getParent()->getParent();

			auto button_sprite2 = CCSprite::createWithSpriteFrameName("GJ_longBtn03_001.png");
			
			auto challenge_button = CCMenuItemSpriteExtra::create(button_sprite2, this, menu_selector(ModifiedSearchLayer::onChallengeList));
			auto challenge_label = CCLabelBMFont::create("Challenge List", "bigFont.fnt");
			auto challenge_icon = CCSprite::createWithSpriteFrameName("rankIcon_top100_001.png");

			challenge_button->addChild(challenge_label);
			challenge_button->addChild(challenge_icon);

			challenge_label->setScale(0.45);
			challenge_label->setPosition(ccp(70, 17));
			challenge_icon->setPosition(ccp(145, 16));
			challenge_icon->setScale(0.8);
			challenge_button->setPosition(reinterpret_cast<CCNode*>(menu->getChildren()->objectAtIndex(1))->getPosition() + ccp(0, 35));

			menu->addChild(challenge_button);
		}
		return true;
	}

	void onDemonList(CCObject*) {
		if (getVar<bool>("demonlist_button")) {
			m_searchInput->onClickTrackNode(false);
			auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3141), ""));

			auto s = CCScene::create();
			s->addChild(p);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
		}
	}

	void onChallengeList(CCObject*) {
		if (getVar<bool>("challengelist_button")) {
			m_searchInput->onClickTrackNode(false);
			auto p = LevelBrowserLayer::create(this->getSearchObject(static_cast<SearchType>(3142), ""));

			auto s = CCScene::create();
			s->addChild(p);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, s));
		}
	}
};

class $modify(GameLevelManager) {
	void ProcessHttpRequest(gd::string gdurl, gd::string gdquery, gd::string idk, int type) {
		std::string url(gdurl);
		std::string query(gdquery);

		if (url == "http://www.boomlings.com/database/getGJLevels21.php") {
			auto thing = atoi(query.substr(query.find("page=") + 5).c_str());
			if (query.find("type=3141") != std::string::npos && getVar<bool>("demonlist_button")) {
				url = std::string("http://absolllute.com/api/mega_hack/demonlist/page") + std::to_string(thing) + ".txt";
			} else if (query.find("type=3142") != std::string::npos && getVar<bool>("challengelist_button")) {
				url = std::string("http://absolllute.com/api/mega_hack/challengelist/page") + std::to_string(thing) + ".txt";
			}
		}

		GameLevelManager::ProcessHttpRequest(url, query, idk, type);
	}
};