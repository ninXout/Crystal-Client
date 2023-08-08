#include "../CrystalProfile.hpp"
#include <Geode/modify/CustomSongWidget.hpp>

class $modify(CustomSongWidget) {
	bool init(SongInfoObject* so, LevelSettingsObject* ls, bool a, bool b , bool c, bool d, bool hideBackground) {
		CustomSongWidget::init(so,ls, a, b, c, d, hideBackground);
	
		if (getVar<bool>("auto_song_download")) {
			auto button = findFirstChildRecursive<CCMenuItemSpriteExtra>(this, [](CCNode* n) {
				return n->getPositionY() == -180.0f;
			});

			if (button->isVisible()) {
				button->activate();
			}
		}

		return true;
	}
};