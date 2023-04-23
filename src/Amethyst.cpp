#include "Amethyst.hpp"
#include "CrystalProfile.hpp"
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = ghc::filesystem;

void AmethystReplay::saveToFile(std::string macroName) {
    std::fstream myfile(macroName.c_str(), std::ios::app);
		myfile << pushes.size();
		myfile << "\n";
		for (size_t i = 0; i < pushes.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << pushes[i];
			myfile << "\n";
		}
		myfile << releases.size();
		myfile << "\n";
		for (size_t i = 0; i < releases.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << releases[i];
			myfile << "\n";
		}
		// pushes
		myfile << pushData.size();
		myfile << "\n";
		for (size_t i = 0; i < pushData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << pushData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << pushData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << pushData[i].accel;
			myfile << "\n";
		}
		// releases
		myfile << releaseData.size();
		myfile << "\n";
		for (size_t i = 0; i < releaseData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << releaseData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << releaseData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << releaseData[i].accel;
			myfile << "\n";
		}
		// frames
		myfile << framesData.size();
		myfile << "\n";
		for (size_t i = 0; i < framesData.size(); i++)
		{
			myfile << std::setprecision(6) << std::fixed << framesData[i].xpos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << framesData[i].ypos;
			myfile << "\n";
			myfile << std::setprecision(6) << std::fixed << framesData[i].accel;
			myfile << "\n";
		}
}

void AmethystReplay::loadFromFile(std::string macroName) {
    std::string line;
		std::fstream file;
		file.open(macroName, std::ios::in);
		if (file.is_open()) {
			getline(file, line);
			int len;
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				pushes.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				getline(file, line);
				releases.push_back(stof(line));
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newPush;
				getline(file, line);
				newPush.xpos = stof(line);
				getline(file, line);
				newPush.ypos = stof(line);
				getline(file, line);
				newPush.accel = stod(line);
				pushData.push_back(newPush);
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newRel;
				getline(file, line);
				newRel.xpos = stof(line);
				getline(file, line);
				newRel.ypos = stof(line);
				getline(file, line);
				newRel.accel = stod(line);
				releaseData.push_back(newRel);
			}
			getline(file, line);
			len = stoi(line);
			for (int lineno = 1; lineno <= len; lineno++) {
				AmethystReplay::AmethystFrame newFrameDat;
				getline(file, line);
				newFrameDat.xpos = stof(line);
				getline(file, line);
				newFrameDat.ypos = stof(line);
				getline(file, line);
				newFrameDat.accel = stod(line);
				framesData.push_back(newFrameDat);
			}
			file.close();
		}
}

void AmethystReplay::clearMacro() {
    pushes.clear();
    releases.clear();
    pushData.clear();
    releaseData.clear();
    framesData.clear();
    checkpointFrames.clear();
    checkpoints.clear();
}

AmethystReplay::AmethystFrame AmethystReplay::create() {
    AmethystReplay::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newframe.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newframe.accel = GJBaseGameLayer::get()->m_player1->m_yAccel;
    return newframe;
}

CheckpointData store() {
    CheckpointData newcp;
    newcp.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newcp.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newcp.rot = GJBaseGameLayer::get()->m_player1->getRotation();
    newcp.yaccel = GJBaseGameLayer::get()->m_player1->m_yAccel;
    newcp.xaccel = GJBaseGameLayer::get()->m_player1->m_xAccel;
    newcp.jump_accel = GJBaseGameLayer::get()->m_player1->m_jumpAccel;
    newcp.isUpsideDown = GJBaseGameLayer::get()->m_player1->m_isUpsideDown;
    newcp.vehicle_size = GJBaseGameLayer::get()->m_player1->m_vehicleSize;
    newcp.player_speed = GJBaseGameLayer::get()->m_player1->m_playerSpeed;
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

