#pragma once

#include <imgui.h>
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>

USE_GEODE_NAMESPACE();

enum class HighlightMode {
    Selected,
    Hovered,
};

class CrystalClient : public cocos2d::CCLayer, cocos2d::CCIMEDelegate {
protected:
    bool m_visible = false;
    bool m_setup = false;
    ImFont* m_defaultFont  = nullptr;

    void setupFonts();
    void setupPlatform();

    static void ImToggleable(const char* label, bool* toggle);
    static void ImExtendedToggleable(const char* str_id, bool* v);
    void drawPages();
    void draw();
    void keyDown(cocos2d::enumKeyCodes key) override;
	void keyUp(cocos2d::enumKeyCodes key) override;
    void insertText(const char* text, int len) override;
	void deleteBackward() override;

    void newFrame();
    void renderDrawData(ImDrawData*);

public:
    bool isMenuOpen = false;
    float g = 0;

    static std::string getRenderPath(bool full);
    static std::string getSongCmdStr(std::string songOffset, std::string songPath, std::string tempPath, std::string time, std::string path);
    static cocos2d::enumKeyCodes shortcutKey(int key);
    float getTimeForXPos(PlayLayer*);
    void loadShortcuts();
    void saveShortcuts();
    void loadMods();
    void saveMods();
    void arrangeText(int arrayLength);
    void openMenu();
    void closeMenu();
    void setAnchoredPosition(CCNode* label, int anchorPos);
    void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
    cocos2d::_ccColor3B getRainbow(float offset);
    void applyTheme();
    static bool getMod(const char* name);
    static void setMod(const char* name, bool b);

    static CrystalClient* get();

    void render();

    // setup ImGui
    void setup();

    void show(bool visible);
    void toggle();
};