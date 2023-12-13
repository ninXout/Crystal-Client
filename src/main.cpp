#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include "CrystalUI/CrystalUI.hpp"
#include "CrystalClient/CrystalClient.hpp"
#include "Mods/Keybind/Keybind.hpp"
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
		ImGui::Begin(" ", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 183);
		CrystalUI::renderLogo();
		ImGui::Spacing();
		CrystalUI::renderTabs();
		CrystalUI::renderUser();
		CrystalUI::renderRightColumn();
		//if (ImGui::GetIO().WantCaptureKeyboard) {
			//CrystalUI::selectedTab = 10;
		//}
		ImGui::End();
		ImGui::PopFont();
    });
	ImGuiCocos::get().toggle();
	CrystalClient::loadConfig();
	Keybinds::keybind.clear();
	if (CrystalClient::modsMapKEY.size() > 0) {
		for (auto [k, v] : CrystalClient::modsMapKEY) {
			Keybinds::keybind.push_back({(cocos2d::enumKeyCodes)k, v});
		}
	}
	AppDelegate::get()->setAnimationInterval(1.0 / getSavedVar<float>("FPS"));
}

class $modify(CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
        if (down && key == KEY_Tab) {
            ImGuiCocos::get().toggle();
			if (ImGuiCocos::get().isVisible()) {
				CrystalClient::loadConfig();
				Keybinds::keybind.clear();
				if (CrystalClient::modsMapKEY.size() > 0) {
					for (auto [k, v] : CrystalClient::modsMapKEY) {
						Keybinds::keybind.push_back({(cocos2d::enumKeyCodes)k, v});
					}
				}
			} else {
				CrystalClient::saveConfig();
				AppDelegate::get()->setAnimationInterval(1.0 / getSavedVar<float>("FPS"));
			}
            return true;
        }
		if (down && CrystalUI::waitingForKey) {
			CrystalUI::queuedKey = key;
			CrystalUI::waitingForKey = false;
			return true;
		}
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
    }
};