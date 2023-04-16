#include "Amethyst.hpp"
#include "CrystalProfile.hpp"
#include <Geode/Geode.hpp>

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

namespace fs = ghc::filesystem;

AmethystReplay::AmethystFrame AmethystReplay::create() {
    AmethystReplay::AmethystFrame newframe;
    newframe.xpos = GJBaseGameLayer::get()->m_player1->m_position.x;
    newframe.ypos = GJBaseGameLayer::get()->m_player1->m_position.y;
    newframe.accel = GJBaseGameLayer::get()->m_player1->m_yAccel;
    return newframe;
}

AmethystReplay::CheckpointData AmethystReplay::store() {
    AmethystReplay::CheckpointData newcp;
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

void AmethystReplay::newReplayFrame(bool isReplay, bool isRecord, int tps, int currentMacroType) {
    currentFrame = (int)(PlayLayer::get()->m_time * tps) + currentOffset;

    if (isRecord) frames.push_back(AmethystReplay::create());

    if (isReplay && frames.size() > 0) {
        if (currentPindex > pushes.size()) currentPindex--;
        if (currentRindex > releases.size()) currentRindex--;

        if (pushes[currentPindex] <= currentFrame) {
            GJBaseGameLayer::get()->pushButton(1, true);
            if (currentMacroType == 1) {
                pushData[currentPindex].apply(GJBaseGameLayer::get()->m_player1);
            }
            currentPindex++;
        }

        if (releases[currentRindex] <= currentFrame) {
            GJBaseGameLayer::get()->releaseButton(1, true);
            if (currentMacroType == 1) {
                releaseData[currentRindex].apply(GJBaseGameLayer::get()->m_player1);
            }
            currentRindex++;
        }
    }
}

void AmethystReplay::createFromFile(AmethystReplay* replay, char macroname[25]) {
    std::string line;
    std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/" + (std::string)macroname + ".thyst";
    std::fstream file;
    file.open(filename, std::ios::in);
    if (file.is_open()) {
        getline(file, line);
        int len;
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            replay->pushes.push_back(stof(line));
        }
        getline(file, line);
        len = stoi(line);
        for (int lineno = 1; lineno <= len; lineno++) {
            getline(file, line);
            replay->releases.push_back(stof(line));
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
            replay->pushData.push_back(newPush);
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
            replay->releaseData.push_back(newRel);
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
            replay->frames.push_back(newFrameDat);
        }
        file.close();
    }
}

void AmethystReplay::saveToFile(AmethystReplay* replay, char macroname[25]) {
    std::string filename = (std::string)geode::Mod::get()->getConfigDir() + "/" + (std::string)macroname + ".thyst";
    std::fstream myfile(filename.c_str(), std::ios::app);
    myfile << replay->pushes.size();
    myfile << "\n";
    for (size_t i = 0; i < replay->pushes.size(); i++)
    {
        myfile << std::setprecision(6) << std::fixed << replay->pushes[i];
        myfile << "\n";
    }
    myfile << replay->releases.size();
    myfile << "\n";
    for (size_t i = 0; i < replay->releases.size(); i++)
    {
        myfile << std::setprecision(6) << std::fixed << replay->releases[i];
        myfile << "\n";
    }
    // pushes
    myfile << replay->pushData.size();
    myfile << "\n";
    for (size_t i = 0; i < replay->pushData.size(); i++)
    {
        myfile << std::setprecision(6) << std::fixed << replay->pushData[i].xpos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->pushData[i].ypos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->pushData[i].accel;
        myfile << "\n";
    }
    // releases
    myfile << replay->releaseData.size();
    myfile << "\n";
    for (size_t i = 0; i < replay->releaseData.size(); i++)
    {
        myfile << std::setprecision(6) << std::fixed << replay->releaseData[i].xpos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->releaseData[i].ypos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->releaseData[i].accel;
        myfile << "\n";
    }
    // frames
    myfile << replay->frames.size();
    myfile << "\n";
    for (size_t i = 0; i < replay->frames.size(); i++)
    {
        myfile << std::setprecision(6) << std::fixed << replay->frames[i].xpos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->frames[i].ypos;
        myfile << "\n";
        myfile << std::setprecision(6) << std::fixed << replay->frames[i].accel;
        myfile << "\n";
    }
}

void AmethystReplay::adjustFrames(int tps, bool pushing, bool record) {
    if (PlayLayer::get()->m_isPracticeMode && record) {
        checkpoints.back().apply(GJBaseGameLayer::get()->m_player1);

        if (checkpointFrames.size() == 0) checkpointFrames.push_back(0);
        currentOffset = checkpointFrames.back();

        currentFrame = (int)(PlayLayer::get()->m_time * tps) + currentOffset;

        if (frames.size() > 0) {
            while (frames.size() >= currentFrame) {
                frames.pop_back();
            }
        }

        if (pushes.size() > 0) {
            while (pushes.back() >= currentFrame) {
                pushData.pop_back();
                pushes.pop_back();
            }
        }

        if (releases.size() > 0) {
            while (releases.back() >= currentFrame) {
                releaseData.pop_back();
                releases.pop_back();
            }
        }

        if (pushing) {
            pushData.push_back(AmethystReplay::create());
            pushes.insert(pushes.end(), currentFrame);
        }

    } else {
        currentPindex = 0;
        currentRindex = 0;
        currentIndex = 0;
        currentFrame = 0;
        currentOffset = 0;
        GJBaseGameLayer::get()->releaseButton(1, true);
    }
}

void AmethystReplay::addInput(bool pushButton, bool record, bool clickBot, bool inited) {
    if (pushButton) {
        if (record) {
            pushes.insert(pushes.end(), currentFrame);
            pushData.push_back(AmethystReplay::create());
        }
        if (clickBot) {
            if (!inited) {
                FMOD::System_Create(&Clickbot::system);
                Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, nullptr);
                inited = true;
            }

            Clickbot::now = std::chrono::system_clock::now();
            Clickbot::cycleTime = Clickbot::now - Clickbot::start;
            if (Clickbot::cycleTime.count() < 0.5f) {
                std::string path = Clickbot::pickRandomSoftClick();
                Clickbot::start = std::chrono::system_clock::now();
                std::cout << Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
            } else {
                std::string path = Clickbot::pickRandomClick();
                Clickbot::start = std::chrono::system_clock::now();
                Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::clickSound);
            }
            
            Clickbot::system->playSound(Clickbot::clickSound, nullptr, true, &Clickbot::clickChannel);
            Clickbot::clickChannel->setVolume((float)(250 / 100));
            Clickbot::clickChannel->setPaused(false);
            Clickbot::system->update();
        }
    } else {
        if (record) {
			releaseData.push_back(AmethystReplay::create());
			releases.insert(releases.end(), currentFrame);
		}
		if (clickBot) {
			if (Clickbot::cycleTime.count() < 0.5f) {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			} else {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			}
			
			
			Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
			Clickbot::releaseChannel->setVolume((float)(250 / 100));
			Clickbot::releaseChannel->setPaused(false);
			Clickbot::system->update();
		}
    }
}

void AmethystReplay::addCheckpoint(bool mark) {
    if (mark) {
        if (!PlayLayer::get()->m_isDead) {
            checkpoints.push_back(AmethystReplay::store());
            checkpointFrames.push_back(currentFrame);
        }
    } else {
        checkpoints.pop_back();
        checkpointFrames.pop_back();
    }
}