#include "hackpro.hpp"

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		pushing = true;
		if (b) mouse1Down = true;
	    if (!b) mouse2Down = true;
		if (playerBools[22]) {
			if (!b) GJBaseGameLayer::pushButton(i,true);
			if (b) GJBaseGameLayer::pushButton(i,false);
		} else if (playerBools[23]) {
			GJBaseGameLayer::pushButton(i,true);
			GJBaseGameLayer::pushButton(i,false);
		} else {
			GJBaseGameLayer::pushButton(i,b);
		}
		clickscount++;
	}

	void releaseButton(int i, bool b) {
		pushing = false;
		if (b) mouse1Down = false;
	    if (!b) mouse2Down = false;
        if (playerBools[22]) {
			if (!b) GJBaseGameLayer::releaseButton(i,true);
			if (b) GJBaseGameLayer::releaseButton(i,false);
		} else if (playerBools[23]) {
			GJBaseGameLayer::releaseButton(i,true);
			GJBaseGameLayer::releaseButton(i,false);
		} else {
			GJBaseGameLayer::releaseButton(i,b);
		}
	}

	void bumpPlayer(PlayerObject* player, GameObject* object) {
		bool a = object->m_hasBeenActivated;
    	bool b = object->m_hasBeenActivatedP2;
		GJBaseGameLayer::bumpPlayer(player, object);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode) {
        	if (object->m_hasBeenActivated && !a) g_activated_objects.push_back(object);
        	if (object->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(object);
    	}
	}
};