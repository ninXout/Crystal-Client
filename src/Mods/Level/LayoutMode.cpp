#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>

using namespace CrystalClient;

class $modify(PlayLayer) {
    void update(float dt) {
        if (!getSavedVar<bool>("layout_mode")) return PlayLayer::update(dt);

        PlayLayer::update(dt);

        auto xpos = m_player1->getPositionX();
        for (int s = GJBaseGameLayer::get()->sectionForPos(xpos) - 5; s < GJBaseGameLayer::get()->sectionForPos(xpos) + 6; ++s) {
			if (s < 0)
				continue;
			if (s >= GJBaseGameLayer::get()->m_sectionObjects->count())
				break;
			auto section = static_cast<CCArray*>(GJBaseGameLayer::get()->m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto o = static_cast<GameObject*>(section->objectAtIndex(i));

				if (o->getType() == GameObjectType::Decoration && o->isVisible() &&
					(o->m_objectID != 44 && o->m_objectID != 749 && o->m_objectID != 12 && o->m_objectID != 38 &&
					 o->m_objectID != 47 && o->m_objectID != 111 && o->m_objectID != 8 && o->m_objectID != 13 &&
					 o->m_objectID != 660 && o->m_objectID != 745 && o->m_objectID != 101 && o->m_objectID != 99 &&
					 o->m_objectID != 1331))
				{
					o->setVisible(false);
				}
                if (o->getType() != GameObjectType::Decoration) {
                    o->setOpacity(255);
                    o->setVisible(true);
                }
			}
		}
    }
};