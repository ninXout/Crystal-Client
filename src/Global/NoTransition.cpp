#include "../CrystalProfile.hpp"
#include <Geode/modify/CCTransitionFade.hpp>

class $modify(CCTransitionFade) {
    virtual bool initWithDuration(float t, cocos2d::CCScene* scene, cocos2d::ccColor3B const& color) {
        if (getVar<bool>("no_transition")) {
            CCTransitionFade::initWithDuration(0.0f, scene, ccBLACK);
        } else {
            CCTransitionFade::initWithDuration(t, scene, ccBLACK);
        }
    }
};