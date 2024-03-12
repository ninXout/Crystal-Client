#ifdef __APPLE__

// silly goofy fix because it errors if it comes after geode includes

#define CommentType CommentTypeDummy
#include <CoreGraphics/CoreGraphics.h>
#include <CoreServices/CoreServices.h>
#undef CommentType

#endif

#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <imgui-cocos.hpp>

using namespace CrystalClient;

#ifdef GEODE_IS_MACOS

class $modify(GJBaseGameLayer) {
    void update(float dt) {
        GJBaseGameLayer::update(dt);

        if (!PlayLayer::get()) return;

        CGEventRef ourEvent = CGEventCreate(NULL);
		auto point = CGEventGetLocation(ourEvent);
		CFRelease(ourEvent);

		if (!ImGuiCocos::get().isVisible() && getSavedVar<bool>("lock_cursor") && !getTempVar<bool>("level_completed")) CGWarpMouseCursorPosition(point);
    } 
};

#endif