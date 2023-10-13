#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
#include "Display.hpp"

class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        Display::get()->setDefaultDisplay(11, "N/A");

        if (!PlayLayer::init(gj)) return false;

        Display::get()->arrangeDisplay(11);
        Display::get()->addDisplayChildren(11, this);
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

        if (getVar<bool>("hide_ID") && !getVar<bool>("level_info_author")) {
            levelInfo = levelName;
        } else if (getVar<bool>("hide_ID") && getVar<bool>("level_info_author")) {
            levelInfo = levelName + " by " + levelAuthor;
        } else {
            levelInfo = levelName + " ( ID:" + levelID + ")";
        }
        
        if (getVar<bool>("level_info")) Display::get()->getDisplay(11)->setString(levelInfo.c_str());
    }
};
