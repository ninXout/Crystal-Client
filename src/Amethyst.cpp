#include "Amethyst.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

void Amethyst::apply(AmethystFrame frame, bool withxpos) {
    if (withxpos) GJBaseGameLayer::get()->m_player1->setPositionX(frame.xpos);
    GJBaseGameLayer::get()->m_player1->setPositionY(frame.ypos);
    mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = frame.accel;
    /*
    if (withxpos) mbo(float, GJBaseGameLayer::get()->m_player1, 0x7c8) = frame.xpos;
	mbo(float, GJBaseGameLayer::get()->m_player1, 0x7cc) = frame.ypos;
    mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = frame.accel;
    */
}

Amethyst::AmethystFrame Amethyst::create() {
    Amethyst::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->getPositionX();
    newframe.ypos = GJBaseGameLayer::get()->m_player1->getPositionY();
    newframe.accel = mbo(double, GJBaseGameLayer::get()->m_player1, 0x760);
    return newframe;
}

Amethyst::CheckpointData Amethyst::store() {
    Amethyst::CheckpointData newcp;
    newcp.xpos = GJBaseGameLayer::get()->m_player1->getPositionX();
    newcp.ypos = GJBaseGameLayer::get()->m_player1->getPositionY();
    newcp.rot = GJBaseGameLayer::get()->m_player1->getRotation();
    newcp.accel = mbo(double, GJBaseGameLayer::get()->m_player1, 0x760);
    return newcp;
}