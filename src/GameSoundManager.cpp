#include "hackpro.hpp"

class $modify(GameSoundManager) {
  	void playBackgroundMusic(gd::string song, bool b1, bool b2) {

  	if ((std::string(song) == "menuLoop.mp3") && randomLoop) {
		song = getRandomSong();
	}  // random menu loop

	//findsong = replacing;
	replacesong = replaceWith;

	if (item_current_idx > 0 && EnableNONGLoader) {
    	//GameSoundManager::playBackgroundMusic("NONGs/" + replacesong, b1, b2);
	} else {
		//GameSoundManager::playBackgroundMusic(song, b1, b2);
	}
	GameSoundManager::playBackgroundMusic(song, b1, b2);
	}
};