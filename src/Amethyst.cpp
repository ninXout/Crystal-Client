#include "Amethyst.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = std::filesystem;

Amethyst::AmethystFrame Amethyst::create() {
    Amethyst::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newframe.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newframe.accel = GJBaseGameLayer::get()->m_player1->m_yAccel;
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

std::string Clickbot::pickRandomClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    std::filesystem::path path = std::filesystem::current_path() / "Crystal" / "clicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomSoftClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    std::filesystem::path path = std::filesystem::current_path() / "Crystal" / "softClicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    std::filesystem::path path = std::filesystem::current_path() / "Crystal" / "releases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}
std::string Clickbot::pickRandomSoftRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    std::filesystem::path path = std::filesystem::current_path() / "Crystal" / "softReleases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}