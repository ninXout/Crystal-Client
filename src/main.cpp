#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include "CrystalUI/CrystalUI.hpp"
#include "CrystalClient/CrystalClient.hpp"
#include <imgui-cocos.hpp>
#include <imgui.h>

using namespace geode::prelude;
using namespace CrystalClient;

$execute {
	ImGuiCocos::get().setup([] {
        ImGuiCocos::get().setInputMode(ImGuiCocos::InputMode::Blocking);
        CrystalUI::setupFonts();
		CrystalUI::setupTheme();
    }).draw([] {
       	ImGui::SetNextWindowSize({ 800, 600 });
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f,0.5f));
		ImGui::PushFont(CrystalUI::font);
		ImGui::GetStyle().WindowRounding = 15.f;
		ImGui::Begin(" ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 183);
		CrystalUI::renderLogo();
		ImGui::Spacing();
		CrystalUI::renderTabs();
		CrystalUI::renderUser();
		CrystalUI::renderRightColumn();
		ImGui::End();
		ImGui::PopFont();
    });
	ImGuiCocos::get().toggle();
}

class $modify(CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        if (down && key == KEY_Tab) {
            ImGuiCocos::get().toggle();
            return true;
        }
		/*
		if (down && ImGuiCocos::get().isVisible()) {
			switch (key) {
				default: break;
				case KEY_One:
					CrystalUI::selectedTab = 0;
					break;
				case KEY_Two:
					CrystalUI::selectedTab = 1;
					break;
				case KEY_Three:
					CrystalUI::selectedTab = 2;
					break;
				case KEY_Four:
					CrystalUI::selectedTab = 3;
					break;
				case KEY_Five:
					CrystalUI::selectedTab = 4;
					break;
				case KEY_Six:
					CrystalUI::selectedTab = 5;
					break;
				case KEY_Seven:
					CrystalUI::selectedTab = 6;
					break;
				case KEY_Eight:
					CrystalUI::selectedTab = 7;
					break;
				case KEY_Nine:
					CrystalUI::selectedTab = 8;
					break;
			}
			return true;
		}*/
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};