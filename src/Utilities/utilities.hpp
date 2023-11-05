#pragma once

inline double getPercentage() {
    if (!PlayLayer::get()) return 0;

    double ret = ((PlayLayer::get()->m_player1->getPositionX()) / PlayLayer::get()->m_levelLength) * 100;
    if (ret < 0) ret = 0;
    if (ret > 100) ret = 100;

    return ret;
}