#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

class Display {
    public:
        static Display* get();
        void addDisplayChildren(int index, PlayLayer* pl);
        CCLabelBMFont* getDisplay(int index);
		void arrangeDisplay(int index);
		void setDefaultDisplay(int index, const char* text);
		void updateDisplay(int index);

    protected:
        CCPoint getDisplayPosition(int index);
        float getDisplayOpacity(int index);
        float getDisplayScale(int index);
        CCPoint getDisplayAnchor(int index, CCLabelBMFont* label);

        CCLabelBMFont* labels[14];
};