#include "HitboxViewer.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace tulip;
using namespace CrystalClient;

HitboxNode::HitboxNode() : m_thickness(0.5), m_trailLength(400), m_drawTrail(false), m_noLimitTrail(false) {}

HitboxNode* HitboxNode::create() {
	auto ret = new (std::nothrow) HitboxNode;
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

void HitboxNode::drawCircleHitbox(CCPoint const& center, float radius, ccColor4B col) {
	constexpr size_t N = 64;
	constexpr double PI = 3.1415926535;
	std::vector<CCPoint> points(N);
	for (size_t i = 0; i < N; ++i) {
		points[i] = center + CCPointMake(std::cos(2 * PI * i / N), std::sin(2 * PI * i / N)) * radius;
	}
	this->drawPolygonHitbox(points, col);
}

void HitboxNode::drawPolygonHitbox(std::vector<CCPoint> const& points, ccColor4B col) {
	auto color1 = ccc4FFromccc4B(col);
	cocos2d::_ccColor4F colorA;
	colorA = ccc4FFromccc4B(ccc4(0, 0, 0, 0));

	this->drawPolygon(const_cast<CCPoint*>(points.data()), points.size(), colorA, m_thickness, color1);
}

void HitboxNode::drawRectangleHitbox(CCRect const& rect, ccColor4B col) {
	constexpr size_t N = 4;
	std::vector<CCPoint> points(N);

	points[0] = CCPointMake(rect.getMinX(), rect.getMinY());
	points[1] = CCPointMake(rect.getMinX(), rect.getMaxY());
	points[2] = CCPointMake(rect.getMaxX(), rect.getMaxY());
	points[3] = CCPointMake(rect.getMaxX(), rect.getMinY());

	this->drawPolygonHitbox(points, col);
}

void HitboxNode::clearQueue() {
	m_player1Queue.clear();
	m_player2Queue.clear();
}

void HitboxNode::addToPlayer1Queue(CCRect const& rect) {
	if (!m_drawTrail) {
		m_player1Queue.clear();
	}
	m_player1Queue.push_back(rect);
}

void HitboxNode::addToPlayer2Queue(CCRect const& rect) {
	if (!m_drawTrail) {
		m_player2Queue.clear();
	}
	m_player2Queue.push_back(rect);
}

void HitboxNode::drawForPlayer1(PlayerObject* obj) {
	if (m_noLimitTrail) {
		for (auto rect : m_player1Queue) {
			this->drawRectangleHitbox(rect, ccc4(127, 63, 63, 255));
		}
	}
	else if (m_drawTrail) {
		auto lim = std::lower_bound(m_player1Queue.begin(), m_player1Queue.end(), obj->getPositionX() - m_trailLength,
			[](CCRect const& info, float pos){
				return info.origin.x < pos;
			}
		);
		if (lim != m_player1Queue.end()) {
			for (auto it = lim; it != m_player1Queue.end(); ++it) {
				this->drawRectangleHitbox(*it, ccc4(127, 63, 63, 255));
			}
		}
		
	}
	else {
		if (m_player1Queue.size() > 0) {
			this->drawRectangleHitbox(m_player1Queue.back(), ccc4(127, 63, 63, 255));
		}
		
	}
	this->drawPolygonHitbox(this->quadrilateralForObject(obj), ccc4(255, 0, 0, 255));
	this->drawRectangleHitbox(obj->getObjectRect(0.25, 0.25), ccc4(0, 255, 0, 255));
}

void HitboxNode::drawForPlayer2(PlayerObject* obj) {
	if (m_noLimitTrail) {
		for (auto rect : m_player2Queue) {
			this->drawRectangleHitbox(rect, ccc4(127, 63, 63, 255));
		}
	}
	else if (m_drawTrail) {
		auto lim = std::lower_bound(m_player2Queue.begin(), m_player2Queue.end(), obj->getPositionX() - m_trailLength,
			[](CCRect const& info, float pos){
				return info.origin.x < pos;
			}
		);
		if (lim != m_player2Queue.end()) {
			for (auto it = lim; it != m_player2Queue.end(); ++it) {
				this->drawRectangleHitbox(*it, ccc4(127, 63, 63, 255));
			}
		}
	}
	else {
		if (m_player2Queue.size() > 0) {
			this->drawRectangleHitbox(m_player2Queue.back(), ccc4(127, 63, 63, 255));
		}
	}
	this->drawPolygonHitbox(this->quadrilateralForObject(obj), ccc4(255, 0, 0, 255));
	this->drawRectangleHitbox(obj->getObjectRect(0.25, 0.25), ccc4(0, 255, 0, 255));
}

void HitboxNode::drawForObject(GameObject* obj) {
	if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) return;
	if (!obj->m_active) return;

	ccColor4B color;
	switch (obj->getType()) {
		case GameObjectType::Solid:
			color = ccc4(0, 0, 255, 255);
			break;
		case GameObjectType::Decoration:
			switch (obj->m_objectID) {
		        case 749:
		        	color = ccc4(255, 127, 0, 255);
					break;
		        default:
		            return;
			}
			break;
		case GameObjectType::TeleportPortal:
			color = ccc4(0, 127, 255, 255);
			break;
		case GameObjectType::Modifier:
			switch (obj->m_objectID) {
				case 200:
		        case 201:
		        case 202:
		        case 203:
		        case 1334:
		        	color = ccc4(255, 255, 255, 255);
					break;
		        default:
		            return;
			}
			break;
		case GameObjectType::Slope:
			color = ccc4(0, 0, 255, 255);
			this->drawPolygonHitbox(this->triangleForObject(obj), color);
			return;
		case GameObjectType::Hazard:
			color = ccc4(255, 0, 0, 255);
			break;

		case GameObjectType::InverseGravityPortal:
		case GameObjectType::YellowJumpPad:
		case GameObjectType::YellowJumpRing:
			color = ccc4(255, 255, 0, 255);
			break;
		case GameObjectType::InverseMirrorPortal:
		case GameObjectType::DualPortal:
			color = ccc4(255, 127, 0, 255);
			break;
		case GameObjectType::NormalGravityPortal:
		case GameObjectType::NormalMirrorPortal:
		case GameObjectType::SoloPortal:
			color = ccc4(0, 127, 255, 255);
			break;
		case GameObjectType::PinkJumpPad:
		case GameObjectType::PinkJumpRing:
			color = ccc4(255, 0, 255, 255);
			break;
		case GameObjectType::GravityPad:
		case GameObjectType::GravityRing:
			color = ccc4(0, 255, 255, 255);
			break;
		case GameObjectType::RedJumpPad:
		case GameObjectType::RedJumpRing:
			color = ccc4(255, 0, 127, 255);
			break;
		case GameObjectType::GreenRing:
		case GameObjectType::DashRing:
		case GameObjectType::RegularSizePortal:
			color = ccc4(0, 255, 0, 255);
			break;
		case GameObjectType::GravityDashRing:
		case GameObjectType::MiniSizePortal:
			color = ccc4(127, 0, 255, 255);
			break;
		case GameObjectType::SecretCoin:
		case GameObjectType::UserCoin:
		case GameObjectType::CustomRing:
		case GameObjectType::Collectible:
			color = ccc4(223, 223, 223, 255);
			break;
		case GameObjectType::DropRing:
			color = ccc4(31, 31, 31, 255);
			break;

		case GameObjectType::CubePortal:
			color = ccc4(0, 255, 0, 255);
			break;
		case GameObjectType::ShipPortal:
			color = ccc4(255, 127, 255, 255);
			break;
		case GameObjectType::BallPortal:
			color = ccc4(255, 127, 0, 255);
			break;
		case GameObjectType::UfoPortal:
			color = ccc4(255, 255, 0, 255);
			break;
		case GameObjectType::WavePortal:
			color = ccc4(0, 127, 255, 255);
			break;
		case GameObjectType::RobotPortal:
			color = ccc4(223, 223, 223, 255);
			break;
		case GameObjectType::SpiderPortal:
			color = ccc4(127, 0, 255, 255);
			break;
		default:
			return;
	}
	if (obj->getObjectRadius() > 0) {
		this->drawCircleHitbox(obj->getPosition(), obj->getObjectRadius(), color);
	}
	else {
		this->drawPolygonHitbox(this->quadrilateralForObject(obj), color);
	}
}

