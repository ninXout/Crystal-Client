#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        if (!PlayLayer::init(gj)) return false;

        // stolen from matcool's run info

        if (this->getChildrenCount()) {
			CCArrayExt<CCNode*> children = this->getChildren();
			for (auto* child : children) {
				using namespace std::literals::string_view_literals;
				if (auto* label = typeinfo_cast<CCLabelBMFont*>(child); label && label->getString() == "Testmode"sv) {
					label->setVisible(getSavedVar<bool>("testmode_label"));
					break;
				}
			}
		}
        
        return true;
    }
};