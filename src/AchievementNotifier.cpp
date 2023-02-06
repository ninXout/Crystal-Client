#include "hackpro.hpp"

class $modify(AchievementNotifier) {
    void willSwitchToScene(cocos2d::CCScene* newScene) {
		if (showing) {
			showing = false;
			gui->removeFromParent();
		}

        AchievementNotifier::willSwitchToScene(newScene);
        
		/*
        if (FPSOverlay::sharedState()->getParent() != newScene) {
            FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(newScene->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
        }
		*/
    }
};