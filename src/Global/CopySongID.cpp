#include "../CrystalProfile.hpp"
#include <Geode/modify/CustomSongWidget.hpp>

int songID;
std::string NONG = "NONG";

struct CopySongID :  Modify<CopySongID, CustomSongWidget> {
    void onCopy(CCObject* sender) {
        std::string text = std::to_string(songID);

        geode::utils::clipboard::write(text);

        FLAlertLayer::create(
			"Amazing!",
			"<cj>Song ID</c> copied to your <cg>clipboard!</c>",
			"OK"
		)->show();
    }

	bool init(SongInfoObject* song, LevelSettingsObject* ls, bool a, bool b , bool c, bool defaultSong, bool hideBackground) {
	    CustomSongWidget::init(song,ls, a, b, c, defaultSong, hideBackground);

            if (getVar<bool>("copy_songID")) {
                auto originalText = static_cast<CCLabelBMFont*>(this->getChildByID("id-and-size-label"));
                auto nongLabel = static_cast<CCLabelBMFont*>(this->getChildByID("nongd-id-and-size-label"));
                auto textanchor = originalText->getAnchorPoint();
                auto menu = this->getChildByID("buttons-menu");
                auto buttonText = CCLabelBMFont::create(originalText->getString(), "bigFont.fnt");
                auto button = CCMenuItemSpriteExtra::create(buttonText, this, menu_selector(CopySongID::onCopy));

                if (song) {
                    songID = song->m_songID;
                } else {
                    songID = 0;
                }
                
                if (nongLabel) {
                    nongLabel->setVisible(false);
                    std::string nongText = nongLabel->getString();

                    if (nongText.find(NONG) != std::string::npos) {
                        button->setVisible(false);
                        nongLabel->setVisible(true);
                    }
                }

                if (defaultSong) {
                    button->setVisible(false);
                }
                
                originalText->setVisible(false);
                
                button->setPosition({-284.450f, -191.950f});
                button->setContentSize({208.0f, 20.0f});
                button->setAnchorPoint(textanchor);
                button->setID("GH_copy-id-button");

                buttonText->setScale(0.4f);
                buttonText->setPosition(104.625f, 9.875f);

                menu->addChild(button);
            }

        return true;
    }

    void updateSongObject(SongInfoObject* song) {
        CustomSongWidget::updateSongObject(song);

        if (getVar<bool>("copy_songID")) {
            auto nongLabel = static_cast<CCLabelBMFont*>(this->getChildByID("nongd-id-and-size-label"));
            auto menu = this->getChildByID("buttons-menu");
            auto button = menu->getChildByID("GH_copy-id-button");

            if (button) {
                button->setVisible(true);
            }

            if (nongLabel) {
                nongLabel->setVisible(false);
                std::string nongText = nongLabel->getString();

                if (nongText.find(NONG) != std::string::npos && button) {
                    button->setVisible(false);
                    nongLabel->setVisible(true);
                }
            }
        }
    }
};