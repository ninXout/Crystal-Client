#include "../../CrystalClient/CrystalClient.hpp"

using namespace CrystalClient;
using namespace geode::prelude;

#define DISPLAYSIZE 14

enum LabelPos {
	TR,
	TL,
	BR,
	BL
};

namespace Display {
    void addDisplayChildren(int index, PlayLayer* pl);
    CCLabelBMFont* getDisplay(int index);
    void arrangeDisplay(int index);
    void setDefaultDisplay(int index, const char* text);
    void updateDisplay(int index);
    CCPoint getDisplayPosition(int index);
    float getDisplayOpacity(int index);
    float getDisplayScale(int index);
    CCPoint getDisplayAnchor(int index, CCLabelBMFont* label);

    inline CCLabelBMFont* nodes[DISPLAYSIZE];
}