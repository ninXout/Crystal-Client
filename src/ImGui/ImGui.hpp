#pragma once

#include <cocos2d.h>
#include <functional>
#include <string>
#include <imgui.h>

class ImGuiCocos {
private:
    cocos2d::CCTexture2D* m_fontTexture = nullptr;
    bool m_initialized = false;
    bool m_visible = true;
    std::function<void()> m_setupCall, m_drawCall;

    ImGuiCocos();

    void newFrame();
    void renderFrame();
public:
    ImGuiCocos(const ImGuiCocos&) = delete;
    ImGuiCocos(ImGuiCocos&&) = delete;

    static ImGuiCocos& get();

    // called on mod unloaded
    void destroy();
    // called on swapBuffers
    void drawFrame();

    ImGuiCocos& setup(std::function<void()> fun);
    ImGuiCocos& setup();

    ImGuiCocos& draw(std::function<void()> fun);

    void toggle();
    bool isVisible();
    void setVisible(bool v);
	
	static ImVec2 cocosToFrame(const cocos2d::CCPoint& pos);
	static cocos2d::CCPoint frameToCocos(const ImVec2& pos);
};