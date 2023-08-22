#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        if (!PlayLayer::init(gj)) return false;

        if (getVar<bool>("testmode_label")) {
			if (this->getChildrenCount()) {
				CCArrayExt<CCNode*> children = this->getChildren();
				for (auto* child : children) {
					using namespace std::literals::string_view_literals;
					if (auto* label = typeinfo_cast<CCLabelBMFont*>(child); label && label->getString() == "Testmode"sv) {
						label->setVisible(false);
						break;
					}
				}
			}
		}

        return true;
    }
};