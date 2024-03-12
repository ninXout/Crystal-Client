#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;

bool lastDeath;
bool dead = false;

float opacity;
CCSprite* noclipRed;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj, bool idk1, bool idk2) {
        *setTempVar<bool>("level_completed") = false; // temporary cuz im lazy

        if (!PlayLayer::init(gj, idk1, idk2)) return false;

        noclipRed = CCSprite::createWithSpriteFrameName("block005b_05_001.png");
		noclipRed->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2});
		noclipRed->setScale(1000.0f);
		noclipRed->setColor(CrystalClient::VarToCC3B("noclipColor"));
		noclipRed->setOpacity(0.f);
		noclipRed->setZOrder(1000);
		m_uiLayer->addChild(noclipRed);

        return true;
    }

    GameObject* antiCheatObject;

    void destroyPlayer(PlayerObject* p, GameObject* g) {
        if (m_fields->antiCheatObject == nullptr && g != nullptr && g->getRealPosition().x == 0.f && g->getRealPosition().y == p->getRealPosition().y) m_fields->antiCheatObject = g;
        if (g == m_fields->antiCheatObject)
            return PlayLayer::destroyPlayer(p,g);
        if (getSavedVar<bool>("accuracy_limit")) {
			auto accu = (float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames");
			if (accu * 100 <= getSavedVar<float>("accuracy_limit_num")) {
				*setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
				resetLevel();
			}
		}
		if (getSavedVar<bool>("death_limit")) {
			if (*setTempVar<int>("noclip_deaths") >= getSavedVar<int>("death_limit_num")) {
				*setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
				resetLevel();
			}
		}
        *setTempVar<bool>("would_die") = true;
        if (getSavedVar<bool>("noclip") && !getSavedVar<bool>("noclip_P2") && getSavedVar<bool>("noclip_P1")) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (getSavedVar<bool>("noclip") && getSavedVar<bool>("noclip_P2") && !getSavedVar<bool>("noclip_P1")) {
			if (p == m_player1) PlayLayer::destroyPlayer(p,g);

		} 
		if (!getSavedVar<bool>("noclip") || (getSavedVar<bool>("noclip") && !getSavedVar<bool>("noclip_P1") && !getSavedVar<bool>("noclip_P2"))) {
			dead = true; // lazy again :P
            PlayLayer::destroyPlayer(p,g);
		}
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        dead = false;

        *setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
		*setTempVar<bool>("would_die") = false;
    }

    void levelComplete() {
        *setTempVar<bool>("level_completed") = true;
        PlayLayer::levelComplete();
    }
};

class $modify(GJBaseGameLayer) {
    void update(float dt) {
        if (!PlayLayer::get()) return GJBaseGameLayer::update(dt);

        if (!getTempVar<bool>("level_completed")) *setTempVar<float>("frames") += dt;

        if (getTempVar<bool>("would_die") && !lastDeath) {
			*setTempVar<int>("noclip_deaths") += 1;
		}

		lastDeath = getTempVar<bool>("would_die");

		if (getTempVar<bool>("would_die") && !dead && !getTempVar<bool>("level_completed")) {
			*setTempVar<float>("noclipped_frames") += dt;
			//dying = true;
			*setTempVar<bool>("would_die") = false;

			if (opacity < 70) {
				opacity += 10;
				if (getSavedVar<bool>("noclip_tint")) noclipRed->setOpacity(opacity);
			}
		} else {
			if (opacity > 0) {
				opacity -= 10;
				if (getSavedVar<bool>("noclip_tint")) noclipRed->setOpacity(opacity);
			}
		}
        GJBaseGameLayer::update(dt);
    }
};