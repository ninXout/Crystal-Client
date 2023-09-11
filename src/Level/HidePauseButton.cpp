#include "../CrystalProfile.hpp"
#include <Geode/modify/UILayer.hpp>

class $modify(UILayer) {
    static UILayer* create() {
        auto ui = UILayer::create();

        if (getVar<bool>("hide_pause_button")) {
			auto pmenu = ui->getChildByID("pause-button-menu");
            auto pbutton = pmenu->getChildByID("pause-button");

            if (pmenu) {
                pbutton->setVisible(false);
                pmenu->setVisible(false);
            }
		}
        
        return ui;
    }
};