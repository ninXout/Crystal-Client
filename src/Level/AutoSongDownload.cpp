#include "../CrystalProfile.hpp"
#include <Geode/modify/CustomSongWidget.hpp>

class $modify(CustomSongWidget) {
	bool init(SongInfoObject* so, LevelSettingsObject* ls, bool a, bool b , bool c, bool d, bool hideBackground) {
		CustomSongWidget::init(so,ls, a, b, c, d, hideBackground);
	
		if (getVar<bool>("auto_song_download")) {
			auto menu = this->getChildByID("buttons-menu");
            auto dbutton = static_cast<CCMenuItem*>(menu->getChildByID("download-button"));

			if (dbutton->isVisible()) {
				dbutton->activate();
			}
		}

		return true;
	}
};