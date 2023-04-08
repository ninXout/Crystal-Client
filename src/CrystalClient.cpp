#include <imgui_internal.h>
#include "CrystalClient.hpp"
#include <Geode/loader/Log.hpp>
#include "ImGui.hpp"
#include "subprocess.h"

CrystalClient* CrystalClient::get() {
    static auto inst = new CrystalClient;
    return inst;
}

void CrystalClient::draw() {
    if (m_visible) {
        this->applyTheme();

        ImGui::PushFont(m_defaultFont);
        this->drawPages();
        ImGui::PopFont();
    }
}

void CrystalClient::setupFonts() {
    static const ImWchar* def_ranges   = ImGui::GetIO().Fonts->GetGlyphRangesDefault();
    
    static constexpr auto add_font = [](
    ) {
        auto& io = ImGui::GetIO();
        ImFontConfig config;
        config.MergeMode = true;
        auto* result = io.Fonts->AddFontFromFileTTF("geode/unzipped/ninxout.crystalclient/resources/ninxout.crystalclient/Verdana.ttf", 14.0f);
        io.Fonts->Build();
        return result;
    };

    m_defaultFont = add_font();
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

void CrystalClient::ImToggleable(const char* str_id, bool* v) {
	ImVec4* colors = ImGui::GetStyle().Colors;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;
	float rounding = 0;

	ImGui::InvisibleButton(str_id, ImVec2(width + 7, height));
	ImGui::SetItemAllowOverlap();
	ImGui::SameLine();
	ImGui::SetCursorScreenPos(ImVec2(p.x + 10, p.y));
	ImGui::TextColored(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f), str_id);
	if (ImGui::IsItemClicked()) *v = !*v;
	ImGuiContext& gg = *GImGui;
	float ANIM_SPEED = 0.085f;
	if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
	if (ImGui::IsItemHovered())
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * rounding);
	else
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * rounding);
	
	ImVec2 center = ImVec2(radius + (*v ? 1 : 0) * (width - radius * 2.0f), radius);
	//draw_list->AddRectFilled(ImVec2((p.x + center.x) - 9.0f, p.y + 1.5f),
		//ImVec2((p.x + (width / 2) + center.x) - 9.0f, p.y + height - 1.5f), IM_COL32(255, 255, 255, 255), height * rounding);
}

void CrystalClient::ImExtendedToggleable(const char* str_id, bool* v) {
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
	ImGui::TextColored(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f), str_id);
	if (ImGui::IsItemClicked()) *v = !*v;
	ImGuiContext& gg = *GImGui;
	float ANIM_SPEED = 0.085f;
	if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
	if (ImGui::IsItemHovered())
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * rounding);
	else
		draw_list->AddRectFilled(p, ImVec2(p.x + width * 0.1, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * rounding);
	
	ImVec2 center = ImVec2(radius + (*v ? 1 : 0) * (width - radius * 2.0f), radius);
    //ImGui::SetItemAllowOverlap();
    ImGui::SameLine();
	ImGui::PushStyleColor(0, *v ? ImVec4(255,255,255,255) : ImVec4(0,0,0,0));
    ImGui::PushStyleColor(21, ImVec4(0,0,0,0));
    if (ImGui::ArrowButton(str_id, 1))
        ImGui::OpenPopup(str_id);
	ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    // Adds 220 to each X for positioning and Adds 3 to each Y
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

float CrystalClient::getTimeForXPos(PlayLayer* play) {
    float ret;
    float xPos = play->m_player1->getPositionX();
    __asm movss xmm1, xPos;
    reinterpret_cast<void(__thiscall*)>(geode::base::get() + 0x293eb0); // PlayLayer::timeForXPos2
    __asm movss ret, xmm0; // return value

    return ret;
}

std::string CrystalClient::getRenderPath(bool full) {
	std::string songPath;
	if (full) {
		songPath = (std::string)geode::dirs::getTempDir();
		songPath.erase(songPath.length() - 10);
		songPath = songPath + "Crystal/temp/";
	} else {
		songPath = "./Crystal/temp/";
	}
	return songPath;
}

std::string CrystalClient::getSongCmdStr(std::string songOffset, std::string songPath, std::string tempPath, std::string time, std::string path) {
	std::stringstream stream;
	stream << "ffmpeg";
	stream << " -y -ss ";
	stream << songOffset;
	stream << " -i \"" << songPath << "\"";
	stream << " -i \"" << tempPath << "\"";
	stream << " -t " << time;
	//stream << " -b:a " << audioBitrate << "k"; //bitrate
	stream << " -c:v copy ";
	stream << "\"" << path << "\"";

	return stream.str();
}

