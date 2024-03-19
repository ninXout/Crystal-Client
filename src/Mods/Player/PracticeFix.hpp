#pragma once

using namespace geode::prelude;

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
        }
};