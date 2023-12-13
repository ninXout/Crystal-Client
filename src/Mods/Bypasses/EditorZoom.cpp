#include "../../CrystalClient/CrystalClient.hpp"
#include <Geode/modify/EditorUI.hpp>

using namespace CrystalClient;

class $modify(EditorUI) {
    void recreatedZoom(bool direction) {
        // recreated version of EditorUI::zoomIn/zoomOut (with the zoom limiting lines commented out)

        float fVar2 = 2.0;
        //if (m_scaleControl->m_value + (direction ? 0.1 : -0.1) <= 2.0) {
            fVar2 = m_scaleControl->m_value + (direction ? 0.1 : -0.1);
        //}
        //m_scaleControl->m_value = 0.2;
        //if (0.2 <= fVar2) {
            m_scaleControl->m_value = fVar2;
        //}
        EditorUI::updateZoom(m_scaleControl->m_value);
    }

    void zoomIn(cocos2d::CCObject* target) {
        if (getSavedVar<bool>("editor_zoom")) recreatedZoom(true);
        else EditorUI::zoomIn(target);
    }

    void zoomOut(cocos2d::CCObject* target) {
        if (getSavedVar<bool>("editor_zoom")) recreatedZoom(false);
        else EditorUI::zoomOut(target);
    }
};

