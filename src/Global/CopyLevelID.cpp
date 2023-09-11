#include "../CrystalProfile.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

struct CopyLevelID :  Modify<CopyLevelID, EditLevelLayer> {
    void onCopy(CCObject* sender) {
        auto buttonText = static_cast<CCLabelBMFont*>(this->getChildByID("level-id-label"));
        std::string text = buttonText->getString();

        std::string numericText;
        for (char c : text) {
            if (isdigit(c)) {
                numericText += c;
            }
        }

        if (numericText.empty()) {
            numericText = "0 (na)";
        }

        geode::utils::clipboard::write(numericText);

        FLAlertLayer::create(
			"Amazing!",
			"<cj>Level ID</c> copied to your <cg>clipboard!</c>",
			"OK"
		)->show();
    }

	bool init(GJGameLevel* level) {
	    EditLevelLayer::init(level);

            if (getVar<bool>("copy_levelID")) {
		        auto text = static_cast<CCLabelBMFont*>(this->getChildByID("level-id-label"));
                auto biText = this->getChildByID("bi-level-id-menu");
                auto textanchor = text->getAnchorPoint();
                auto menu = CCMenu::create();
                auto buttonText = CCLabelBMFont::create(text->getString(), "goldFont.fnt" );
                auto button = CCMenuItemSpriteExtra::create(buttonText, this, menu_selector(CopyLevelID::onCopy));

                text->setVisible(false);

                if (biText && button) {
                    button->setVisible(false);
                }

                button->setPosition({75.0f, 15.5f});
                button->setContentSize({135.25f, 20.75f});
                button->setAnchorPoint(textanchor);
                button->setID("copy-id-button");

                buttonText->setScale(0.6f);
                buttonText->setPosition({67.125f, 10.0f});

                menu->setPosition({284.5f, -1.0f});
                menu->setContentSize({150.0f, 30.0f});
                menu->setID("copy-id-menu");
                menu->addChild(button);

                this->addChild(menu);
            }

		return true;
	}
};