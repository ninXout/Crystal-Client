#include "Amethyst.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = ghc::filesystem;

Amethyst::AmethystFrame Amethyst::create() {
    Amethyst::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newframe.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newframe.accel = GJBaseGameLayer::get()->m_player1->m_yAccel;
    return newframe;
}

Amethyst::CheckpointData Amethyst::store() {
    Amethyst::CheckpointData newcp;
    newcp.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newcp.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newcp.rot = GJBaseGameLayer::get()->m_player1->getRotation();
    newcp.accel = GJBaseGameLayer::get()->m_player1->m_yAccel;
    return newcp;
}

std::string Clickbot::pickRandomClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "clicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomSoftClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "softClicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "releases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}
std::string Clickbot::pickRandomSoftRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "softReleases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}