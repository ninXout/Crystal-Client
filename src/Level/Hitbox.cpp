#include "../CrystalProfile.hpp"
#include "../Hitbox/HitboxNode.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/PlayerObject.hpp>

// Copied from altalk23/alk1m123's Hitbox Visualizer

static inline bool s_onlyHitboxes = false;
static inline bool s_showOnDeath = false;
static inline bool s_drawOnDeath = false;
static inline bool s_noLimitTrail = false;
std::vector<GameObject*> coins;

class $modify(PlayLayer) {
    static inline tulip::HitboxNode* drawer;

    bool init(GJGameLevel* gj) {
        drawer = tulip::HitboxNode::create();

        if (!PlayLayer::init(gj)) return false;
        
        m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = getVar<bool>("hitbox_on_death");
		drawer->m_drawTrail = getVar<bool>("hitbox_trail");
		s_onlyHitboxes = false;
		if (s_showOnDeath) s_drawOnDeath = false;

        return true;
    }

    void checkCollisions(PlayerObject* p, float idk) {
        PlayLayer::checkCollisions(p, idk);

		if (!getVar<bool>("hitboxes")) return;

        if (p == m_player1) {
            drawer->addToPlayer1Queue(m_player1->getObjectRect());
        }
        if (p == m_player2) {
            drawer->addToPlayer2Queue(m_player2->getObjectRect());
        }
    }

    void update(float dt) {
        drawer->clear();

        PlayLayer::update(dt);

		if (!getVar<bool>("hitboxes")) return;

        if (s_showOnDeath) {
			if (!s_drawOnDeath) return;
			drawer->setVisible(true);
		}

		for (size_t i = 0; i < coins.size(); i++) {
			if (coins[i] && m_player1->getPositionX() <= coins[i]->getPositionX() && getVar<bool>("coin_tracker")) drawer->drawSegment(m_player1->getPosition(), coins[i]->getPosition(), 0.5f, ccc4f(0, 1, 0, 1));
		}

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		s_showOnDeath = getVar<bool>("hitbox_on_death");

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				drawer->drawForObject(obj);
			}
		}
    }

    void resetLevel() {
        if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();
        PlayLayer::resetLevel();
    }

    void addObject(GameObject* g) {
        PlayLayer::addObject(g);
		if ((g->m_objectID == 1329 || g->m_objectID == 142)) coins.push_back(g);
    }

    void onQuit() {
        coins.clear();
        PlayLayer::onQuit();
    }
};

class $modify(HitboxLevelEditorLayer, LevelEditorLayer) {
    static inline tulip::HitboxNode* drawer;
	static inline bool paused = false;

	bool init(GJGameLevel* lvl) {
		drawer = tulip::HitboxNode::create();
		auto ret = LevelEditorLayer::init(lvl);
		drawer->setVisible(false);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		drawer->m_drawTrail = getVar<bool>("hitbox_trail");
		s_noLimitTrail = false;

		this->updateHitboxEditor();

		if (getVar<bool>("hitboxes_in_editor")) drawer->setVisible(true);
		return ret;
	}
	bool checkCollisions(PlayerObject* player, float uhh) {
		auto ret = LevelEditorLayer::checkCollisions(player, uhh);
		if (player == m_player1) {
			drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
		return ret;
	}
	void onPlaytest() {
		LevelEditorLayer::onPlaytest();
		drawer->drawForPlayer1(m_player1);
		this->updateHitboxEditor();
		if (getVar<bool>("hitboxes_in_editor")) {
			drawer->setVisible(true);
		}
	}
	void onPausePlaytest() {
		LevelEditorLayer::onPausePlaytest();
		paused = true;
		this->updateHitboxEditor();
	}
	void updateHitboxEditor() {
		if (!paused) return;
		if (s_noLimitTrail) drawer->m_noLimitTrail = true;

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				drawer->drawForObject(obj);
			}
		}
	}
	void onResumePlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
		LevelEditorLayer::onResumePlaytest();
	}
	void onStopPlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
        drawer->clearQueue();
        if (getVar<bool>("hitboxes_in_editor")) {
			drawer->setVisible(true);
		}
        LevelEditorLayer::onStopPlaytest();
    }

	void update(float dt) {
		drawer->clear();
		LevelEditorLayer::update(dt);

		if (m_player1) {
			if (getVar<bool>("hitboxes_in_editor")) drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			if (getVar<bool>("hitboxes_in_editor")) drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				if (getVar<bool>("hitboxes_in_editor")) drawer->drawForObject(obj);
			}
		}
	}
};

class $modify(EditorUI) {
	void keyDown(enumKeyCodes code) {
		EditorUI::keyDown(code);
		if (s_drawer) {
			s_drawer->clear();
			if (GJBaseGameLayer::get()->m_player1) {
				s_drawer->drawForPlayer1(GJBaseGameLayer::get()->m_player1);
			}
			if (GJBaseGameLayer::get()->m_player2) {
				s_drawer->drawForPlayer2(GJBaseGameLayer::get()->m_player2);
			}

			float xp = GJBaseGameLayer::get()->m_player1->getPositionX();

			for (int s = GJBaseGameLayer::get()->sectionForPos(xp) - 5; s < GJBaseGameLayer::get()->sectionForPos(xp) + 6; ++s) {
				if (s < 0) continue;
				if (s >= GJBaseGameLayer::get()->m_sectionObjects->count()) break;
				auto section = static_cast<CCArray*>(GJBaseGameLayer::get()->m_sectionObjects->objectAtIndex(s));
				for (size_t i = 0; i < section->count(); ++i) {
					auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

					if (s_onlyHitboxes) obj->setOpacity(0);

					if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
					if (!obj->m_active) continue;

					s_drawer->drawForObject(obj);
				}
			}
		} 
	}
};

class $modify(PlayerObject) {
    void playerDestroyed(bool idk) {
        PlayerObject::playerDestroyed(idk);
        s_drawOnDeath = true;
    }
};