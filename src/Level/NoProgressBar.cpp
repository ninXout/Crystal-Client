#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    void update(float dt) {
        if (getVar<bool>("no_progress_bar")) {
			m_sliderGrooveSprite->setVisible(false);
			m_percentLabel->setPositionX(cocos2d::CCDirector::sharedDirector()->getWinSize().width / 2 - (m_percentLabel->getContentSize().width / 4));
		} else {
			m_sliderGrooveSprite->setVisible(true);
		}

        PlayLayer::update(dt);
    }
};