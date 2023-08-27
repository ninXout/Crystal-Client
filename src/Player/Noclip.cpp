#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool lastDeath;

float opacity;
CCSprite* noclipRed;

using namespace Crystal;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        if (!PlayLayer::init(gj)) return false;

        noclipRed = CCSprite::createWithSpriteFrameName("block005b_05_001.png");
		noclipRed->setPosition({CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2});
		noclipRed->setScale(1000.0f);
		noclipRed->setColor(ccc3(255,0,0));
		noclipRed->setOpacity(0);
		noclipRed->setZOrder(1000);
		m_UILayer->addChild(noclipRed);

        return true;
    }

    void destroyPlayer(PlayerObject* p, GameObject* g) {
        if (g == m_antiCheatObject) {
			return PlayLayer::destroyPlayer(p,g);
		}
        if (getVar<bool>("accuracy_limit")) {
			auto accu = (float)(getTempVar<float>("frames") - getTempVar<float>("noclipped_frames")) / (float)getTempVar<float>("frames");
			if (accu * 100 <= getVar<float>("accuracy_limit_num")) {
				*setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
				resetLevel();
			}
		}
		if (getVar<bool>("death_limit")) {
			if (*setTempVar<int>("noclip_deaths") >= getVar<int>("death_limit_num")) {
				*setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
				resetLevel();
				//if (profile.noclipDeath) g_death->setString(std::to_string(*setTempVar<int>("noclip_deaths")).c_str());
			}
		}
        *setTempVar<bool>("would_die") = true;
        if (getVar<bool>("noclip") && !getVar<bool>("noclip_P2") && getVar<bool>("noclip_P1")) {
			if (p == m_player2) PlayLayer::destroyPlayer(p,g);
		}
		if (getVar<bool>("noclip") && getVar<bool>("noclip_P2") && !getVar<bool>("noclip_P1")) {
			if (p == m_player1) PlayLayer::destroyPlayer(p,g);

		} 
		if (!getVar<bool>("noclip") || (getVar<bool>("noclip") && !getVar<bool>("noclip_P1") && !getVar<bool>("noclip_P2"))) {
			PlayLayer::destroyPlayer(p,g);
		}
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        *setTempVar<float>("frames") = *setTempVar<float>("noclipped_frames") = *setTempVar<int>("noclip_deaths") = 0;
		*setTempVar<bool>("would_die") = false;
    }

    void update(float dt)  {
        if (!m_hasCompletedLevel) *setTempVar<float>("frames") += dt;

        if (getTempVar<bool>("would_die") && !lastDeath) {
			*setTempVar<int>("noclip_deaths") += 1;
		}

		lastDeath = getTempVar<bool>("would_die");

		if (getTempVar<bool>("would_die") && !m_isDead && !m_hasCompletedLevel) {
			*setTempVar<float>("noclipped_frames") += dt;
			//dying = true;
			*setTempVar<bool>("would_die") = false;

			if (opacity < 70) {
				opacity += 10;
				if (getVar<bool>("noclip_tint")) noclipRed->setOpacity(opacity);
			}
		} else {
			if (opacity > 0) {
				opacity -= 10;
				if (getVar<bool>("noclip_tint")) noclipRed->setOpacity(opacity);
			}
		}
        PlayLayer::update(dt);
    }
};