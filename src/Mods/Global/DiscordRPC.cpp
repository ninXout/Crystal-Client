#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "../../CrystalClient/CrystalClient.hpp"

#include <discord_register.h>
#include <discord_rpc.h>

#include <iostream>
#include <chrono>
#include <type_traits>

using namespace CrystalClient;

static const char* APPLICATION_ID = "1178492879627366472";

// using some of TechStudent10's things because im lazyyyyyyyy

static void handleDiscordReady(const DiscordUser* user) {
	log::info("Connected to Discord RPC");
	log::info("Username: {}", user->username);
	log::info("UserID: {}", user->userId);
}

static void handleDiscordError(int errorCode, const char* message) {
	log::info("Discord RPC error");
	log::info("Error Code: {}", std::to_string(errorCode));
	log::info("Message: {}", std::string(message));
}

static void handleDiscordDisconnected(int errorCode, const char* message) {
	log::info("Discord RPC disconnected");
	log::info("Error Code: {}", std::to_string(errorCode));
	log::info("Message: {}", std::string(message));
}

static void initDiscordRP() {
	DiscordEventHandlers handlers;
	handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, "322170");
	Discord_RunCallbacks();

}

void updateDiscordRP(std::string details, std::string state = "", std::string smallImageKey = "", std::string smallImageText = "") {
	auto gm = GameManager::sharedState();
	DiscordRichPresence discordPresence{};
    discordPresence.details = details.c_str();
    discordPresence.state = state.c_str();
    discordPresence.largeImageKey = "gd_large";
    discordPresence.largeImageText = gm->m_playerName.c_str();
	if (smallImageKey != "") {
		discordPresence.smallImageKey = smallImageKey.c_str();
		discordPresence.smallImageText = smallImageText.c_str();
	}
    discordPresence.instance = 0;
    if (getSavedVar<bool>("discord_rpc")) Discord_UpdatePresence(&discordPresence);
}

std::chrono::seconds getTimeInSec() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
}

std::string secToString(std::chrono::seconds second) {
    int min = second.count() / 60;
    int sec = second.count() % 60;
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << min;
    stream << ":";
    stream << std::setfill('0') << std::setw(2) << sec;
    stream << " elapsed";
    return stream.str();
}

std::string convertGJDifficultyDemonToAssetKey(int difficulty) {
    switch (difficulty) {
        case 3:
            return "easy_demon";
        case 4:
            return "medium_demon";
        case 0:
            return "hard_demon";
        case 5:
            return "insane_demon";
        case 6:
            return "extreme_demon";
    }
    return "na";
}

std::string convertGJDifficultyToAssetKey(GJDifficulty difficulty) {
	switch (static_cast<int>(difficulty)) {
		case -1:
			return "auto";
		case 0:
			return "na";
		case static_cast<int>(GJDifficulty::Easy):
			return "easy";
		case static_cast<int>(GJDifficulty::Normal):
			return "normal";
		case static_cast<int>(GJDifficulty::Hard):
			return "hard";
		case static_cast<int>(GJDifficulty::Harder):
			return "harder";
		case static_cast<int>(GJDifficulty::Insane):
			return "insane";
	}
	return "na";
}

std::string convertRobTopLevelToAssetKey(int lvlID) {
	switch (lvlID) {
		case 1:
			return "easy"; // Stereo Madness
		case 2:
			return "easy"; // Back On Track
		case 3:
			return "normal"; // Polargeist
		case 4:
			return "normal"; // Dry Out
		case 5:
			return "hard"; // Base After Base
		case 6:
			return "hard"; // Can't Let Go
		case 7:
			return "harder"; // Jumper
		case 8:
			return "harder"; // Time Machine
		case 9:
			return "harder"; // Cycles
		case 10:
			return "insane"; // xStep
		case 11:
			return "insane"; // Clutterfunk
		case 12:
			return "insane"; // Theory of Everything
		case 13:
			return "insane"; // Electroman Adventures
		case 14:
			return "hard_demon"; // Clubstep
		case 15:
			return "insane"; // Electrodynamix
		case 16:
			return "insane"; // Hexagon Force
		case 17:
			return "harder"; // Blast Processing
		case 18:
			return "hard_demon"; // TOE 2
		case 19:
			return "harder"; // Geometrical Dominator
		case 20:
			return "hard_demon"; // Deadlocked
		case 21:
			return "insane"; // Fingerdash
		case 22:
			return "insane"; // Dash
		case 23:
			return "hard_demon"; // Explorers
		case 3001:
			return "hard"; // The Challenge
	}
}

