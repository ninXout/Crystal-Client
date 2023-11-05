#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace CrystalClient;

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		if (getSavedVar<bool>("flipped_dual")) {
			if (!b) GJBaseGameLayer::pushButton(i,true);
			if (b) GJBaseGameLayer::pushButton(i,false);
		} else if (getSavedVar<bool>("mirrored_dual")) {
			GJBaseGameLayer::pushButton(i,true);
			GJBaseGameLayer::pushButton(i,false);
		} else {
			GJBaseGameLayer::pushButton(i,b);
		}
	}

	void releaseButton(int i, bool b) {
        if (getSavedVar<bool>("flipped_dual")) {
			if (!b) GJBaseGameLayer::releaseButton(i,true);
			if (b) GJBaseGameLayer::releaseButton(i,false);
		} else if (getSavedVar<bool>("mirrored_dual")) {
			GJBaseGameLayer::releaseButton(i,true);
			GJBaseGameLayer::releaseButton(i,false);
		} else {
			GJBaseGameLayer::releaseButton(i,b);
		}
	}
};