std::vector<CCPoint> HitboxNode::triangleForObject(GameObject* obj) {
	constexpr size_t N = 3;
	std::vector<CCPoint> points(N);
	int i = 0;
	obj->updateOrientedBox();
	if (obj->m_objectOBB2D) {
		auto obb = obj->m_objectOBB2D;
		if (obj->isFlipX() || !obj->isFlipY())
			points[i++] = obb->m_p1_1;
		if (!obj->isFlipX() || !obj->isFlipY())
			points[i++] = obb->m_p1_2;
		if (!obj->isFlipX() || obj->isFlipY())
			points[i++] = obb->m_p1_3;
		if (obj->isFlipX() || obj->isFlipY())
			points[i++] = obb->m_p1_4;
	}
	else {
		auto rect = obj->getObjectRect();
		if (obj->isFlipX() || !obj->isFlipY())
			points[i++] = CCPointMake(rect.getMinX(), rect.getMinY());
		if (!obj->isFlipX() || !obj->isFlipY())
			points[i++] = CCPointMake(rect.getMinX(), rect.getMaxY());
		if (!obj->isFlipX() || obj->isFlipY())
			points[i++] = CCPointMake(rect.getMaxX(), rect.getMaxY());
		if (obj->isFlipX() || obj->isFlipY())
			points[i++] = CCPointMake(rect.getMaxX(), rect.getMinY());
	}
	return points;
}
std::vector<CCPoint> HitboxNode::quadrilateralForObject(GameObject* obj) {
	constexpr size_t N = 4;
	std::vector<CCPoint> points(N);
	if (obj->m_objectOBB2D) {
		auto obb = obj->m_objectOBB2D;
		points[0] = obb->m_p1_1;
		points[1] = obb->m_p1_2;
		points[2] = obb->m_p1_3;
		points[3] = obb->m_p1_4;
	}
	else {
		auto rect = obj->getObjectRect();
		points[0] = CCPointMake(rect.getMinX(), rect.getMinY());
		points[1] = CCPointMake(rect.getMinX(), rect.getMaxY());
		points[2] = CCPointMake(rect.getMaxX(), rect.getMaxY());
		points[3] = CCPointMake(rect.getMaxX(), rect.getMinY());
	}
	return points;
}

