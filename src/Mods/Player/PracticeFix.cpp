#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CheckpointObject.hpp>

using namespace CrystalClient;

struct IconCheckpoint {
    CCPoint m_position;
    double m_rotation;
    double m_yVelocity;
    double m_xVelocity;
    double m_jumpAccel;
    bool m_isUpsideDown;
    float m_vehicleSize;
    float m_playerSpeed;
    GameObject* m_objectSnappedTo;
    bool m_isHolding;
    bool m_hasJustHeld;
    bool m_isHolding2;
    bool m_hasJustHeld2;
    bool m_isSliding;
    bool m_isRising;
    bool m_canRobotJump;

    static IconCheckpoint create(PlayerObject*);
    void apply(PlayerObject*);
};

#define FIELD(var) ic.var = pl->var;

IconCheckpoint IconCheckpoint::create(PlayerObject* pl) {
    IconCheckpoint ic;
    ic.m_rotation = pl->getRotation();

    FIELD(m_position);
    FIELD(m_yVelocity);
    FIELD(m_xVelocity);
    FIELD(m_jumpAccel);
    FIELD(m_isUpsideDown);
    FIELD(m_vehicleSize);
    FIELD(m_playerSpeed);
    FIELD(m_objectSnappedTo);
    FIELD(m_isHolding);
    FIELD(m_hasJustHeld);
    FIELD(m_isHolding2);
    FIELD(m_hasJustHeld2);
    FIELD(m_isSliding);
    FIELD(m_isRising);
    FIELD(m_canRobotJump);
    return ic;
}

#undef FIELD
#define FIELD(var) pl->var = var;

void IconCheckpoint::apply(PlayerObject* pl) {
    pl->setRotation(m_rotation);

    FIELD(m_position);
    FIELD(m_yVelocity);
    FIELD(m_xVelocity);
    FIELD(m_jumpAccel);
    FIELD(m_isUpsideDown);
    FIELD(m_vehicleSize);
    FIELD(m_playerSpeed);
    FIELD(m_objectSnappedTo);
    FIELD(m_isHolding);
    FIELD(m_hasJustHeld);
    FIELD(m_isHolding2);
    FIELD(m_hasJustHeld2);
    FIELD(m_isSliding);
    FIELD(m_isRising);
    FIELD(m_canRobotJump);
}

#undef FIELD

// objects

struct ObjectCheckpoint {
    CCPoint m_position;
    double m_rotation;
    double m_yVelocity;
    double m_xVelocity;
    float m_unk2F4;
    float m_unk2F8;
    float m_unk33C;
    float m_unk340;
    float m_unk390;

    static ObjectCheckpoint create(PlayLayer*);
    void apply(PlayLayer*);
};

#define FIELD(var) ic.var = obj->var;

ObjectCheckpoint ObjectCheckpoint::create(PlayLayer* pl) {
    ObjectCheckpoint ic;

    float xp = pl->m_player1->getPositionX();

	for (int s = GJBaseGameLayer::get()->sectionForPos(xp) - 5; s < GJBaseGameLayer::get()->sectionForPos(xp) + 6; ++s) {
        if (s < 0)
            continue;
        if (s >= pl->m_sectionObjects->count())
            break;
        auto section = static_cast<CCArray*>(pl->m_sectionObjects->objectAtIndex(s));
        for (size_t i = 0; i < section->count(); ++i) {
            auto obj = static_cast<GameObject*>(section->objectAtIndex(i));
            if (obj != PlayLayer::get()->m_antiCheatObject) {
                ic.m_position = obj->getPosition();
                ic.m_rotation = obj->getRotation();
                ic.m_xVelocity = obj->getSkewX();
                ic.m_yVelocity = obj->getSkewY();
                FIELD(m_unk2F4);
                FIELD(m_unk2F8);
                //FIELD(m_unk33C);
                //FIELD(m_unk340);
                //FIELD(m_unk390);
            }
        }
    }

    return ic;
}

#undef FIELD
#define FIELD(var) obj->var = var;

void ObjectCheckpoint::apply(PlayLayer* pl) {
    float xp = pl->m_player1->getPositionX();

	for (int s = GJBaseGameLayer::get()->sectionForPos(xp) - 5; s < GJBaseGameLayer::get()->sectionForPos(xp) + 6; ++s) {
        if (s < 0)
            continue;
        if (s >= pl->m_sectionObjects->count())
            break;
        auto section = static_cast<CCArray*>(pl->m_sectionObjects->objectAtIndex(s));
        for (size_t i = 0; i < section->count(); ++i) {
            auto obj = static_cast<GameObject*>(section->objectAtIndex(i));
            if (obj != PlayLayer::get()->m_antiCheatObject) {
                obj->setPosition(m_position);
                //obj->setRotation(m_rotation);
                obj->setSkewX(m_xVelocity);
                obj->setSkewY(m_yVelocity);
                FIELD(m_unk2F4);
                FIELD(m_unk2F8);
            }
        }
    }
}

#undef FIELD

std::vector<IconCheckpoint> checkpoints_P1;
std::vector<IconCheckpoint> checkpoints_P2;
std::vector<ObjectCheckpoint> checkpoints_OBJ;

class $modify(CheckpointObject) {
    static CheckpointObject* create() {
        auto co = CheckpointObject::create();
        checkpoints_P1.push_back(IconCheckpoint::create(PlayLayer::get()->m_player1));
        checkpoints_P2.push_back(IconCheckpoint::create(PlayLayer::get()->m_player2));
        checkpoints_OBJ.push_back(ObjectCheckpoint::create(PlayLayer::get()));
        return co;
    }
};

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        checkpoints_P1.clear();
        checkpoints_P2.clear();
        checkpoints_OBJ.clear();

        if (!PlayLayer::init(gj))
            return false;

        return true;
    }

    void startGame() {
        PlayLayer::startGame();
        if (m_player1) checkpoints_P1.push_back(IconCheckpoint::create(m_player1));
        if (m_player2) checkpoints_P2.push_back(IconCheckpoint::create(m_player2));
        if (m_sectionObjects) checkpoints_OBJ.push_back(ObjectCheckpoint::create(this));
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        if (checkpoints_P1.size() > 0 && m_player1 && getSavedVar<bool>("practice_fix")) checkpoints_P1.back().apply(m_player1);
        if (checkpoints_P2.size() > 0 && m_player2 && getSavedVar<bool>("practice_fix")) checkpoints_P2.back().apply(m_player2);
        if (checkpoints_OBJ.size() > 0 && m_sectionObjects && getSavedVar<bool>("practice_fix")) checkpoints_OBJ.back().apply(this);
    }

    void removeLastCheckpoint() {
        PlayLayer::removeLastCheckpoint();
        if (checkpoints_P1.size() > 0) checkpoints_P1.pop_back();
        if (checkpoints_P2.size() > 0) checkpoints_P2.pop_back();
        if (checkpoints_OBJ.size() > 0) checkpoints_OBJ.pop_back();
    }
};