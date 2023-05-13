#include "Amethyst.hpp"
#include "CrystalProfile.hpp"
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = ghc::filesystem;
using namespace Crystal;

void AmethystReplay::resetActions() {
    
}


void AmethystReplay::updateAmethyst() {
    
}

void AmethystReplay::addAction(bool push) {
    P1pushing = push;
    if (push) {
        
    } else {
        
    }
}

AmethystReplay::AmethystFrame AmethystReplay::create() {
    AmethystReplay::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newframe.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newframe.accel = GJBaseGameLayer::get()->m_player1->m_yVelocity;
    return newframe;
}

CheckpointData store(PlayerObject* player) {
    CheckpointData newcp;
    newcp.xpos = player->m_position.x;
    newcp.ypos = player->m_position.y;
    newcp.rot = player->getRotation();
    newcp.yaccel = player->m_yVelocity;
    newcp.xaccel = player->m_xVelocity;
    newcp.jump_accel = player->m_jumpAccel;
    newcp.isUpsideDown = player->m_isUpsideDown;
    newcp.vehicle_size = player->m_vehicleSize;
    newcp.player_speed = player->m_playerSpeed;
    newcp.snapped_obj = player->m_objectSnappedTo;
    return newcp;
}

std::string Clickbot::pickRandomClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "Amethyst" / "ClickBot" / "clicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomSoftClick() {
    std::vector<std::string> clicks;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "Amethyst" / "ClickBot" / "softClicks";
    for (const auto & entry : fs::directory_iterator(path))
    {
        clicks.push_back(entry.path().string());
    }
    return clicks[rand() % clicks.size()];
}
std::string Clickbot::pickRandomRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "Amethyst" / "ClickBot" / "releases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}
std::string Clickbot::pickRandomSoftRelease() {
    std::vector<std::string> releases;
    std::vector<std::string> out;
    ghc::filesystem::path path = geode::Mod::get()->getConfigDir() / "Amethyst" / "ClickBot" / "softReleases";
    for (const auto & entry : fs::directory_iterator(path))
        releases.push_back(entry.path().string());
    return releases[rand() % releases.size()];
}

