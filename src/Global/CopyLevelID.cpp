#include "../CrystalProfile.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

struct CopyLevelID :  Modify<CopyLevelID, EditLevelLayer> {
    void onCopy(CCObject* sender) {
        auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
        button->setScale(1);

        auto buttonText = static_cast<CCLabelBMFont*>(button->getNormalImage());
        std::string text = buttonText->getString();

        std::string numericText;
        for (char c : text) {
            if (isdigit(c)) {
                numericText += c;
            }
        }

        CrystalClient::get()->copyToClipboard(numericText);

        FLAlertLayer::create(
			"Amazing!",
			"<cj>Level ID</c> copied to your <cg>clipboard!</c>",
			"OK"
		)->show();
    }

	bool init(GJGameLevel* level) {
	    EditLevelLayer::init(level);
		    auto text = static_cast<CCLabelBMFont*>(this->getChildByID("level-id-label"));
            auto menu = CCMenu::create();
            auto buttonText = CCLabelBMFont::create(text->getString(), "goldFont.fnt" );
            auto button = CCMenuItemSpriteExtra::create(buttonText, this, menu_selector(CopyLevelID::onCopy));

            if (getVar<bool>("copy_levelID")) {
                text->setVisible(false);
                buttonText->setScale(0.6);

                button->setPosition({75.0f, -146.0f});
                button->setScale(1);
			    button->setAnchorPoint({0.5f, 0.5f});

                menu->addChild(button);

                this->addChild(menu);
            }

		return true;
	}
};