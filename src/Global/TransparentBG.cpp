#include "../CrystalProfile.hpp"
#include "../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LocalLevelManager.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

class $modify(EditLevelLayer) {
	bool init(GJGameLevel* ed) {
        EditLevelLayer::init(ed);
        
        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level) {
        LevelInfoLayer::init(level);
        
        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);

        return true;
 
    }
};

class $modify(CreatorLayer) {
	virtual bool init() {
        CreatorLayer::init();

        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState state) {
        LeaderboardsLayer::init(state);

        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};

class $modify(LevelSearchLayer) {
	virtual bool init() {
		LevelSearchLayer::init();

        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);
        
        return true;
    }
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* search) {
		LevelBrowserLayer::init(search);

        if (getVar<bool>("transparent_BG")) CrystalClient::get()->addTransparentBG(this);

        return true;
    }
};