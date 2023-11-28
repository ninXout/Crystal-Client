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
    double m_rotationX;
    double m_rotationY;
    double m_scale;
    bool m_skewX;
    bool m_skewY;
    float m_unk2F4;
    float m_unk2F8;
    float m_unk33C;
    float m_unk340;
    float m_unk390;

    static ObjectCheckpoint create(GameObject*);
    void apply(GameObject*);
};

#define FIELD(var) ic.var = obj->var;

ObjectCheckpoint ObjectCheckpoint::create(GameObject* obj) {
    ObjectCheckpoint ic;
    ic.m_position = obj->getPosition();
    ic.m_rotationX = obj->getRotationX();
    ic.m_rotationY = obj->getRotationY();
    ic.m_scale = obj->getScale();
    ic.m_skewX = obj->getSkewX();
    ic.m_skewY = obj->getSkewY();
    FIELD(m_unk2F4);
    FIELD(m_unk2F8);
    return ic;
}

#undef FIELD
#define FIELD(var) obj->var = var;

void ObjectCheckpoint::apply(GameObject* obj) {
    obj->setPosition(m_position);
    obj->setRotationX(m_rotationX);
    obj->setRotationY(m_rotationY);
    obj->setScale(m_scale);
    obj->setSkewX(m_skewX);
    obj->setSkewY(m_skewY);
    //FIELD(m_unk2F4);
    //FIELD(m_unk2F8);
}

#undef FIELD

struct PlayCheckpoint {
    IconCheckpoint m_player1;
    IconCheckpoint m_player2;
    std::vector<ObjectCheckpoint> m_objects;

    static PlayCheckpoint create(PlayLayer*);
    void apply(PlayLayer*);
};

PlayCheckpoint PlayCheckpoint::create(PlayLayer* pl) {
    PlayCheckpoint pc;
    pc.m_player1 = IconCheckpoint::create(pl->m_player1);
    pc.m_player2 = IconCheckpoint::create(pl->m_player2);
    pc.m_objects = {};
    CCArrayExt<GameObject*> objects = pl->m_objects;
    for (auto* obj : objects) {
        pc.m_objects.push_back(ObjectCheckpoint::create(obj));
    }
    return pc;
}

void PlayCheckpoint::apply(PlayLayer* pl) {
    m_player1.apply(pl->m_player1);
    m_player2.apply(pl->m_player2);
    int index = 0;
    CCArrayExt<GameObject*> objects = pl->m_objects;
    for (auto* obj : objects) {
        m_objects[index].apply(obj);
        index++;
    }
}

std::vector<PlayCheckpoint> g_checkpoints;

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        g_checkpoints.clear();

        if (!PlayLayer::init(gj))
            return false;

        g_checkpoints.push_back(PlayCheckpoint::create(this));
        return true;
    }

    void markCheckpoint() {
        PlayLayer::markCheckpoint();
        g_checkpoints.push_back(PlayCheckpoint::create(PlayLayer::get()));
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        if (g_checkpoints.size() && getSavedVar<bool>("practice_fix")) g_checkpoints.back().apply(this);
    }

    void removeLastCheckpoint() {
        PlayLayer::removeLastCheckpoint();
        if (g_checkpoints.size()) g_checkpoints.pop_back();
    }
};