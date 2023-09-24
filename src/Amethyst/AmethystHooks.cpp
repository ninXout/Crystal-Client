#include "Amethyst.hpp"
#include "../CrystalProfile.hpp"
#include "../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/CheckpointObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

class $modify(CheckpointObject) {
	static CheckpointObject* create() {
		auto cpo = CheckpointObject::create();

		if (getVar<bool>("AT_record")) currentMacro.createCheckpointData();

		return cpo;
	}
};

class $modify(PlayLayer) {
    bool init(GJGameLevel* gl) {
        *setTempVar<bool>("gameStarted") = false;

        if (!PlayLayer::init(gl)) return false;

        if (getVar<bool>("clickbot")) {
			Clickbot::start = std::chrono::system_clock::now();

			if (!ghc::filesystem::exists(Clickbot::clicksCB) || !ghc::filesystem::exists(Clickbot::softC) 
			|| !ghc::filesystem::exists(Clickbot::releasesCB) || !ghc::filesystem::exists(Clickbot::softR)) {
				CrystalClient::get()->noFoldersCB(this);
			} else if (Clickbot::pickRandomClick() == "This folder is empty!" || Clickbot::pickRandomSoftClick() == "This folder is empty!" 
				|| Clickbot::pickRandomRelease() == "This folder is empty!" || Clickbot::pickRandomSoftRelease()  == "This folder is empty!") {
					CrystalClient::get()->emptyFoldersCB(this);
			}
		}

        return true;
    }

    void update(float dt) {
		PlayLayer::update(dt);

		if ((getVar<bool>("AT_replay") || getVar<bool>("AT_record")) && getTempVar<bool>("gameStarted")) currentMacro.updateReplay(dt, getVar<bool>("AT_replay"));
    }

#ifdef GEODE_IS_MACOS
    void startGame() {
		PlayLayer::startGame();
		*setTempVar<bool>("gameStarted") = true;
	}
#endif

    void resetLevel() {
		PlayLayer::resetLevel();

		if (getVar<bool>("AT_replay") || getVar<bool>("AT_record")) currentMacro.resetActions(getVar<bool>("AT_record"));
	}

    void removeLastCheckpoint() {
		PlayLayer::removeLastCheckpoint();
		if (getVar<bool>("AT_record")) currentMacro.removeCheckpointData();
	}
};

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		currentMacro.setPushingData(true, b);
        if (getVar<bool>("clickbot")) {
            if (!Clickbot::inited) {
                FMOD::System_Create(&Clickbot::system);
                Clickbot::system->init(1024 * 2, FMOD_INIT_NORMAL, nullptr);
                Clickbot::inited = true;
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
            Clickbot::clickChannel->setVolume((float)(getVar<float>("clickbot_volume") / 100));
            Clickbot::clickChannel->setPaused(false);
            Clickbot::system->update();
        }
		GJBaseGameLayer::pushButton(i,b);
	}

	void releaseButton(int i, bool b) {
		currentMacro.setPushingData(false, b);
		if (getVar<bool>("clickbot")) {
			if (Clickbot::cycleTime.count() < 0.5f) {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			} else {
				std::string path = Clickbot::pickRandomRelease();
				Clickbot::system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &Clickbot::releaseSound);
			}
			
			
			Clickbot::system->playSound(Clickbot::releaseSound, nullptr, true, &Clickbot::releaseChannel);
			Clickbot::releaseChannel->setVolume((float)(getVar<float>("clickbot_volume") / 100));
			Clickbot::releaseChannel->setPaused(false);
			Clickbot::system->update();
		}
        GJBaseGameLayer::releaseButton(i,b);
	}
};
