#include <imgui_internal.h>
#include "CrystalClient.hpp"
#include <Geode/loader/Log.hpp>
#include <Geode/loader/Mod.hpp>
#include "../json.hpp"
#include "../CrystalProfile.hpp"
#include "../Shortcuts.hpp"
#include "../Renderer/Renderer.hpp"

using namespace geode::prelude;
using namespace AmethystReplay;

CrystalClient* CrystalClient::get() {
    static auto inst = new CrystalClient;
    return inst;
}

void CrystalClient::setupFonts(const char* filepath, float size) {
    auto& io = ImGui::GetIO();
    ImFontConfig config;
    config.MergeMode = true;
    auto* result = io.Fonts->AddFontFromFileTTF(filepath, size);
    io.Fonts->Build();
	m_defaultFont = result;
}

void CrystalClient::ImToggleable(const char* str_id, bool* v, std::string tooltip) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	bool no_win = (tooltip == "This mod is not available for Windows");

	ImVec4 regularColor;
	if (no_win) {
		regularColor = ImVec4(0.85f, 0.85f, 0.85f, 0.1f);
	} else {
		regularColor = *v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f);
	}

	ImVec4 activeColor;
	if (no_win) {
		activeColor = ImVec4(0.85f, 0.85f, 0.85f, 0.1f);
	} else {
		activeColor = *v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f);
	}

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;
	float rounding = 0;

	ImGui::InvisibleButton(str_id, ImVec2(width + 7, height));
	ImGui::SetItemAllowOverlap();
	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 10, p.y));
	ImGui::TextColored(regularColor, "%s", str_id);
	if (ImGui::IsItemClicked() && !no_win) *v = !*v;
	ImGuiContext& gg = *GImGui;
	float ANIM_SPEED = 0.085f;
	if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
	if (ImGui::IsItemHovered()) {
		if (tooltip != "N/A") ImGui::SetTooltip("%s", tooltip.c_str());
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(activeColor), height * rounding);
	} else {
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(regularColor), height * rounding);
	}
}

void CrystalClient::ImExtendedToggleable(const char* str_id, bool* v, std::string tooltip) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;
	float rounding = 0;

	//ImGui::InvisibleButton(str_id, ImVec2(width + 7, height));
	//ImGui::SetItemAllowOverlap();
	//ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 10, p.y));
	ImGui::TextColored(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f), "%s", str_id);
	if (ImGui::IsItemClicked()) *v = !*v;
	ImGuiContext& gg = *GImGui;
	float ANIM_SPEED = 0.085f;
	if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
	if (ImGui::IsItemHovered()) {
		if (tooltip != "N/A") ImGui::SetTooltip("%s", tooltip.c_str());
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * rounding);
	} else {
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * rounding);
	}
	
	ImVec2 center = ImVec2(radius + (*v ? 1 : 0) * (width - radius * 2.0f), radius);
    //ImGui::SetItemAllowOverlap();
    ImGui::SameLine();
	ImGui::PushStyleColor(0, *v ? colors[ImGuiCol_Button] : ImVec4(255,255,255,255));
    ImGui::PushStyleColor(21, ImVec4(0,0,0,0));
    if (ImGui::ArrowButton(str_id, 1))
        ImGui::OpenPopup(str_id);
	ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    // Adds 220 to each X for positioning and Adds 3 to each Y
}

void CrystalClient::Im4FloatColor(const char* label, std::string name) {
	float col[4];
	col[0] = getVar<float>(name + "-red");
	col[1] = getVar<float>(name + "-blue");
	col[2] = getVar<float>(name + "-green"); 
	col[3] = getVar<float>(name + "-alpha");

	ImGui::ColorEdit4(label, col, ImGuiColorEditFlags_NoInputs);

	*setVar<float>(name + "-red") = col[0];
	*setVar<float>(name + "-blue") = col[1];
	*setVar<float>(name + "-green") = col[2];
	*setVar<float>(name + "-alpha") = col[3];
}

void CrystalClient::ImTextbox(const char* name, std::string* str) {
	char buf[255]{};
	strncpy(buf, str->c_str(), sizeof(buf) - 1);
    ImGui::InputTextWithHint(name, name, buf, sizeof(buf));
    *str = buf;
}

