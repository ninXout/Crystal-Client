#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::setDefaultDisplay(11, "N/A");

        if (!PlayLayer::init(gj)) return false;

        Display::updateDisplay(11);
        Display::addDisplayChildren(11, this);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        std::string levelInfo;
        std::string levelName = m_level->m_levelName;
        std::string levelAuthor = m_level->m_creatorName;
        std::string levelID = std::to_string(m_level->m_levelID);			
        if (m_level->m_levelID == 0) {
            levelID = "Copy";
        }
        if (m_level->m_levelID < 22 && m_level->m_levelID > 0) {
            levelAuthor = "RobTop"; 
        }

        if (getSavedVar<bool>("hide_ID") && !getSavedVar<bool>("level_info_author")) {
            levelInfo = levelName;
        } else if (getSavedVar<bool>("hide_ID") && getSavedVar<bool>("level_info_author")) {
            levelInfo = levelName + " by " + levelAuthor;
        } else {
            levelInfo = levelName + " (" + levelID + ")";
        }
        
        if (getSavedVar<bool>("level_info")) Display::getDisplay(11)->setString(levelInfo.c_str());
    }
};