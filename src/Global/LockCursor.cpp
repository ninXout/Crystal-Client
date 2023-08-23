#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "../ImGui/ImGui.hpp"

class $modify(PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);

        CGEventRef ourEvent = CGEventCreate(NULL);
		auto point = CGEventGetLocation(ourEvent);
		CFRelease(ourEvent);

		if (!ImGuiCocos::get().isVisible() && getVar<bool>("lock_cursor") && !m_hasCompletedLevel) CGWarpMouseCursorPosition(point);
    } 
};