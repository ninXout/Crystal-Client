#pragma once

#include <imgui.h>
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>

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

    static std::string getRenderPath(bool full);
    static cocos2d::enumKeyCodes shortcutKey(int key);
    float getTimeForXPos(PlayLayer*);
    void arrangeText(int arrayLength, PlayLayer* menulay);
    void setAnchoredPosition(CCLabelBMFont* label, int anchorPos, CCLayer* layer);
    void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
    cocos2d::_ccColor3B getRainbow(float offset);
    static void getTextPos(CCNode* label, int anchor);
    void addTransparentBG(CCNode* layer);
    
    void initPatches();

    // setup ImGui
    void setup();

    void show(bool visible);
    void toggle();
};