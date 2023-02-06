#include "hackpro.hpp"

class $modify(EditorUI) {
	void keyDown(enumKeyCodes code) {
		EditorUI::keyDown(code);
		if (s_drawer) {
			s_drawer->clear();
			static_cast<HitboxLevelEditorLayer*>(LevelEditorLayer::get())->updateHitboxEditor();
		} 
	}

	void scrollWheel(float y, float x) {
		auto kb = CCDirector::sharedDirector()->getKeyboardDispatcher();
		if (kb->getShiftKeyPressed() && scrollzoom) {
			auto zoom = this->m_editorLayer->m_objectLayer->getScale();
			zoom = std::pow(std::numbers::e, std::log(std::max(zoom, 0.001f)) - y * 0.025f);
			this->updateZoom(zoom);
		} else {
			EditorUI::scrollWheel(y, x);
		}
	}

	void zoomIn(cocos2d::CCObject* sender) {
		if (bypassBools[8]) {
			zoom = zoom + 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomIn(sender);
		}
	}

	void zoomOut(cocos2d::CCObject* sender) {
		if (bypassBools[8]) {
			zoom = zoom - 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomOut(sender);
		}
	}
};