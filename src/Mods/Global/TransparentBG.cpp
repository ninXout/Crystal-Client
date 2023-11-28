#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace CrystalClient;

void addTransparentBG(CCNode* layer) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
        
	auto bg = CCSprite::create("GJ_gradientBG.png");
	auto bgSize = bg->getTextureRect().size;
	bg->setAnchorPoint({ 0.0f, 0.0f });
	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
	bg->setPosition({ -5.0f, -5.0f });
	bg->setColor(ccc3(255, 255, 255));
	
	layer->addChild(bg, -2);
}

class $modify(EditLevelLayer) {
	bool init(GJGameLevel* ed) {
        EditLevelLayer::init(ed);
        
        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);

        return true;
    }
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level) {
        LevelInfoLayer::init(level);
        
        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);

        return true;
 
    }
};

class $modify(CreatorLayer) {
	virtual bool init() {
        CreatorLayer::init();

        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);

        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
        LeaderboardsLayer::init(state);

        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);

        return true;
    }
};

class $modify(LevelSearchLayer) {
	virtual bool init() {
		LevelSearchLayer::init();

        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);
        
        return true;
    }
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* search) {
		LevelBrowserLayer::init(search);

        if (getSavedVar<bool>("transparent_BG")) addTransparentBG(this);

        return true;
    }
};