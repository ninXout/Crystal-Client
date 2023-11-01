#include <Geode/Geode.hpp>
#include <imgui.h>
#include "Fonts.hpp"

using namespace geode::prelude;

namespace CrystalUI {
    void setupFonts();
    void setupTheme();

    void toggle(const char* str_id, bool* v, std::string tooltip = "N/A", bool no_win = false);
    void toggleWithMenu(const char* str_id, bool* v, std::string tooltip = "N/A", bool no_win = false); // TODO: Make the popup a lambda
    void colorPicker(const char* label, std::string name);
    void textbox(const char* name, std::string* str);
    void iconEffect(const char* categoryName, std::string saveName);
    void inputInt(const char* name, int* num);
    void inputFloat(const char* name, float* num);

    void renderLogo();
    void renderUser();
    void renderTabs();
    void renderRightColumn();
    void renderFavorites();

    inline ImFont* font;
    inline int selectedTab = 0;
}