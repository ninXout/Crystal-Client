#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <imgui-cocos.hpp>

using namespace CrystalClient;

#ifdef GEODE_IS_MACOS

#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>

class $modify(PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        CGEventRef ourEvent = CGEventCreate(NULL);
		auto point = CGEventGetLocation(ourEvent);
		CFRelease(ourEvent);

		if (!ImGuiCocos::get().isVisible() && getSavedVar<bool>("lock_cursor") && !m_hasCompletedLevel) CGWarpMouseCursorPosition(point);
    } 
};

#endif