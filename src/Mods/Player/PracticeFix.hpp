#pragma once

using namespace geode::prelude;

#define CPMEMBER(member) fc.member = pl->member;
#define REGMEMBER(member) pl->member = member;

class FixedCheckpoint {
    protected:
        CCPoint position;
        CCPoint nodePosition;
        float rotation;
        double xVel;
        double yVel;
        float rotationSpeed;
        GameObject* snappedObj;
        bool isOnSlope;
        bool wasOnSlope;
        float vehicleSize;
        float playerSpeed;

        bool m_isShip;
        bool m_isBird;
        bool m_isBall;
        bool m_isDart;
        bool m_isRobot;
        bool m_isSpider;
        bool m_isUpsideDown;
        bool m_isDead;
        bool m_isOnGround;
        bool m_isGoingLeft;
        bool m_isSideways;
        bool m_isSwing;

        bool m_unk658;
        bool m_unk659;
        bool m_unk65a;
        bool m_unk65b;
        bool m_unk65c;
        bool m_unk65d;
        bool m_unk65e;
        bool m_unk65f;
        GameObject* m_collidedObject;
        float m_unk644;
	    float m_unk648;
        float m_unk688;
	    float m_unk68c;
        float m_unk6ac;
        float m_unk6bc;

    public:
        static FixedCheckpoint create(PlayerObject* pl) {
            FixedCheckpoint fc;
            fc.position = pl->m_position;
            fc.nodePosition = pl->getPosition();
            fc.rotation = pl->getRotation();
            fc.xVel = pl->m_platformerXVelocity;
            fc.yVel = pl->m_yVelocity;
            fc.rotationSpeed = pl->m_rotationSpeed;
            fc.snappedObj = pl->m_objectSnappedTo;
            fc.isOnSlope = pl->m_isOnSlope;
            fc.wasOnSlope = pl->m_wasOnSlope;
            fc.vehicleSize = pl->m_vehicleSize;
            fc.playerSpeed = pl->m_playerSpeed;

            CPMEMBER(m_isShip);
            CPMEMBER(m_isBird);
            CPMEMBER(m_isBall);
            CPMEMBER(m_isDart);
            CPMEMBER(m_isRobot);
            CPMEMBER(m_isSpider);
            CPMEMBER(m_isUpsideDown);
            CPMEMBER(m_isDead);
            CPMEMBER(m_isOnGround);
            CPMEMBER(m_isGoingLeft);
            CPMEMBER(m_isSideways);
            CPMEMBER(m_isSwing);

            CPMEMBER(m_unk658);
            CPMEMBER(m_unk659);
            CPMEMBER(m_unk65a);
            CPMEMBER(m_unk65b);
            CPMEMBER(m_unk65c);
            CPMEMBER(m_unk65d);
            CPMEMBER(m_unk65e);
            CPMEMBER(m_unk65f);
            CPMEMBER(m_collidedObject);
            CPMEMBER(m_unk644);
            CPMEMBER(m_unk648);
            CPMEMBER(m_unk688);
            CPMEMBER(m_unk68c);
            CPMEMBER(m_unk6ac);
            CPMEMBER(m_unk6bc);
            return fc;
        }

        void apply(PlayerObject* pl) {
            pl->m_position = position;
            pl->setPosition(nodePosition);
            pl->setRotation(rotation);
            pl->m_platformerXVelocity = xVel;
            pl->m_yVelocity = yVel;
            pl->m_rotationSpeed = rotationSpeed;
            pl->m_objectSnappedTo = snappedObj;
            pl->m_isOnSlope = isOnSlope;
            pl->m_wasOnSlope = wasOnSlope;
            pl->m_vehicleSize = vehicleSize;
            pl->m_playerSpeed = playerSpeed;

            REGMEMBER(m_isShip);
            REGMEMBER(m_isBird);
            REGMEMBER(m_isBall);
            REGMEMBER(m_isDart);
            REGMEMBER(m_isRobot);
            REGMEMBER(m_isSpider);
            REGMEMBER(m_isUpsideDown);
            REGMEMBER(m_isDead);
            REGMEMBER(m_isOnGround);
            REGMEMBER(m_isGoingLeft);
            REGMEMBER(m_isSideways);
            REGMEMBER(m_isSwing);

            REGMEMBER(m_unk658);
            REGMEMBER(m_unk659);
            REGMEMBER(m_unk65a);
            REGMEMBER(m_unk65b);
            REGMEMBER(m_unk65c);
            REGMEMBER(m_unk65d);
            REGMEMBER(m_unk65e);
            REGMEMBER(m_unk65f);
            REGMEMBER(m_collidedObject);
            REGMEMBER(m_unk644);
            REGMEMBER(m_unk648);
            REGMEMBER(m_unk688);
            REGMEMBER(m_unk68c);
            //REGMEMBER(m_unk6ac);
            //REGMEMBER(m_unk6bc);
        }
};