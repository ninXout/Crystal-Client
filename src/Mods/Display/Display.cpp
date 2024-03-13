#include "Display.hpp"

CCLabelBMFont* Display::getDisplay(int index) {
    return nodes[index];
}

void Display::setDefaultDisplay(int index, const char* text) {
    nodes[index] = CCLabelBMFont::create(text, "bigFont.fnt");
}

CCPoint Display::getDisplayPosition(int index) {
    auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

    std::vector<bool> displays = {
        getSavedVar<bool>("cheat_indicator"),
        getSavedVar<bool>("custom_message"),
        getSavedVar<bool>("cps_display"),
        getSavedVar<bool>("fps_display"),
        getSavedVar<bool>("last_death"),
        getSavedVar<bool>("attempts"),
        getSavedVar<bool>("jumps"),
        getSavedVar<bool>("run_from"),
        getSavedVar<bool>("best_run"),
        getSavedVar<bool>("noclip_accuracy"),
        getSavedVar<bool>("noclip_deaths"),
        getSavedVar<bool>("level_info"),
        getSavedVar<bool>("macro_status"),
        getSavedVar<bool>("clock")
    };

    std::vector<LabelPos> displayPositions;

	for (int i = 0; i < DISPLAYSIZE; i++) {
        std::string theKey = "label_pos-" + std::to_string(i);
	    displayPositions.push_back((LabelPos)getSavedVar<int>(theKey));
    }

    float tr = 0, tl = 0, br = 0, bl = 0, thisLabel;

    if (getSavedVar<bool>("testmode_label")) tl += 1.0f * getSavedVar<float>("display_scale");

	for (int i = 0; i < DISPLAYSIZE; i++) {
		if (displays[i]) {
            switch (displayPositions[i]) {
                case TR:
                    if (index == i)
                        thisLabel = tr;
                    tr += 1.0f * getSavedVar<float>("display_scale");
                    break;
                case TL:
                    if (index == i)
                        thisLabel = tl;
                    tl += 1.0f * getSavedVar<float>("display_scale");
                    break;
                case BR:
                    if (index == i)
                        thisLabel = br;
                    br += 1.0f * getSavedVar<float>("display_scale");
                    break;
                case BL:
                    if (index == i)
                        thisLabel = bl;
                    bl += 1.0f * getSavedVar<float>("display_scale");
                    break;
            }
        }
	}

    float height = 0, x = 0;

	switch (displayPositions[index]) {
		case TR:
			height = size.height - 10 - (thisLabel * getSavedVar<float>("display_space"));
			x = size.width - 5;
			break;
		case TL:
			height = size.height - 10 - (thisLabel * getSavedVar<float>("display_space"));
			x = 5.0f;
			break;
		case BR:
			height = 10.0f + (thisLabel * getSavedVar<float>("display_space"));
			x = size.width - 5;
			break;
		case BL:
			height = 10.0f + (thisLabel * getSavedVar<float>("display_space"));
			x = 5.0f;
			break;
	}

    if (index == 0) return {x, height + 10};

    return {x, height};
}

float Display::getDisplayOpacity(int index) {
    if (getSavedVar<float>("display_opacity") < 1)
		*setSavedVar<float>("display_opacity") = 255;
	else if (getSavedVar<float>("display_opacity") > 255)
		*setSavedVar<float>("display_opacity") = 255;

	return getSavedVar<float>("display_opacity");
}

float Display::getDisplayScale(int index) {
    if (getSavedVar<float>("display_scale") < 0.1f || getSavedVar<float>("display_scale") > 1.5f) 
        *setSavedVar<float>("display_scale") = 1.0f;
    float sc = getSavedVar<float>("display_scale") * 0.45f;
	if (index == 0) {
		sc *= 1.8f;
	}

	return sc;
}

CCPoint Display::getDisplayAnchor(int index, CCLabelBMFont* label) {
    return label->getPositionX() > 284.5f
           ? ccp(1.0f, label->getAnchorPoint().y)
           : ccp(0.0f, label->getAnchorPoint().y);
}

void Display::arrangeDisplay(int index) {
    nodes[index]->setPosition(getDisplayPosition(index));
    nodes[index]->setOpacity(getDisplayOpacity(index));
    nodes[index]->setScale(getDisplayScale(index));
    nodes[index]->setAnchorPoint(getDisplayAnchor(index, nodes[index]));
}

void Display::addDisplayChildren(int index, PlayLayer* pl) {
    pl->addChild(nodes[index], 1000);
}

void Display::updateDisplay(int index) {
    switch (index) {
        case 0:
            nodes[0]->setVisible(getSavedVar<bool>("cheat_indicator"));
            break;
        case 1:
            nodes[1]->setVisible(getSavedVar<bool>("custom_message"));
            break;
        case 2:
            nodes[2]->setVisible(getSavedVar<bool>("cps_display"));
            break;
        case 3:
            nodes[3]->setVisible(getSavedVar<bool>("fps_display"));
            break;
        case 4:
            nodes[4]->setVisible(getSavedVar<bool>("last_death"));
            break;
        case 5:
            nodes[5]->setVisible(getSavedVar<bool>("attempts"));
            break;
        case 6:
            nodes[6]->setVisible(getSavedVar<bool>("jumps"));
            break;
        case 7:
            nodes[7]->setVisible(getSavedVar<bool>("run_from"));
            break;
        case 8:
            nodes[8]->setVisible(getSavedVar<bool>("best_run"));
            break;
        case 9:
            nodes[9]->setVisible(getSavedVar<bool>("noclip_accuracy"));
            break;
        case 10:
            nodes[10]->setVisible(getSavedVar<bool>("noclip_deaths"));
            break;
        case 11:
            nodes[11]->setVisible(getSavedVar<bool>("level_info"));
            break;
        case 12:
            nodes[12]->setVisible(getSavedVar<bool>("macro_status"));
            break;
        case 13:
            nodes[13]->setVisible(getSavedVar<bool>("clock"));
            break;
    }
    Display::arrangeDisplay(index);
}