void CrystalClient::ImIconEffect(const char* categoryName, std::string saveName) {
	CrystalClient::ImExtendedToggleable(categoryName, setVar<bool>(saveName));
	if (ImGui::BeginPopupModal(categoryName, NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		CrystalClient::ImExtendedToggleable("Static", setVar<bool>(saveName + "_static"));
		if (ImGui::BeginPopupModal("Static", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			Im4FloatColor("Static Color", saveName + "_static");
			if (ImGui::Button("Close")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		CrystalClient::ImExtendedToggleable("Fade", setVar<bool>(saveName + "_fade"));
		if (ImGui::BeginPopupModal("Fade", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
			Im4FloatColor("Fade Color 1", saveName + "_fade1");
			Im4FloatColor("Fade Color 2", saveName + "_fade2");
			if (ImGui::Button("Close")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		CrystalClient::ImToggleable("Rainbow", setVar<bool>(saveName + "_rainbow"));
		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

cocos2d::enumKeyCodes CrystalClient::shortcutKey(int key) {
	switch (key) {
        case 0: return enumKeyCodes::KEY_Space;
		case 1: return enumKeyCodes::KEY_A;
		case 2: return enumKeyCodes::KEY_B;
		case 3: return enumKeyCodes::KEY_C;
		case 4: return enumKeyCodes::KEY_D;
		case 5: return enumKeyCodes::KEY_E;
		case 6: return enumKeyCodes::KEY_F;
		case 7: return enumKeyCodes::KEY_G;
		case 8: return enumKeyCodes::KEY_H;
		case 9: return enumKeyCodes::KEY_I;
		case 10: return enumKeyCodes::KEY_J;
		case 11: return enumKeyCodes::KEY_K;
		case 12: return enumKeyCodes::KEY_L;
		case 13: return enumKeyCodes::KEY_M;
		case 14: return enumKeyCodes::KEY_N;
		case 15: return enumKeyCodes::KEY_O;
		case 16: return enumKeyCodes::KEY_P;
		case 17: return enumKeyCodes::KEY_Q;
		case 18: return enumKeyCodes::KEY_R;
		case 19: return enumKeyCodes::KEY_S;
		case 20: return enumKeyCodes::KEY_T;
		case 21: return enumKeyCodes::KEY_U;
		case 22: return enumKeyCodes::KEY_V;
		case 23: return enumKeyCodes::KEY_W;
		case 24: return enumKeyCodes::KEY_X;
		case 25: return enumKeyCodes::KEY_Y;
		case 26: return enumKeyCodes::KEY_Z;

		case 27: return enumKeyCodes::KEY_Zero;
		case 28: return enumKeyCodes::KEY_One;
		case 29: return enumKeyCodes::KEY_Two;
		case 30: return enumKeyCodes::KEY_Three;
		case 31: return enumKeyCodes::KEY_Four;
		case 32: return enumKeyCodes::KEY_Five;
		case 33: return enumKeyCodes::KEY_Six;
		case 34: return enumKeyCodes::KEY_Seven;
		case 35: return enumKeyCodes::KEY_Eight;
		case 36: return enumKeyCodes::KEY_Nine;

		case 37: return enumKeyCodes::KEY_Up;
		case 38: return enumKeyCodes::KEY_Down;
		case 39: return enumKeyCodes::KEY_Left;
		case 40: return enumKeyCodes::KEY_Right;

		case 41: return enumKeyCodes::KEY_Backspace;
        case 42: return enumKeyCodes::KEY_Enter;
        case 43: return enumKeyCodes::KEY_Shift;
        case 44: return enumKeyCodes::KEY_Control;
        case 45: return enumKeyCodes::KEY_Alt;
        case 46: return enumKeyCodes::KEY_CapsLock;
        case 47: return enumKeyCodes::KEY_Escape;

		default: return enumKeyCodes::KEY_A;
	}
}

void CrystalClient::setAnchoredPosition(CCLabelBMFont* label, int anchorPos, CCLayer* layer, bool first) {
	auto corner = CCDirector::sharedDirector()->getScreenTop();
	int anchorY = ((anchorPos - 1) * 15) + 10;
	label->setPosition(5, corner - anchorY);
	label->setAnchorPoint({0, 0.5});
	label->setScale(0.4);
	label->setOpacity(100);
	if (first) layer->addChild(label, 1000);
}

void CrystalClient::addTransparentBG(CCNode* layer) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
        
	auto bg = CCSprite::create("GJ_gradientBG.png");
	auto bgSize = bg->getTextureRect().size;
	bg->setAnchorPoint({ 0.0f, 0.0f });
	bg->setScaleX((winSize.width + 10.0f) / bgSize.width);
	bg->setScaleY((winSize.height + 10.0f) / bgSize.height);
	bg->setPosition({ -5.0f, -5.0f });
	bg->setColor(ccc3(255, 255, 255));
	
	layer->addChild(bg, -2);
}

void CrystalClient::initPatches() {
#ifdef GEODE_IS_MACOS
	// scale hack
	scaleHack1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18D811), {static_cast<unsigned char>('\xeb')}).unwrap();
	scaleHack2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18D7D9), {static_cast<unsigned char>('\xeb')}).unwrap();
	//auto respawn = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x072419), {'\x00'}).unwrap();

	// object limit
	objLimit1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18bfa), {static_cast<unsigned char>('\xeb')}).unwrap();
	objLimit2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18f25), {static_cast<unsigned char>('\xeb')}).unwrap();
	objLimit3 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1b991), {static_cast<unsigned char>('\xeb')}).unwrap();

	// custom object

	customObjLimit1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d67c), {
    	static_cast<unsigned char>('\xe9'), 
    	static_cast<unsigned char>('\x98'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x90')
	}).unwrap();

	customObjLimit2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d869), {
    	static_cast<unsigned char>('\x90'), 
    	static_cast<unsigned char>('\x90'), 
    	static_cast<unsigned char>('\x90'), 
    	static_cast<unsigned char>('\x90'), 
    	static_cast<unsigned char>('\x90'), 
    	static_cast<unsigned char>('\x90')
	}).unwrap();

	customObjLimit3 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d72d), {
    	static_cast<unsigned char>('\xe9'), 
    	static_cast<unsigned char>('\xa7'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x00'), 
    	static_cast<unsigned char>('\x90')
	}).unwrap();
