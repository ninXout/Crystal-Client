#pragma once

#include <Geode/Geode.hpp>
#include <Geode/Modify.hpp>
#include <vector>

namespace tulip {
	class __attribute__((visibility("hidden"))) HitboxNode : public cocos2d::CCDrawNode {
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

		virtual std::vector<cocos2d::CCPoint> triangleForObject(GameObject* obj);
		virtual std::vector<cocos2d::CCPoint> quadrilateralForObject(GameObject* obj);
	};
}

static inline tulip::HitboxNode* s_drawer = nullptr;