static inline tulip::HitboxNode* s_drawer = nullptr;
static inline bool s_onlyHitboxes = false;
static inline bool s_showOnDeath = false;
static inline bool s_drawOnDeath = false;
static inline bool s_noLimitTrail = false;
std::vector<GameObject*> s_coins = {};

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        s_drawer = tulip::HitboxNode::create();

        if (!PlayLayer::init(gj)) return false;
        
        m_objectLayer->addChild(s_drawer, 32);

		s_showOnDeath = getSavedVar<bool>("hitbox_on_death");
		s_drawer->m_drawTrail = getSavedVar<bool>("hitbox_trail");
		s_onlyHitboxes = false;
		if (s_showOnDeath) s_drawOnDeath = false;

        return true;
    }

    void checkCollisions(PlayerObject* p, float idk) {
        PlayLayer::checkCollisions(p, idk);

		if (!getSavedVar<bool>("hitboxes")) return;

        if (p == m_player1) {
            s_drawer->addToPlayer1Queue(m_player1->getObjectRect());
        }
        if (p == m_player2) {
            s_drawer->addToPlayer2Queue(m_player2->getObjectRect());
        }
    }

    void update(float dt) {
        s_drawer->clear();

        PlayLayer::update(dt);

		if (!getSavedVar<bool>("hitboxes")) return;

        if (s_showOnDeath) {
			if (!s_drawOnDeath) return;
			s_drawer->setVisible(true);
		}

		for (size_t i = 0; i < s_coins.size(); i++) {
			if (s_coins[i] && m_player1->getPositionX() <= s_coins[i]->getPositionX() && getSavedVar<bool>("coin_tracker")) s_drawer->drawSegment(m_player1->getPosition(), s_coins[i]->getPosition(), 0.5f, ccc4f(0, 1, 0, 1));
		}

		if (m_player1) {
			s_drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			s_drawer->drawForPlayer2(m_player2);
		}

		s_showOnDeath = getSavedVar<bool>("hitbox_on_death");

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

				s_drawer->drawForObject(obj);
			}
		}
    }

    void resetLevel() {
        if (s_showOnDeath) s_drawOnDeath = false;
        s_drawer->clearQueue();
        PlayLayer::resetLevel();
    }

    void addObject(GameObject* g) {
        PlayLayer::addObject(g);
		if ((g->m_objectID == 1329 || g->m_objectID == 142)) s_coins.push_back(g);
    }

    void onQuit() {
        s_coins.clear();
        PlayLayer::onQuit();
    }
};