#endif
}

void CrystalClient::refreshPatches() {
	/*
	if (getVar<bool>("scalehack")) {
		scaleHack1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18D811), {'\xeb'}).unwrap();
		scaleHack2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18D7D9), {'\xeb'}).unwrap();
	} else {
		Mod::get()->unpatch(scaleHack1);
		Mod::get()->unpatch(scaleHack2);
	}

	if (getVar<bool>("obj_limit")) {
		objLimit1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18bfa), {'\xeb'}).unwrap();
		objLimit2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x18f25), {'\xeb'}).unwrap();
		objLimit3 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1b991), {'\xeb'}).unwrap();
	} else {
		Mod::get()->unpatch(objLimit1);
		Mod::get()->unpatch(objLimit2);
		Mod::get()->unpatch(objLimit3);
	}

	if (getVar<bool>("custom_obj_limit")) {
		customObjLimit1 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d67c), {'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}).unwrap();
		customObjLimit2 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d869), {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}).unwrap();
		customObjLimit3 = Mod::get()->patch(reinterpret_cast<void*>(base::get() + 0x1d72d), {'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}).unwrap();
	} else {
		Mod::get()->unpatch(customObjLimit1);
		Mod::get()->unpatch(customObjLimit2);
		Mod::get()->unpatch(customObjLimit3);
	}
	*/
}

void CrystalClient::firstLoad(CCNode* layer) {
	*setVar<int>("keybindsSize") = 2;
	*setVar<int>("keybind_key-1") = 39;
	*setVar<int>("keybind_mod-1") = 6;
	*setVar<int>("keybind_key-2") = 40;
	*setVar<int>("keybind_mod-2") = 7;
	//keybinds.push_back({39, 6});
	//keybinds.push_back({40, 7});
	if (layer) {
		auto alert = geode::createQuickPopup(
			"Hi!",            // title
			"Thank you for installing <cg>Crystal Client.</c> You can <cj>open the mod menu by pressing TAB</c> and you can <cr>report any bugs</c> or suggestions in my <cj>discord server.</c> Enjoy!",   // content
			"OK", "Join Discord Server",      // buttons
			[](auto, bool btn2) {
				if (btn2) {
					CCApplication::sharedApplication()->openURL("https://discord.gg/xV5dekWHTd");
				}
			},
			false
		);
		//alert->m_scene = layer;
		alert->show();
	}
}

void CrystalClient::noImage(CCNode* layer) {
	if (layer) {
		auto alert = geode::createQuickPopup(
			"Oops",            // title
			"You are using <cg>BetterBG</c> from Crystal but there is <cr>no image for it.</c> Please put <cj>whatever image with the name background.jpg</c> on GD/Contents/geode/config/ninxout.crystalclient/BetterBG. Thanks for using Crystal <cp><3</c>",   // content
			"OK", "Join Discord Server",      // buttons
			[](auto, bool btn2) {
				if (btn2) {
					CCApplication::sharedApplication()->openURL("https://discord.gg/xV5dekWHTd");
				}
			},
			false
		);
		alert->m_scene = layer;
		alert->show();
	}
}

void CrystalClient::noFoldersCB(CCNode* layer) {
	if (layer) {
		auto alert = geode::createQuickPopup(
			"Oops",            // title
			"You are using <cg>Clickbot</c> from Crystal but there is <cr>no folders for it.</c> Please create this folders: <cj>clicks, softClicks, releases and softReleases</c> on GD/Contents/geode/config/ninxout.crystalclient/Amethyst/Clickbot. Thanks for using Crystal <3 <cr>(Tap ESC to exit)</c>", // content
			"OK", "Join Discord Server",      // buttons
			[](auto, bool btn2) {
				if (btn2) {
					CCApplication::sharedApplication()->openURL("https://discord.gg/xV5dekWHTd");
				}
			},
			false
		);
		alert->m_scene = layer;
		alert->show();
	}
}

void CrystalClient::emptyFoldersCB(CCNode* layer) {
	if (layer) {
		auto alert = geode::createQuickPopup(
			"Oops",            // title
			"You are using <cg>Clickbot</c> from Crystal but there is <cr>no sounds for it.</c> Please put <cj>at least one .mp3 file</c> inside all the Clickbot folders. Thanks for using Crystal <3 <cr>(Tap ESC to exit)</c>", // content
			"OK", "Join Discord Server",      // buttons
			[](auto, bool btn2) {
				if (btn2) {
					CCApplication::sharedApplication()->openURL("https://discord.gg/xV5dekWHTd");
				}
			},
			false
		);
		alert->m_scene = layer;
		alert->show();
	}
}