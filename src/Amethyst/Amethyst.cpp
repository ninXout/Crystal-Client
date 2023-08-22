#include "Amethyst.hpp"
#include "../CrystalProfile.hpp"
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = ghc::filesystem;
using namespace Crystal;

AmethystMacro AmethystMacro::createFromFile(const char* filename, bool legacy) {
    AmethystMacro ret;
    std::string line;
    std::fstream file;
    file.open(filename, std::ios::in);
    if (file.is_open()) {
        getline(file, line);
        int len;
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            ret.P1pushes.push_back(stof(line));
        }
        getline(file, line);
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            ret.P1releases.push_back(stof(line));
        }
        getline(file, line);
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            ret.P2pushes.push_back(stof(line));
        }
        getline(file, line);
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            ret.P2releases.push_back(stof(line));
        }
        file.close();
    }
    return ret;
}

void AmethystMacro::saveToFile(const char* filename) {
    std::fstream myfile(filename, std::ios::app);
    myfile << P1pushes.size();
    myfile << "\n";
    for (size_t i = 0; i < P1pushes.size(); i++)
    {
        myfile << std::setprecision(10) << std::fixed << P1pushes[i];
        myfile << "\n";
    }
    myfile << P1releases.size();
    myfile << "\n";
    for (size_t i = 0; i < P1releases.size(); i++)
    {
        myfile << std::setprecision(10) << std::fixed << P1releases[i];
        myfile << "\n";
    }
    myfile << P2pushes.size();
    myfile << "\n";
    for (size_t i = 0; i < P2pushes.size(); i++)
    {
        myfile << std::setprecision(10) << std::fixed << P2pushes[i];
        myfile << "\n";
    }
    myfile << P2releases.size();
    myfile << "\n";
    for (size_t i = 0; i < P2releases.size(); i++)
    {
        myfile << std::setprecision(10) << std::fixed << P2releases[i];
        myfile << "\n";
    }
    myfile.close();
}

void AmethystMacro::resetActions(bool recording) {
    if (PlayLayer::get()->m_isPracticeMode && recording) {
        if (P1checkpoints.size() > 0) P1checkpoints.back().apply(GJBaseGameLayer::get()->m_player1);
		if (P2checkpoints.size() > 0) P2checkpoints.back().apply(GJBaseGameLayer::get()->m_player2);

        if (checkpointFrames.size() == 0) checkpointFrames.push_back(0);
        currentFrame = checkpointFrames.back();

        if (P1pushes.size() > 0) {
            while (P1pushes.back() >= currentFrame && P1pushes.size() != 0) {
                P1pushes.pop_back();
            }
        }

        if (P1releases.size() > 0) {
            while (P1releases.back() >= currentFrame && P1releases.size() != 0) {
                P1releases.pop_back();
            }
        }

		if (P2pushes.size() > 0) {
            while (P2pushes.back() >= currentFrame && P2pushes.size() != 0) {
                P2pushes.pop_back();
            }
        }

        if (P2releases.size() > 0) {
            while (P2releases.back() >= currentFrame && P2releases.size() != 0) {
                P2releases.pop_back();
            }
        }

        if (P1pushing) P1pushes.push_back(currentFrame);
		if (P2pushing) P2pushes.push_back(currentFrame);

        log::info("[reset] currentFrame: {}", currentFrame);
    } else {
        currentP1index = 0;
        currentR1index = 0;
		currentP2index = 0;
        currentR2index = 0;
        currentFrame = 0;
        //if (profile.replay) GJBaseGameLayer::get()->releaseButton(1, true);
		//if (profile.replay) GJBaseGameLayer::get()->releaseButton(1, false);
    }
}

void AmethystMacro::updateReplay(float dt, bool replay) {
    currentFrame += dt;

    if (replay) {
        if (P1pushes.size() > 0) {
            if (P1pushes[currentP1index] <= currentFrame && currentP1index < P1pushes.size()) {
                GJBaseGameLayer::get()->pushButton(1, true);
                currentP1index++;
            }

            if (P1releases[currentR1index] <= currentFrame && currentR1index < P1releases.size()) {
                GJBaseGameLayer::get()->releaseButton(1, true);
                currentR1index++;
            }
        }

        if (P2pushes.size() > 0) {
            if (P2pushes[currentP2index] <= currentFrame && currentP2index < P2pushes.size()) {
                GJBaseGameLayer::get()->pushButton(1, false);
                currentP2index++;
            }

            if (P2releases[currentR2index] <= currentFrame && currentR2index < P2releases.size()) {
                GJBaseGameLayer::get()->releaseButton(1, false);
                currentR2index++;
            }
        }
    }
}

void AmethystMacro::createCheckpointData() {
    if (!PlayLayer::get()->m_isDead) {
        P1checkpoints.push_back(store(PlayLayer::get()->m_player1));
        P2checkpoints.push_back(store(PlayLayer::get()->m_player2));
        checkpointFrames.push_back(currentFrame);
    }
}

void AmethystMacro::removeCheckpointData() {
    P1checkpoints.pop_back();
    P2checkpoints.pop_back();
    checkpointFrames.pop_back();
}

void AmethystMacro::clearData() {
    P1pushes.clear();
    P1releases.clear();
    P2pushes.clear();
    P2releases.clear();
    checkpointFrames.clear();
    P1checkpoints.clear();
    P2checkpoints.clear();
}

void AmethystMacro::setPushingData(bool pushing, bool b) {
    if (pushing) {
        if (b) P1pushing = true;
		if (!b) P2pushing = true;
        log::info("[pushing] currentFrame: {}", currentFrame);
        if (b) P1pushes.push_back(currentFrame);
		if (!b) P2pushes.push_back(currentFrame);
    } else  {
        if (b) P1pushing = false;
		if (!b) P2pushing = false;
        log::info("[releasing] currentFrame: {}", currentFrame);
        if (b) P1releases.push_back(currentFrame);
		if (!b) P2releases.push_back(currentFrame);
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
    newcp.holding = player->m_isHolding;
    newcp.justHeld = player->m_hasJustHeld;
    newcp.holding2 = player->m_isHolding2;
    newcp.justHeld2 = player->m_hasJustHeld2;
    newcp.sliding = player->m_isSliding;
    newcp.rising = player->m_isRising;
    newcp.robotJump = player->m_canRobotJump;
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

