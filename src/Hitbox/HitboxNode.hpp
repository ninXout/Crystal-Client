#pragma once

#include <Geode/Geode.hpp>
#include <Geode/Modify.hpp>
#include <vector>

namespace tulip {
	class HitboxNode : public cocos2d::CCDrawNode {
	public:
		HitboxNode();
		static HitboxNode* create();

		virtual void drawCircleHitbox(cocos2d::CCPoint const& center, float radius, cocos2d::ccColor4B col);

		virtual void drawPolygonHitbox(std::vector<cocos2d::CCPoint> const& points, cocos2d::ccColor4B col);

		virtual void drawRectangleHitbox(cocos2d::CCRect const& rect, cocos2d::ccColor4B col);

		virtual void drawPathLine(cocos2d::CCPoint const&, cocos2d::_ccColor4F const&);

		std::deque<cocos2d::CCRect> m_player1Queue;
		std::deque<cocos2d::CCRect> m_player2Queue;

		PlayerObject* m_pPlayer1ForSimulation;
		PlayerObject* m_pPlayer2ForSimulation;

		bool m_pIsSimulation;
		bool m_pDieInSimulation;

		float m_thickness;
		float m_trailLength;
		bool m_drawTrail;
		bool m_noLimitTrail;

		virtual void clearQueue();
		virtual void addToPlayer1Queue(cocos2d::CCRect const& rect);
		virtual void addToPlayer2Queue(cocos2d::CCRect const& rect);


		virtual void drawForPlayer1(PlayerObject* obj);
		virtual void drawForPlayer2(PlayerObject* obj);
		virtual void drawForObject(GameObject* obj);

		virtual void createPlayersForTrajectory();
		virtual void trajectoryPerPlayer(PlayerObject* player, PlayerObject* playerBase, float dt);
		virtual void processMainTrajectory(float dt);
		virtual bool shouldInterrumpHooks(PlayerObject* player);
		virtual void activateObjectsOnPlayerTrajectory(GameObject* obj, PlayerObject* player);
		virtual void onQuitTrajectory();
/*
		virtual void calculateForPlayer(PlayerObject* player);
		virtual float recreatedSlopeY(PlayerObject* player);
		virtual bool recreatedIsFalling(PlayerObject* player);
		virtual void initPlayerValues(PlayerObject* player);

		int m_hasGhostTrail;
		double m_xVelocity;
		double m_jumpAccel;
		double m_gravity;
		double m_lastJumpTime;
		double m_unk558;
		double m_unk560;
		float m_decelerationRate;
		bool m_hasHitRing;
		int m_unknown6a0;
		bool m_unk5B0;
		void* m_unk5D0;
		bool m_unk5FC;
		bool m_unk5FD;
		bool m_hasHitPortal;
		bool m_unknown73d;
		bool m_isHolding;
		bool m_hasJustHeld;
		bool m_isHolding2;
		bool m_hasJustHeld2;
		bool m_canRobotJump;
		double m_yVelocity;
		bool m_isOnSlope;
		bool m_wasOnSlope;
		bool m_isShip;
		bool m_isBird;
		bool m_isBall;
		bool m_isDart;
		bool m_isRobot;
		bool m_isSpider;
		bool m_isUpsideDown;
		bool m_unk63F;
		bool m_isOnGround;
		bool m_isDashing;
		float m_vehicleSize;
		float m_playerSpeed;
		bool m_isSliding;
		bool m_isRising;
		bool m_isLocked;
		bool m_unk674;
		bool m_unk675;
		cocos2d::CCPoint m_position;
		bool m_unk684;
		bool m_unk685;
		double m_unk688;
		float m_groundHeight;
		float m_unk69C;
*/
		virtual std::vector<cocos2d::CCPoint> triangleForObject(GameObject* obj);
		virtual std::vector<cocos2d::CCPoint> quadrilateralForObject(GameObject* obj);
	};
}

static inline tulip::HitboxNode* s_drawer = nullptr;
