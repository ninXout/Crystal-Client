#include "../CrystalProfile.hpp"
#include <Geode/modify/CustomSongWidget.hpp>

struct PlaySongLevelPage :  Modify<PlaySongLevelPage, CustomSongWidget> {
    bool init(SongInfoObject* so, LevelSettingsObject* ls, bool a, bool b , bool c, bool d, bool hideBackground) {
		CustomSongWidget::init(so,ls, a, b, c, d, hideBackground);
        this->schedule(schedule_selector(PlaySongLevelPage::updateVisiblity));
        
		return true;
	}

    void updateVisiblity(float dt) {
        if (getVar<bool>("play_song_level_page")) {
            auto menu = this->getChildByID("buttons-menu");
            auto pbutton = menu->getChildByID("play-song-button");

            if (!pbutton->isVisible()) {
                pbutton->setVisible(true);
            }
        }
    }
};

