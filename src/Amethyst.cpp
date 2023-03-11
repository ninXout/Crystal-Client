#include <Geode/Geode.hpp>
#include "Amethyst.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

void Amethyst::apply(AmethystFrame frame, bool withxpos) {
    GJBaseGameLayer::get()->m_player1->setPositionX(frame.xpos);
    GJBaseGameLayer::get()->m_player1->setPositionY(frame.ypos);
    mbo(double, GJBaseGameLayer::get()->m_player1, 0x760) = frame.accel;
    /*
	if (withxpos) mbo(float, GJBaseGameLayer::get()->m_player1, 0x7c8) = frame.xpos;
	mbo(float, GJBaseGameLayer::get()->m_player1, 0x7cc) = frame.ypos;
    */
}

Amethyst::AmethystFrame Amethyst::create() {
    Amethyst::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->getPositionX();
    newframe.ypos = GJBaseGameLayer::get()->m_player1->getPositionY();
    newframe.accel = mbo(double, GJBaseGameLayer::get()->m_player1, 0x760);
    return newframe;
}