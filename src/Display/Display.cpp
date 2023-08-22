#include "Display.hpp"

Display* Display::get() {
    static auto inst = new Display;
    return inst;
}

CCLabelBMFont* Display::getDisplay(int index) {
    return labels[index];
}

void Display::setDefaultDisplay(int index, const char* text) {
    labels[index] = CCLabelBMFont::create(text, "bigFont.fnt");
}

CCPoint Display::getDisplayPosition(int index) {
    auto director = CCDirector::sharedDirector();
	auto size = director->getWinSize();

    std::vector<LabelPos> displayPositions;

	for (int i = 0; i < 13; i++) {
        std::string theKey = "label_pos-" + std::to_string(index);
	    displayPositions.push_back((LabelPos)getVar<int>(theKey));
    }

    float tr = 0, tl = 0, br = 0, bl = 0, thisLabel;

	for (int i = 0; i < 13; i++) {
		switch (displayPositions[i]) {
			case TR:
				if (index == i)
					thisLabel = tr;
				tr += 1.0f * getVar<float>("display_scale");
				break;
			case TL:
				if (index == i)
					thisLabel = tl;
				tl += 1.0f * getVar<float>("display_scale");
				break;
			case BR:
				if (index == i)
					thisLabel = br;
				br += 1.0f * getVar<float>("display_scale");
				break;
			case BL:
				if (index == i)
					thisLabel = bl;
				bl += 1.0f * getVar<float>("display_scale");
				break;
		}
	}

    float height = 0, x = 0;

	switch (displayPositions[index]) {
		case TR:
			height = size.height - 10 - (thisLabel * getVar<float>("display_space"));
			x = size.width - 5;
			break;
		case TL:
			height = size.height - 10 - (thisLabel * getVar<float>("display_space"));
			x = 5.0f;
			break;
		case BR:
			height = 10.0f + (thisLabel * getVar<float>("display_space"));
			x = size.width - 5;
			break;
		case BL:
			height = 10.0f + (thisLabel * getVar<float>("display_space"));
			x = 5.0f;
			break;
	}

    if (index == 0) return {x, height + 10};

    return {x, height};
}

float Display::getDisplayOpacity(int index) {
    if (getVar<float>("display_opacity") < 1)
		*setVar<float>("display_opacity") = 255;
	else if (getVar<float>("display_opacity") > 255)
		*setVar<float>("display_opacity") = 255;

	return getVar<float>("display_opacity");
}

float Display::getDisplayScale(int index) {
    if (getVar<float>("display_scale") < 0.1f || getVar<float>("display_scale") > 1.5f) 
        *setVar<float>("display_scale") = 1.0f;
    float sc = getVar<float>("display_scale") * 0.45f;
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
    labels[index]->setPosition(getDisplayPosition(index));
    labels[index]->setOpacity(getDisplayOpacity(index));
    labels[index]->setScale(getDisplayScale(index));
    labels[index]->setAnchorPoint(getDisplayAnchor(index, labels[index]));
}

void Display::addDisplayChildren(int index, PlayLayer* pl) {
    pl->addChild(labels[index], 1000);
}

void Display::updateDisplay(int index) {
    /*
    switch (index) {
        case 0:
            labels[0]->setVisible(getVar<bool>("cheat_indicator"));
            break;
        case 1:
            labels[1]->setVisible(getVar<bool>("custom_message"));
            break;
        case 2:
            labels[2]->setVisible(getVar<bool>("cps_display"));
            break;
        case 3:
            labels[3]->setVisible(getVar<bool>("fps_display"));
            break;
        case 4:
            labels[4]->setVisible(getVar<bool>("last_death"));
            break;
        case 5:
            labels[5]->setVisible(getVar<bool>("attempts"));
            break;
        case 6:
            labels[6]->setVisible(getVar<bool>("jumps"));
            break;
        case 7:
            labels[7]->setVisible(getVar<bool>("run_from"));
            break;
        case 8:
            labels[8]->setVisible(getVar<bool>("best_run"));
            break;
        case 9:
            labels[9]->setVisible(getVar<bool>("noclip_accuracy"));
            break;
        case 10:
            labels[10]->setVisible(getVar<bool>("noclip_deaths"));
            break;
        case 11:
            labels[11]->setVisible(getVar<bool>("level_info"));
            break;
        case 12:
            labels[12]->setVisible(getVar<bool>("macro_status"));
            break;
        case 13:
            labels[13]->setVisible(getVar<bool>("clock"));
            break;
    }
    */
}