std::string getAssetKey(GJGameLevel* level) {
	int stars = level->m_stars.value();
	auto difficulty = level->m_difficulty;
	log::info(std::to_string(level->m_levelID.value()));
	if (stars == 0) {
		return convertGJDifficultyToAssetKey(difficulty);
	}
	if (stars == 10) {
		return convertGJDifficultyDemonToAssetKey(level->m_demonDifficulty);
	}
	if (level->m_levelID.value() < 128 || level->m_levelID.value() == 3001) {
		return convertRobTopLevelToAssetKey(level->m_levelID.value());
	}

	switch (stars) {
		case 1:
			return "auto";
		case 2:
			return "easy";
		case 3:
			return "normal";
		case 4:
			return "hard";
		case 5:
			return "hard";
		case 6:
			return "harder";
		case 7:
			return "harder";
		case 8:
			return "insane";
		case 9:
			return "insane";
	}
	return "na";
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		initDiscordRP();
		updateDiscordRP("Browsing Menus");

		return true;
	}
};

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) return false;
		updateDiscordRP("Browsing Menus", "Creator Tab");
		return true;
	}
};

class $modify(LevelSearchLayer) {
	bool init() {
		if (!LevelSearchLayer::init()) return false;
		updateDiscordRP("Browsing Menus", "Search Tab");
		return true;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level) {
		if (!LevelInfoLayer::init(level)) return false;

		bool isRated = level->m_stars.value() != 0;
		
		updateDiscordRP(
			"Viewing Level",
			std::string(level->m_levelName) + " by " + std::string(level->m_creatorName),
			getAssetKey(level),
			(isRated) ? "Rated" : "Not Rated"
		);
		return true;
	}
};

class $modify(MyLevelEditorLayer, LevelEditorLayer) {
	bool init(GJGameLevel* level) {
		if (!LevelEditorLayer::init(level)) return false;

		MyLevelEditorLayer::updateStatus();

		return true;
	}

	void updateStatus() {
		updateDiscordRP("Working on a level", std::to_string(m_level->m_objectCount.value()) + " Objects");
	}

	GameObject* createObject(int objectID, CCPoint pos, bool p2) {
		auto object = LevelEditorLayer::createObject(objectID, pos, p2);
		updateStatus();
		return object;
	}

	void removeObject(GameObject* object, bool p1) {
		LevelEditorLayer::removeObject(object, p1);
		updateStatus();
	}
};

class $modify(MyPlayLayer, PlayLayer) {
    std::chrono::seconds elapsed_start;

	bool init(GJGameLevel* level) {
		if (!PlayLayer::init(level)) return false;

        elapsed_start = getTimeInSec();

		this->schedule(schedule_selector(MyPlayLayer::updateRP));

		return true;
	}

	void showNewBest(bool p0, int p1, int p2, bool p3, bool p4, bool p5) {
		PlayLayer::showNewBest(p0, p1, p2, p3, p4, p5);

		updateRP();
	}

	void resetLevel() {
		PlayLayer::resetLevel();
		updateRP();
	}

	void levelComplete() {
		PlayLayer::levelComplete();
		updateRP();
	}

    void updateRP() {
        bool isRated = m_level->m_stars.value() != 0;
        auto shouldShowSensitive = Mod::get()->getSettingValue<bool>("private-info");

        std::string state;

        bool isRobTopLevel = m_level->m_levelID.value() < 128 || m_level->m_levelID.value() == 3001;

        if (m_level->m_levelType != GJLevelType::Editor || shouldShowSensitive) {
            state = std::string(m_level->m_levelName) + " by " + ((isRobTopLevel) ? "RobTopGames" : std::string(m_level->m_creatorName)) + " (" + std::to_string(m_level->m_normalPercent.value()) + "%)";
        } else if (!shouldShowSensitive) {
            state = "Playtesting a created level";
        }

        updateDiscordRP(
            std::string("Playing ") + state,
            secToString(getTimeInSec() - elapsed_start),
            getAssetKey(m_level),
            (isRated) ? "Rated" : "Not Rated"
        );
    }
};