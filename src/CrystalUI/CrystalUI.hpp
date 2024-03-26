#include <Geode/Geode.hpp>
#include <imgui.h>
#include "Fonts.hpp"


using namespace geode::prelude;

namespace CrystalUI {
    void setupFonts();
    void setupTheme();

    void toggle(const char* str_id, bool* v, std::string tooltip = "N/A", bool no_win = false);
    void toggleWithMenu(const char* str_id, bool* v, std::string tooltip = "N/A", bool no_win = false); // TODO: Make the popup a lambda
    void subToggle(const char* str_id, bool* v);
    void subToggleWithMenu(const char* str_id, bool* v);
    void internalToggle(const char* std_id, bool* v, bool no_win = false);
    void colorPicker(const char* label, std::string name);
    void textbox(const char* name, std::string* str);
    void iconEffect(const char* categoryName, std::string saveName);
    void inputInt(const char* name, int* num);
    void inputFloat(const char* name, float* num);
    void hotkey(const char* label);
    void subTab(std::string childName, ImVec2 childSize, std::vector<std::string> tabNames, int* selectedSubTab);
    void mainColorPicker(const char* str_id, std::string name, std::string tooltip, bool no_win = false);
    //void mainButton(const char* str_id, std::function<void> func, std::string tooltip, bool no_win = false);

    void renderLogo();
    void renderUser();
    void renderTabs();
    void renderRightColumn();
    void renderFavorites();

    inline bool waitingForKey = false;
    inline cocos2d::enumKeyCodes queuedKey = KEY_Escape;
    inline ImFont* font;
    inline std::string fileName;
    inline int selectedTab = 0;
    inline int selectedIconSubTab = 0;
    inline int selectedCustomSubTab = 0;
}

inline ImVec4 operator+(const ImVec4& a, const ImVec4& b) {
	ImVec4 vec;
	vec.w = a.w + b.w;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return vec;
}

inline ImVec4 operator-(const ImVec4& a, const ImVec4& b) {
	ImVec4 vec;
	vec.w = a.w - b.w;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return vec;
}

inline ImVec4 operator*(const ImVec4& a, float b) {
	ImVec4 vec;
	vec.w = a.w;
	vec.x = a.x * b;
	vec.y = a.y * b;
	vec.z = a.z * b;
	return vec;
}

inline ImVec4 operator/(const ImVec4& a, float b) {
	ImVec4 vec;
	vec.w = a.w;
	vec.x = a.x / b;
	vec.y = a.y / b;
	vec.z = a.z / b;
	return vec;
}

inline bool operator==(const ImVec4& a, const ImVec4& b) {
	bool wb, xb, yb, zb;
	wb = static_cast<int>(a.w * 255.f) == static_cast<int>(b.w * 255.f);
	xb = static_cast<int>(a.x * 255.f) == static_cast<int>(b.x * 255.f);
	yb = static_cast<int>(a.y * 255.f) == static_cast<int>(b.y * 255.f);
	zb = static_cast<int>(a.z * 255.f) == static_cast<int>(b.z * 255.f);
	return (wb && xb && yb && zb);
}