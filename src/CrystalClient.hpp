#pragma once

#include <imgui.h>
#include <cocos2d.h>
#include <Geode/utils/cocos.hpp>
#include <unordered_map>

USE_GEODE_NAMESPACE();

class CrystalClient {
protected:
    bool m_visible = false;
    bool m_setup = false;
    ImFont* m_defaultFont  = nullptr;

    void setupFonts(const char* filepath, float size);
    void setupPlatform();
    static void ImToggleable(const char* label, bool* toggle);
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
    void arrangeText(int arrayLength);
    void setAnchoredPosition(CCNode* label, int anchorPos);
    void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
    cocos2d::_ccColor3B getRainbow(float offset);

    // setup ImGui
    void setup();

    void show(bool visible);
    void toggle();
};

namespace CrystalTheme {
    static inline float rDir = -0.05;
    static inline float gDir = 0.05;
    static inline float bDir = -0.05;

    static inline float BGColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    static inline float LightColour[4] = { 0.262715f,
                            0.624691f,
                            0.818605f,
                            1.0f };
    static inline float DarkColour[4];
    static inline float VeryLightColour[4];

    static ImVec4 RGBAtoIV4(float rgb[4]) {
        float newr = rgb[0];
        float newg = rgb[1];
        float newb = rgb[2];
        float newa = rgb[3];
        return ImVec4(newr, newg, newb, newa);
    }
}