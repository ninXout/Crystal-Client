#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/CCTransitionFade.hpp>

using namespace CrystalClient;

class $modify(CCTransitionFade) {
    cocos2d::CCTransitionFade* create(float time, cocos2d::CCScene* scene, cocos2d::_ccColor3B const& color) {
        return cocos2d::CCTransitionFade::create(getSavedVar<bool>("no_transition") ? 0.f : time, scene, color);
    }
};