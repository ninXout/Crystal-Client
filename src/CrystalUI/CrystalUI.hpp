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