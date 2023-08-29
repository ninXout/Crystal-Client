#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

bool frozen = false;
float pauseTime = 0;

class PauseCountdown : public CCLayerColor {
 public:
	static PauseCountdown* create() {
		auto pRet = new PauseCountdown();
		
		if (pRet && pRet->init()) {
			pRet->autorelease();
		    return pRet;
		}
		
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

	bool init() override {
        if (!CCLayerColor::initWithColor(ccc4(50, 50, 50, 100))) return false;
        m_countdown = CCLabelBMFont::create("3", "goldFont.fnt");
        m_countdown->setScale(1.5);
        m_countdown->setPosition(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2);
        addChild(m_countdown, 100);

		return true;
	}

    void setTimer(int count) {
        std::string realCount = std::to_string(3 - count);
        if (m_countdown) m_countdown->setString(realCount.c_str());
    }
 protected:
 	CCLabelBMFont* m_countdown = nullptr;
};

PauseCountdown* countdown = nullptr;
/*
class $modify(PlayLayer) {
    void pauseGame(bool pause) {
        pauseTime = 0;

        if (m_time == 0 || !getVar<bool>("pause_countdown") || pause) return PlayLayer::pauseGame(pause);

        PlayLayer::pauseGame(pause);

        frozen = true;
        countdown = PauseCountdown::create();
        countdown->setVisible(false);

        addChild(countdown, 1001);
    }

    void update(float dt) {
        if (frozen && getVar<bool>("pause_countdown") && countdown) {
            pauseTime += dt;

            if (pauseTime <= 3) {
                countdown->setVisible(true);
                countdown->setTimer(static_cast<int>(pauseTime));
            } else {
                countdown->removeMeAndCleanup();
                countdown = nullptr;
                frozen = false;
                pauseTime = 0;
            }
        }

        if (!frozen || !getVar<bool>("pause_countdown")) PlayLayer::update(dt);
    }
};*/