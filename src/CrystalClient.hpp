#pragma once

#include <imgui.h>
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>
#include <dispatch/dispatch.h>

using namespace geode::prelude;

class CrystalClient {
protected:
    bool m_visible = false;
    bool m_setup = false;
    ImFont* m_defaultFont  = nullptr;

    void setupFonts(const char* filepath, float size);
    void setupPlatform();
    static void ImToggleable(const char* label, bool* toggle);
    static void ImSelectable(const char* label, int* toggle, int value);
    static void ImExtendedToggleable(const char* str_id, bool* v);

    void drawGUI();
    void draw();
    void addTheme();

    void newFrame();
    void renderDrawData(ImDrawData*);

public:
    bool isRendering = false;

    static CrystalClient* get();

    void render();
    void saveToFile();
    void loadFromFile();

    void firstLoad(CCNode* layer);
    void noImage(CCNode* layer);

    static std::string getRenderPath(bool full);
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

    Result<geode::Patch *> scaleHack1;
    Result<geode::Patch *> scaleHack2;

    Result<geode::Patch *> objLimit1;
    Result<geode::Patch *> objLimit2;
    Result<geode::Patch *> objLimit3;

    Result<geode::Patch *> customObjLimit1;
    Result<geode::Patch *> customObjLimit2;
    Result<geode::Patch *> customObjLimit3;

    bool shouldLoadFont = false;

    std::vector<const char*> plugins;
    std::vector<bool*> pluginBools;

    // setup ImGui
    void setup();

    void show(bool visible);
    void toggle();
};