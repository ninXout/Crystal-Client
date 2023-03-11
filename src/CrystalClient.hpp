#pragma once

#include "platform/platform.hpp"
#include <imgui.h>
#include "themes.hpp"
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>

USE_GEODE_NAMESPACE();

enum class HighlightMode {
    Selected,
    Hovered,
};

class CrystalClient : public cocos2d::CCLayer, cocos2d::CCIMEDelegate {
    bool m_ime_attached = false;
protected:
    bool m_visible = false;
    bool m_setup = false;
    bool m_reloadTheme = true;
    bool m_GDInWindow = true;
    bool m_attributesInTree = false;
    bool m_alwaysHighlight = true;
    bool m_shouldRelayout = false;
    std::string m_theme = DARK_THEME;
    ImGuiID m_dockspaceID;
    ImFont* m_defaultFont  = nullptr;
    ImFont* m_smallFont    = nullptr;
    ImFont* m_monoFont     = nullptr;
    ImFont* m_boxFont      = nullptr;
    Ref<CCNode> m_selectedNode;
    std::vector<std::pair<CCNode*, HighlightMode>> m_toHighlight;

    void setupFonts();
    void setupPlatform();

    static void ImToggleable(const char* label, bool* toggle);
    static void ImExtendedToggleable(const char* str_id, bool* v);
    void drawPages();
    void draw(GLRenderCtx* ctx);
    bool canAttachWithIME() override;
    bool canDetachWithIME() override;
    void keyDown(cocos2d::enumKeyCodes key) override;
	void keyUp(cocos2d::enumKeyCodes key) override;
    void insertText(const char* text, int len) override;
	void deleteBackward() override;

    void newFrame();
    void renderDrawData(ImDrawData*);

public:
    bool isMenuOpen = false;
    float g = 0;

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
    void applyTheme(std::string const& name);

    static CrystalClient* get();

    bool shouldPopGame() const;

    CCNode* getSelectedNode() const;
    void selectNode(CCNode* node);
    void highlightNode(CCNode* node, HighlightMode mode);

    void sceneChanged();

    void render(GLRenderCtx* ctx);

    // setup ImGui
    void setup();

    void show(bool visible);
    void toggle();
};