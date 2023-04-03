#include "Amethyst.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

Amethyst::AmethystFrame Amethyst::create() {
    Amethyst::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->getPositionX();
    newframe.ypos = GJBaseGameLayer::get()->m_player1->getPositionY();
    newframe.accel = mbo(double, GJBaseGameLayer::get()->m_player1, 0x760);
    return newframe;
}

Amethyst::CheckpointData Amethyst::store() {
    Amethyst::CheckpointData newcp;
    //newcp.xpos = GJBaseGameLayer::get()->m_player1->getPositionX();
    //newcp.ypos = GJBaseGameLayer::get()->m_player1->getPositionY();
    newcp.rot = GJBaseGameLayer::get()->m_player1->getRotation();
    newcp.accel = mbo(double, GJBaseGameLayer::get()->m_player1, 0x760);
    return newcp;
}