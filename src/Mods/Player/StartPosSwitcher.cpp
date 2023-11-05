#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/UILayer.hpp>
#include "StartPosSwitcher.hpp"

// [Partially] Copied from camila314/Camila's StartPos Switcher

std::vector<std::pair<StartPosObject*, CCPoint>> g_startPoses;
int g_startPosIndex;
CCLabelBMFont* g_startPosText;
CCSprite* g_rightButton;
CCSprite* g_leftButton;

void updateIndex(bool increment) {
    auto corner = CCDirector::sharedDirector()->getScreenTop();
    auto win_size = CCDirector::sharedDirector()->getWinSize();
    auto pl = PlayLayer::get();

    if (pl->m_isTestMode && getSavedVar<bool>("startpos_switch")) {
        if (increment) {
            g_startPosIndex++;
        } else {
            g_startPosIndex--;
        }

        if (g_startPosIndex == g_startPoses.size()) {
            g_startPosIndex = -1;
        } else if (g_startPosIndex < -1) {
            g_startPosIndex = g_startPoses.size() - 1;
        }

        auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
        g_startPosText->setString(label.c_str());

        if (pl->m_isTestMode) {
            pl->m_startPosCheckpoint = nullptr;
            if (g_startPosIndex == -1) {
                pl->m_startPos = nullptr;
                pl->m_playerStartPosition = ccp(0, 105);
            } else {
                pl->m_startPos = g_startPoses[g_startPosIndex].first;
                pl->m_playerStartPosition = g_startPoses[g_startPosIndex].second;
            }
        }

        pl->resetLevel();
    }
}

class $modify(SPPlayLayer, PlayLayer) {
    void addObject(GameObject* g) {
		PlayLayer::addObject(g);
		if (g->m_objectID == 31) {
            g->retain();
            g_startPoses.push_back({reinterpret_cast<StartPosObject*>(g), g->getPosition()});
            g_startPosIndex += 1;
            auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
            g_startPosText->setString(label.c_str());
        }
	}

    bool init(GJGameLevel* gj) {
        auto corner = CCDirector::sharedDirector()->getScreenTop();
        auto win_size = CCDirector::sharedDirector()->getWinSize();

        g_rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        g_leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
        g_startPosIndex = -1;
        g_startPoses = {};

        if (!PlayLayer::init(gj)) return false;

        g_startPosText->setPosition(win_size.width / 2, corner - 275);
        g_startPosText->setScale(0.5);
        g_startPosText->setOpacity(50);

        g_rightButton->setPosition(ccp(win_size.width / 2 - 30, corner - 275));
        g_rightButton->setScale(0.5);
        g_rightButton->setOpacity(50);
        
        g_leftButton->setPosition(ccp(win_size.width / 2 + 30, corner - 275));
        g_leftButton->setFlipX(true);
        g_leftButton->setScale(0.5);
        g_leftButton->setOpacity(50);

        if (!m_isTestMode || (!getSavedVar<bool>("startpos_switch") && m_isTestMode)) {
            g_startPosText->setVisible(false);
            g_rightButton->setVisible(false);
            g_leftButton->setVisible(false);
        }
        
        addChild(g_startPosText, 1000);
        addChild(g_rightButton, 1000);
        addChild(g_leftButton, 1000);

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        if (!m_isTestMode || (!getSavedVar<bool>("startpos_switch") && m_isTestMode)) {
            g_startPosText->setVisible(false);
            g_rightButton->setVisible(false);
            g_leftButton->setVisible(false);
        } else {
            g_startPosText->setVisible(true);
            g_rightButton->setVisible(true);
            g_leftButton->setVisible(true);
        }
    }
};