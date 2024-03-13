#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace CrystalClient;

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel *p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1))
			return false;

		if (this->m_songWidget->m_downloadBtn->isVisible() && getSavedVar<bool>("auto_song_download")) {
			this->m_songWidget->onDownload(nullptr);
		}

		return true;
	}

	void levelDownloadFinished(GJGameLevel *level) {
		LevelInfoLayer::levelDownloadFinished(level);

		if (this->m_songWidget->m_downloadBtn->isVisible() && getSavedVar<bool>("auto_song_download")) {
			this->m_songWidget->onDownload(nullptr);
		}
	}
};