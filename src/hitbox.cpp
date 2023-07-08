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
	//if (Crystal::profile.fillHitbox) {
		//colorA = ccc4FFromccc4B(ccc4(col.r, col.g, col.b, Crystal::profile.fillOpacity));
	//} else {
		//colorA = ccc4FFromccc4B(ccc4(0, 0, 0, 0));
	//}
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
	PlayerButton p0;
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
/*
void HitboxNode::recreatedSlopeY(PlayerObject* player) {
	double dVar1;
  
	dVar1 = member<double>(player, 0x7d8) - member<double>(player, 0x500);
	if (0.1000000014901161 <= dVar1) {
		dVar1 = 1.0;
	}
	else {
		dVar1 = dVar1 * 10.0;
		if (dVar1 <= 0.4000000059604645) {
			dVar1 = 0.4000000059604645;
		}
	}
	return (float)((double)*(member<float>(player, 0x76c)) * dVar1);
}

bool HitboxNode::recreatedIsFalling(PlayerObject* player) {
	double* dVar1;
	bool bVar2;
	double* dVar3;
	
	dVar3 = member<double>(player, 0x618);
	dVar1 = member<double>(player, 0x760);
	if (member<char *>(player, 0x776) == '\0') {
		if (member<char *>(player, 0x7d1) != '\0') {
		dVar3 = (double)((unsigned long)dVar3 ^ 0x8000000000000000);
		}
		dVar3 = (double)((float)dVar3 + (float)dVar3);
		bVar2 = dVar3 < dVar1;
	} else {
		dVar3 = dVar3 + dVar3;
		bVar2 = dVar1 < dVar3;
	}
	return !bVar2 && dVar1 != dVar3;
}

void HitboxNode::initPlayerValues(PlayerObject* player) {
	m_xVelocity;
	m_jumpAccel;
	m_gravity;
	m_isInPlayLayer;
	m_unk53D;
	m_unk53E;
	m_unk53F;
	m_isCheckpointQueued;
	m_lastJumpTime;
	m_unk558;
	m_unk560;
	m_decelerationRate;
	m_hasHitRing;
	m_unknown6a0;
	m_unk5B0;
	m_unk5FC;
	m_unk5FD;
	m_hasHitPortal;
	m_unknown73d;
	m_isHolding;
	m_hasJustHeld;
	m_isHolding2;
	m_hasJustHeld2;
	m_unk615;
	m_unk616;
	m_unk618;
	m_unk61C;
	m_unk620;
	m_canRobotJump;
	m_yVelocity;
	m_isOnSlope;
	m_wasOnSlope;
	m_unk634;
	m_isShip;
	m_isBird;
	m_isBall;
	m_isDart;
	m_isRobot;
	m_isSpider;
	m_isUpsideDown;
	m_unk63F;
	m_isOnGround;
	m_isDashing;
	m_vehicleSize;
	m_playerSpeed;
	m_isSliding;
	m_isRising;
	m_isLocked;
	m_unk674;
	m_unk675;
	m_position;
	m_unk684;
	m_unk685;
	m_unk688;
	m_groundHeight;
	m_unk69C;

	
	
	
	
	
	
	player->isHidden;
	player->hasGhostTrail;
	player->xVelocity;
	player->jumpAccel;
	player->gravity;
	player->unknown20;
	player->unk538;
	player->unk539;
	player->unk53A;
	player->unk53B;
	player->isInPlayLayer;
	player->unk53D;
	player->unk53E;
	player->unk53F;
	player->isCheckpointQueued;
	player->lastJumpTime;
	player->unk558;
	player->unk560;
	player->decelerationRate;
	player->hasHitRing;
	player->unknown6a0;
	player->unk5B0;
	player->unk5FC;
	player->unk5FD;
	player->hasHitPortal;
	player->unknown73d;
	player->isHolding;
	player->hasJustHeld;
	player->isHolding2;
	player->hasJustHeld2;
	player->unk615;
	player->unk616;
	player->unk618;
	player->unk61C;
	player->unk620;
	player->canRobotJump;
	player->yVelocity;
	player->isOnSlope;
	player->wasOnSlope;
	player->unk634;
	player->isShip;
	player->isBird;
	player->isBall;
	player->isDart;
	player->isRobot;
	player->isSpider;
	player->isUpsideDown;
	player->unk63F;
	player->isOnGround;
	player->isDashing;
	player->vehicleSize;
	player->playerSpeed;
	player->isSliding;
	player->isRising;
	player->isLocked;
	player->unk674;
	player->unk675;
	player->position;
	player->unk684;
	player->unk685;
	player->unk688;
	player->groundHeight;
	player->unk69C;
}

void HitboxNode::calculateForPlayer(PlayerObject* player) {
	const float dtSlow = dt * 0.9f;
			
	float localGravity = this->m_gravity;
        if (this->m_isBall || this->m_isShip || this->m_isBird || this->m_isDart || this->m_isSpider) {
            localGravity = 0.958199;
        }

        const bool isMini = this->m_vehicleSize != 1.0;

        float playerSize = isMini ? 0.8 : 1.0;

        const int flipGravityMult = this->m_isUpsideDown ? -1 : 1;

        if (this->m_isShip || this->m_isBird || this->m_isDart) {
            if (isMini) {
                playerSize = 0.85;
            }
            // limit for velocity going up
            float upperVelocityLimit = 8.0 / playerSize;
            // limit for velocity going down
            float lowerVelocityLimit = -6.4 / playerSize;
            
            if (!this->m_isUpsideDown) {
                if (
                    (this->m_yVelocity >= 0.0 && this->m_yVelocity < upperVelocityLimit)
                    || (this->m_yVelocity <= 0.0 && this->m_yVelocity > lowerVelocityLimit)
                ) {
                    this->m_hasHitPortal = false;
                }
            } else if (
                (this->m_yVelocity <= 0.0 && -upperVelocityLimit < this->m_yVelocity)
                || (this->m_yVelocity >= 0.0 && this->m_yVelocity < -lowerVelocityLimit)
            ) {
                this->m_hasHitPortal = false;
            }

            if (this->m_isShip) {
                // ship
                float shipAccel = 0.8;
                
                if (this->m_hasHitPortal) {
                    if (!this->m_isUpsideDown) {
                        if (this->m_yVelocity < 0.0) {
                            shipAccel = -1.0;
                        }
                    } else if (this->m_yVelocity > 0.0) {
                        shipAccel = -1.0;
                    }
                } else if (this->m_isHolding) {
                    shipAccel = -1.0;
                }

                if (!this->m_isHolding && !this->recreatedIsFalling(player)) {
                    shipAccel = 1.2;
                }
                float extraBoost = 0.4;
                if (this->m_isHolding && this->recreatedIsFalling(player)) {
                    extraBoost = 0.5;
                }
                this->m_yVelocity -= localGravity * dtSlow * flipGravityMult * shipAccel * extraBoost / playerSize;

                if (this->m_isHolding) {
                    this->m_isSliding = false;
                }
            } else if (this->m_isDart) {
                // wave
                int holdingMult = this->m_isHolding ? 1 : -1;
                this->m_yVelocity = this->m_playerSpeed * this->m_xVelocity * flipGravityMult * holdingMult;
            } else {
                // ufo
                if (this->m_hasJustHeld && this->m_isHolding) {
                    this->m_hasJustHeld = false;

                    const float sizeMultiplier = isMini ? 8.0 : 7.0;
                    float newVelocity = flipGravityMult * sizeMultiplier * playerSize;

                    if (!this->m_isUpsideDown && this->m_yVelocity < newVelocity || newVelocity < this->m_yVelocity) {
                        this->m_yVelocity = newVelocity;

                        if ((this->m_wasOnSlope || this->m_isOnSlope) && (this->m_unk634 > 0.0)) {
                            this->m_yVelocity = std::min(this->m_yVelocity + this->m_unk634 * 0.5, newVelocity * 1.4);
                        }
                    }
                    //this->playBurstEffect();
                }

                float gravityMult = 0.8;
                if (!this->recreatedIsFalling(player)) {
                    gravityMult = 1.2;
                }
                this->m_yVelocity -= localGravity * dtSlow * flipGravityMult * gravityMult * 0.5 / playerSize;
                if (this->m_isHolding) {
                    this->m_isSliding = false;
                }
            }
            if (this->m_hasHitPortal) {
                return;
            }
            if (this->m_isDart) {
                return;
            }
            if (!this->m_isUpsideDown) {
                if (this->m_yVelocity <= lowerVelocityLimit) {
                    this->m_yVelocity = lowerVelocityLimit;
                }
            } else {
                if (this->m_yVelocity <= -upperVelocityLimit) {
                    this->m_yVelocity = -upperVelocityLimit;
                }
                upperVelocityLimit = 6.4 / playerSize;
            }
            if (this->m_yVelocity >= upperVelocityLimit) {
                this->m_yVelocity = upperVelocityLimit;
            }
        } else {
            // not ship wave or ufo
            // so cube, robot, ball, spider

            float gravityMultiplier = 1.0;

            if (this->m_isBall) {
                gravityMultiplier = 0.6;
            } else if (this->m_isSpider) {
                gravityMultiplier = 0.6;
            } else if (this->m_isRobot) {
                gravityMultiplier = 0.9;
            }

            bool shouldJump = this->m_isHolding;
            if (this->m_isRobot) {
                shouldJump = this->m_hasJustHeld && this->m_isHolding;
            }
            
            if (shouldJump && this->m_isOnGround && !this->m_isDashing) {
                if (this->m_isSpider) {
                    //this->spiderTestJump(false);
                } else {
                    this->m_isSliding = false;
                    this->m_isRising = true;

                    this->m_isOnGround = false;
                    this->m_hasJustHeld = false;
                    this->m_canRobotJump = false;
                    this->m_decelerationRate = 0.0;

                    float jumpAccel = this->m_jumpAccel;
                    if (this->m_isRobot) {
                        jumpAccel *= 0.5;

                    if (this->m_unk620 != 213) {
                        jumpAccel = 9999.0;
                        this->m_hasHitPortal = true;
                    }
                    this->m_yVelocity = flipGravityMult * jumpAccel * playerSize;

                    if (this->m_wasOnSlope || this->m_isOnSlope) {
                        if (flipGravityMult * this->m_unk634 > 0.0) {
                            double scaledVelocityIDK = this->m_yVelocity * 1.4;

                            float slopeVel = this->recreatedSlopeY(player);
                            if (this->m_isBall) {
                                slopeVel = this->m_unk634;
                            }
                            this->m_yVelocity += slopeVel * 0.25;
                            if (!this->m_isUpsideDown) {
                                this->m_yVelocity = std::min(this->m_yVelocity, scaledVelocityIDK);
                            } else {
                                this->m_yVelocity = std::max(this->m_yVelocity, scaledVelocityIDK);
                            }
                        }
                    }
                    
                    // has jumped?
                    this->m_unk53B = true;
                    this->m_lastJumpTime = time(nullptr);
                    //this->incrementJumps();
                    
                    if (this->m_isBall) {
                        //this->flipGravity(!this->m_isUpsideDown,true);
                        this->m_unk53F = false;
                        this->m_isHolding = false;
                        this->m_yVelocity *= 0.6;
                    } else if (this->m_isRobot) {
                        //this->m_robotSprite->tweenToAnimation("jump_loop", 0.1);
                    } else if (!this->m_isSpider) {
                        // should only get here when cube
                        //this->runRotateAction();
                    }
                }
                // return;
            } else {
                float flippedGravityIfIDKThing = this->m_gravity;
                // unk685 = is on dual? ive only seen it true there
                if (this->m_unk685) {
                    flippedGravityIfIDKThing = -this->m_gravity;
                }
                if (this->m_isRising) {
                    if (!this->m_isRobot || !this->m_isHolding || this->m_canRobotJump || 1.5 <= this->m_decelerationRate) {
                        this->m_yVelocity -= localGravity * dtSlow * flipGravityMult * gravityMultiplier;
                    } else {
                        this->m_decelerationRate += dtSlow * 0.1;
                    }
                    bool condition;
                    if (!this->m_isUpsideDown) {
                        condition = this->m_yVelocity <= flippedGravityIfIDKThing * 2.0;
                    } else {
                        condition = this->m_yVelocity >= this->m_gravity * 2.0;
                    }
                    if (condition) {
                        this->m_isSliding = false;
                        this->m_isRising = false;

                        this->m_unk53A = true;
                    }
                } else {
                    if (!this->m_isUpsideDown) {
                        if (this->m_yVelocity < flippedGravityIfIDKThing * 2.0) {
                            this->m_isOnGround = false;
                        }
                    } else {
                        if (this->m_yVelocity > this->m_gravity * 2.0) {
                            this->m_isOnGround = false;
                        }
                    }
                    this->m_yVelocity -= localGravity * dtSlow * flipGravityMult * gravityMultiplier;
                    if (!this->m_isUpsideDown) {
                        this->m_yVelocity = std::max(this->m_yVelocity, -15.0);
                    } else {
                        this->m_yVelocity = std::min(this->m_yVelocity, 15.0);
                    }
                    if (!this->m_isUpsideDown) {
                        if (this->m_yVelocity >= flippedGravityIfIDKThing * 2.0) {
                            return;
                        }
                    } else {
                        if (this->m_yVelocity <= this->m_gravity * 2.0) {
                            return;
                        }
                    }
                    if (!this->m_isUpsideDown) {
                        if (this->m_yVelocity >= -4.0) {
                            return;
                        }
                    } else {
                        if (this->m_yVelocity <= 4.0) {
                            return;
                        }
                    }
                    this->m_isSliding = false;
                }
            }
        }
	}
	
	if (m_isDashing) {
		m_yVelocity = 0.0;
	}

	const float velX = dt * m_xVelocity * m_playerSpeed;
	float velY = dtSlow * m_yVelocity;

	if (m_isDashing) {
		velY = from<float>(player, 0x46c) * velX;
	} else if (m_isDart) {
		velY = (m_isHolding ? 1.0f : -1.0f) * (m_isUpsideDown ? -1.0f : 1.0f) * velX;
		if (m_vehicleSize != 1.0) {
			velY *= 2.0f;
		}
	}

	m_unk69C = velY;
	const CCPoint velocity { velX, velY };
	// PlayerObject::setPosition(const CCPoint&), does a lot of stuff
	this->setPosition(this->getPosition() + velocity);
}
*/