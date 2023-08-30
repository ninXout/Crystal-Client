#include "../CrystalProfile.hpp"
#include <Geode/modify/LevelSettingsLayer.hpp>
#include <Geode/modify/CustomSongWidget.hpp>

static bool move = false;

struct CopySongID :  Modify<CopySongID, CustomSongWidget> {
    void onCopy(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        button->setScale(1);

        auto copyText = static_cast<CCLabelBMFont*>(this->getChildByID("id-and-size-label"));
        std::string text = copyText->getString();

        if (text.length() > 22) { 
            text = text.substr(8, text.length() - 22); // deleting the Size things and SongID: text
        } else {
            text.clear();
        }

        CrystalClient::get()->copyToClipboard(text);

        FLAlertLayer::create(
			"Amazing!",
			"<cj>Song ID</c> copied to your <cg>clipboard!</c>",
			"OK"
		)->show();
    }

	bool init(SongInfoObject* so, LevelSettingsObject* ls, bool a, bool b , bool c, bool d, bool hideBackground) {
	    CustomSongWidget::init(so,ls, a, b, c, d, hideBackground);

            if (getVar<bool>("copy_songID")) {
                auto menu = this->getChildByID("buttons-menu");
                auto atext = this->getChildByID("author-name-label");
                auto mbutton = menu->getChildByID("more-button");
                auto dbutton = menu->getChildByID("download-button");
                auto cbutton = menu->getChildByID("cancel-button");
                auto rbutton = menu->getChildByID("refresh-button");
                auto ubutton = menu->getChildByID("use-button");
                auto pbutton = menu->getChildByID("play-song-button");
                auto buttonSprite = ButtonSprite::create("Copy");
                auto button = CCMenuItemSpriteExtra::create(buttonSprite, this, menu_selector(CopySongID::onCopy));

                if (atext->getContentSize().width >= 178.5f) {
                    move = true;
                    dbutton->setScale(0.7f);
                    cbutton->setScale(0.7f);
                    rbutton->setScale(0.7f);
                    ubutton->setScale(0.7f);
                    pbutton->setScale(0.6f);
                    dbutton->setPositionY(-184.0f);
                    cbutton->setPositionY(-184.0f);
                    rbutton->setPositionY(-184.0f);
                    ubutton->setPositionY(-184.0f);
                    pbutton->setPositionY(-132.0f);
                } else {
                    move = false;
                }   

                if (!mbutton->isVisible()) {
                    button->setVisible(false);
                }
            
                auto mbpos = mbutton->getPosition();
                auto mcs = mbutton->getContentSize();
                button->setPositionX(mbpos.x + 45);
                buttonSprite->setPositionY(12.5f);
                button->setPositionY(-157.0f);
                button->setContentSize(mcs);
                buttonSprite->setContentSize({101.6f, 25.0f});
            
                buttonSprite->setScale(0.575f);

                menu->addChild(button);
            }
            
		return true;
	}
};

class $modify(LevelSettingsLayer) {
    bool init(LevelSettingsObject* levelSettings, LevelEditorLayer* editor) {
        LevelSettingsLayer::init(levelSettings, editor);
            auto newbutton = findFirstChildRecursive<CCNode>(this, [](CCNode* n) {
                return n->getPositionX() == 127.0f; // theres no node ids im so sorry :(
            });

            if (move && getVar<bool>("copy_songID")) {
                newbutton->setPositionY(-97.0f);
            }

        return true;
    }
};