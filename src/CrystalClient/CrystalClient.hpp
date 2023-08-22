#pragma once

#include <imgui.h>
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>
#include <dispatch/dispatch.h>

using namespace geode::prelude;

class CrystalClient {
protected:
    ImFont* m_defaultFont;

    static void ImToggleable(const char* label, bool* toggle);
    static void ImSelectable(const char* label, int* toggle, int value);
    static void ImExtendedToggleable(const char* str_id, bool* v);
    static void ImIconEffect(bool* mainBool, bool* staticBool, bool* fadeBool, bool* rainbowBool, float* staticC, float* fade1, float* fade2, const char* categoryName);

    void setupFonts(const char* filepath, float size);

public:
    static CrystalClient* get();

    void render();
    void saveToFile();
    void loadFromFile();

    void drawGUI();
    void addTheme();

    void firstLoad(CCNode* layer);
    void noImage(CCNode* layer);

    static cocos2d::enumKeyCodes shortcutKey(int key);
    float getTimeForXPos(PlayLayer*);
    void arrangeText(int arrayLength, PlayLayer* menulay, bool first);
    void setAnchoredPosition(CCLabelBMFont* label, int anchorPos, CCLayer* layer, bool first);
    void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
    cocos2d::_ccColor3B getRainbow(float offset);
    static void addTransparentBG(CCNode* layer);
    void GameTime();
    
    void initPatches();
    void refreshPatches();

    geode::Patch *scaleHack1;
    geode::Patch *scaleHack2;

    geode::Patch *objLimit1;
    geode::Patch *objLimit2;
    geode::Patch *objLimit3;

    geode::Patch *customObjLimit1;
    geode::Patch *customObjLimit2;
    geode::Patch *customObjLimit3;

    std::vector<const char*> plugins;
    std::vector<bool*> pluginBools;
};