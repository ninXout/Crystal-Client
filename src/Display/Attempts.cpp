#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

/*class $modify(PlayLayer) {
    bool init(GJGameLevel* gj) {
        labels[5] = CCLabelBMFont::create("0 Attempts", "bigFont.fnt");

        if (!PlayLayer::init(gj)) return false;

        CrystalClient::get()->arrangeText(5, this, true);
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);

        labels[5]->setVisible(getVar<bool>("attempts"));
    }

    void resetLevel() {
        PlayLayer::resetLevel();

        int attempt;

        if (getVar<bool>("total_attempts")) attempt = m_level->m_attempts;
        else attempt = m_currentAttempt;

        std::string attempts = std::to_string(attempt) + " Attempts";
        if (getVar<bool>("attempts")) {
            labels[5]->setString(attempts.c_str());
        }
    }
};*/