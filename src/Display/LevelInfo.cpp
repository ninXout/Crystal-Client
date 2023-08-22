#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>
/*
class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[11] = CCLabelBMFont::create("N/A", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(11, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[11]->setVisible(getVar<bool>("level_info"));

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
            levelInfo = levelName + " (" + levelID + ")";
        }
        
        if (getVar<bool>("level_info")) {
            labels[11]->setString(levelInfo.c_str());
        }
    }
};*/