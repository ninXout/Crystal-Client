#include <imgui_internal.h>
#include "CrystalClient.hpp"
#include "fonts/OpenSans.hpp"
#include "fonts/GeodeIcons.hpp"
#include "fonts/RobotoMono.hpp"
#include "fonts/SourceCodeProLight.hpp"
#include "platform/platform.hpp"
#include <Geode/loader/Log.hpp>
#include "ImGui.hpp"

CrystalClient* CrystalClient::get() {
    static auto inst = new CrystalClient;
    return inst;
}

void CrystalClient::draw(GLRenderCtx* ctx) {
    if (m_visible) {
        this->applyTheme(m_theme);

        ImGui::PushFont(m_defaultFont);
        this->drawPages();
        ImGui::PopFont();
    }
}

void CrystalClient::setupFonts() {
    static const ImWchar* def_ranges   = ImGui::GetIO().Fonts->GetGlyphRangesDefault();
    
    static constexpr auto add_font = [](
        void* font, float size, const ImWchar* range
    ) {
        auto& io = ImGui::GetIO();
        ImFontConfig config;
        config.MergeMode = true;
        auto* result = io.Fonts->AddFontFromFileTTF("Verdana.ttf", 14.0f);
        io.Fonts->Build();
        return result;
    };

    m_defaultFont = add_font(Font_OpenSans, 18.f, def_ranges);
    m_smallFont = add_font(Font_OpenSans, 10.f, def_ranges);
    m_monoFont = add_font(Font_RobotoMono, 18.f, def_ranges);
}

void CrystalClient::setup() {
    if (m_setup) return;
    m_setup = true;

    IMGUI_CHECKVERSION();
    
    ImGui::CreateContext();
    
    auto& io = ImGui::GetIO();

    this->setupFonts();
    this->setupPlatform();
}

void CrystalClient::show(bool visible) {
    m_visible = visible;
    isMenuOpen = visible;
}

void CrystalClient::sceneChanged() {
    m_selectedNode = nullptr;
}