#include <Geode/Geode.hpp>
#include <Geode/Modify.hpp>
#include "CrystalProfile.hpp"

using namespace geode::prelude;

#include "HitboxNode.hpp"
using namespace tulip;

HitboxNode::HitboxNode() : m_thickness(0.5), m_trailLength(400), m_drawTrail(false), m_noLimitTrail(false) {

}

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
	if (Crystal::profile.fillHitbox) {
		colorA = ccc4FFromccc4B(ccc4(col.r, col.g, col.b, Crystal::profile.fillOpacity));
	} else {
		colorA = ccc4FFromccc4B(ccc4(0, 0, 0, 0));
	}

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

void HitboxNode::drawPathLine(cocos2d::CCPoint const& point, cocos2d::_ccColor4F const& color) {
	this->drawDot(point, 2, color);
}

void HitboxNode::clearQueue() {
	m_player1Queue.clear();
	m_player2Queue.clear();
}
void HitboxNode::addToPlayer1Queue(CCRect const& rect) {
	
	if (m_drawTrail) {
		// while (m_player1Queue.size() > 0 && 
		// 	m_player1Queue.front().origin.x < rect.origin.x - m_trailLength) {
		// 	m_player1Queue.pop_front();
		// }
	}
	else {
		m_player1Queue.clear();
	}
	m_player1Queue.push_back(rect);
}
void HitboxNode::addToPlayer2Queue(CCRect const& rect) {
	if (m_drawTrail) {
		// while (m_player2Queue.size() > 0 && 
		// 	m_player2Queue.front().origin.x < rect.origin.x - m_trailLength) {
		// 	m_player2Queue.pop_front();
		// }
	}
	else {
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

void HitboxNode::createPlayersForTrajectory() {
	auto playLayer = GameManager::sharedState()->getPlayLayer();
	if (!playLayer)
		return;

	m_pPlayer1ForSimulation = PlayerObject::create(1, 1, 0);
	m_pPlayer1ForSimulation->setPosition({0, 105});
	m_pPlayer1ForSimulation->setVisible(false);
	playLayer->m_batchNodePlayer->addChild(m_pPlayer1ForSimulation);

	m_pPlayer2ForSimulation = PlayerObject::create(1, 1, 0);
	m_pPlayer2ForSimulation->setPosition({0, 105});
	m_pPlayer2ForSimulation->setVisible(false);
	playLayer->m_batchNodePlayer->addChild(m_pPlayer2ForSimulation);
}

void HitboxNode::trajectoryPerPlayer(PlayerObject* player, PlayerObject* playerBase, float dt) {
	auto pos = playerBase->getPosition();
	auto playLayer = GameManager::sharedState()->getPlayLayer();
	auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

	player->setPosition(pos);
	player->pushButton(1);

	if(playerBase->m_vehicleSize < 1) {
		player->togglePlayerScale(true);
		player->m_vehicleSize = 0.6f;
	}

	for (size_t i = 0; i < static_cast<int>(winSize.width); i++) {
		auto prevPos = player->getPosition();
		player->m_collisionLog->removeAllObjects();
		player->m_collisionLog1->removeAllObjects();
		player->update(0.2f);
		player->updateSpecial(0.2f);
		playLayer->checkCollisions(player, 1);
		this->drawSegment(prevPos, player->getPosition(), 0.65f, cocos2d::ccc4f(0, 1, 0.1, 1));
		if (m_pDieInSimulation)
			break;
	}

	this->drawForPlayer1(player);
	player->setPosition(pos);
	player->releaseButton(1);
	m_pDieInSimulation = false;

	for (size_t i = 0; i < static_cast<int>(winSize.width); i++)
	{
		auto prevPos = player->getPosition();
		player->m_collisionLog->removeAllObjects();
		player->m_collisionLog1->removeAllObjects();
		player->update(0.2f);
		player->updateSpecial(0.2f);
		playLayer->checkCollisions(player, 1);
		this->drawSegment(prevPos, player->getPosition(), 0.65f, cocos2d::ccc4f(0, 1, 0.1, 1));
		if (m_pDieInSimulation)
			break;
	}

	this->drawForPlayer1(player);
	player->setPosition(pos);
}

void HitboxNode::processMainTrajectory(float dt)
{
	auto playLayer = GameManager::sharedState()->getPlayLayer();
	if (!playLayer || !m_pPlayer1ForSimulation || !m_pPlayer2ForSimulation)
		return;

	m_pIsSimulation = true;

	auto safeCircles = playLayer->m_circleWaves->count();
	this->trajectoryPerPlayer(m_pPlayer1ForSimulation, playLayer->m_player1, dt);
	m_pDieInSimulation = false;
	if (playLayer->m_player2 && playLayer->m_isDualMode)
		this->trajectoryPerPlayer(m_pPlayer2ForSimulation, playLayer->m_player2, dt);

	if (safeCircles < playLayer->m_circleWaves->count())
	{
		auto cantRemove = playLayer->m_circleWaves->count() - safeCircles;
		for (size_t i = 0; i < cantRemove; i++)
		{
			int index = playLayer->m_circleWaves->count() - 1;
			reinterpret_cast<CCCircleWave*>(playLayer->m_circleWaves->objectAtIndex(index))->removeMeAndCleanup();
		}
	}

	m_pIsSimulation = false;
	m_pDieInSimulation = false;
}

bool HitboxNode::shouldInterrumpHooks(PlayerObject* player) {
	auto playLayer = GameManager::sharedState()->getPlayLayer();
	if (!playLayer)
		return false;
	if ((player == m_pPlayer1ForSimulation || player == m_pPlayer2ForSimulation || m_pIsSimulation))
	{
		return true;
	}
	return false;
}


void HitboxNode::activateObjectsOnPlayerTrajectory(GameObject* obj, PlayerObject* player) {
	auto playLayer = GameManager::sharedState()->getPlayLayer();
	if (!playLayer)
		return;
	auto typeObj = obj->getType();

	if (typeObj != GameObjectType::BallPortal && typeObj != GameObjectType::ShipPortal &&
		typeObj != GameObjectType::UfoPortal && typeObj != GameObjectType::WavePortal &&
		typeObj != GameObjectType::RobotPortal && typeObj != GameObjectType::CubePortal)
	{
		return;
	}

	player->toggleFlyMode(false);
	player->toggleBirdMode(false);
	player->toggleRollMode(false);
	player->toggleDartMode(false);
	player->toggleRobotMode(false);
	player->toggleSpiderMode(false);

	if (typeObj == GameObjectType::BallPortal)
	{
		player->toggleRollMode(true);
	}
	else if (typeObj == GameObjectType::ShipPortal)
	{
		player->toggleFlyMode(true);
	}
	else if (typeObj == GameObjectType::UfoPortal)
	{
		player->toggleBirdMode(true);
	}
	else if (typeObj == GameObjectType::WavePortal)
	{
		player->toggleDartMode(true);
	}
	else if (typeObj == GameObjectType::RobotPortal)
	{
		player->toggleRobotMode(true);
	}
	else if (typeObj == GameObjectType::SpiderPortal)
	{
		player->toggleSpiderMode(true);
	}
}

void HitboxNode::onQuitTrajectory() {
	m_pDieInSimulation = false;
	m_pIsSimulation = false;
	m_pPlayer1ForSimulation = nullptr;
	m_pPlayer2ForSimulation = nullptr;
}