#include "../CrystalProfile.hpp"
#include <Geode/modify/EditorUI.hpp>
#include <numbers>

class $modify(EditorUI) {
    void zoomIn(cocos2d::CCObject* sender) {
        if (getVar<bool>("editor_zoom")) {
            auto zoom = this->m_editorLayer->m_objectLayer->getScale();
            zoom = std::pow(std::numbers::e, std::log(std::max(zoom, 0.001f)) + 10 * 0.015f);
            EditorUI::updateZoom(zoom);
        } else {
            EditorUI::zoomIn(sender);
        }
    }

    void zoomOut(cocos2d::CCObject* sender) {
        if (getVar<bool>("editor_zoom")) {
            auto zoom = this->m_editorLayer->m_objectLayer->getScale();
            zoom = std::pow(std::numbers::e, std::log(std::max(zoom, 0.001f)) - 10 * 0.015f);
            EditorUI::updateZoom(zoom);
        } else {
            EditorUI::zoomOut(sender);
        }
    }
};