class $modify(HitboxLevelEditorLayer, LevelEditorLayer) {
	static inline bool paused = false;

	bool init(GJGameLevel* lvl) {
		s_drawer = tulip::HitboxNode::create();
		auto ret = LevelEditorLayer::init(lvl);
		s_drawer->setVisible(false);
		m_objectLayer->addChild(s_drawer, 32);

		s_drawer->m_drawTrail = getSavedVar<bool>("hitbox_trail");
		s_noLimitTrail = true;

		this->updateHitboxEditor();

		s_drawer->setVisible(true);
		return ret;
	}
	bool checkCollisions(PlayerObject* player, float uhh) {
		auto ret = LevelEditorLayer::checkCollisions(player, uhh);

        if (!getSavedVar<bool>("hitboxes_in_editor")) return ret;

		if (player == m_player1) {
			s_drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			s_drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
		return ret;
	}
	void onPlaytest() {
		LevelEditorLayer::onPlaytest();

        if (!getSavedVar<bool>("hitboxes_in_editor")) return;

		s_drawer->drawForPlayer1(m_player1);
		this->updateHitboxEditor();
		s_drawer->setVisible(true);
	}
	void onPausePlaytest() {
		LevelEditorLayer::onPausePlaytest();
        if (!getSavedVar<bool>("hitboxes_in_editor")) return;
		paused = true;
		this->updateHitboxEditor();
	}
	void updateHitboxEditor() {
		if (!paused) return;
		if (s_noLimitTrail) s_drawer->m_noLimitTrail = true;

		if (m_player1) {
			s_drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			s_drawer->drawForPlayer2(m_player2);
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

				s_drawer->drawForObject(obj);
			}
		}
	}
	void onResumePlaytest() {
        if (!getSavedVar<bool>("hitboxes_in_editor")) return LevelEditorLayer::onResumePlaytest();
		if (s_noLimitTrail) s_drawer->m_noLimitTrail = false;
		paused = false;
		LevelEditorLayer::onResumePlaytest();
	}
	void onStopPlaytest() {
        if (!getSavedVar<bool>("hitboxes_in_editor")) return LevelEditorLayer::onStopPlaytest();
		if (s_noLimitTrail) s_drawer->m_noLimitTrail = false;
		paused = false;
        s_drawer->clearQueue();
		s_drawer->setVisible(true);
        LevelEditorLayer::onStopPlaytest();
    }

	void update(float dt) {
        if (!getSavedVar<bool>("hitboxes_in_editor")) return LevelEditorLayer::update(dt);

		s_drawer->clear();
		LevelEditorLayer::update(dt);

		if (m_player1) {
			s_drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			s_drawer->drawForPlayer2(m_player2);
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

				s_drawer->drawForObject(obj);
			}
		}
	}
};

class $modify(EditorUI) {
	void keyDown(enumKeyCodes code) {
		EditorUI::keyDown(code);
        if (!getSavedVar<bool>("hitboxes_in_editor")) return;
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
        if (!getSavedVar<bool>("hitboxes_in_editor")) return;
        s_drawOnDeath = true;
    }
};