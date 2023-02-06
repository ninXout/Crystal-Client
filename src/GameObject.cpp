#include "hackpro.hpp"

class $(MyGameObject, GameObject) {
	CCSprite* m_backgroundLayer;
	bool m_realVisible;
	cocos2d::_ccColor3B m_realColor;

	void setVisible(bool v) {
		if (playerBools[39]) {
			m_fields->m_realVisible = v;

			if (m_objectType == GameObjectType::Decoration) {
				GameObject::setVisible(false);
			} else {
				GameObject::setVisible(v); // for CCParticleSystem (idk why)
				GameObject::setVisible(true);
			}
		} else GameObject::setVisible(v);
	}

	void revertVisibility() {
		setVisible(m_fields->m_realVisible);
	}

	void setOpacity(unsigned char g) {
		GameObject::setOpacity(g);

		if (playerBools[39] && m_objectType != GameObjectType::Decoration) {
			CCSpritePlus::setOpacity(255);
			if (m_glowSprite)
				m_glowSprite->setOpacity(255);
		}
	}

	void setGlowColor(cocos2d::_ccColor3B const& col) {
		if (playerBools[39]) {
			GameObject::setGlowColor(ccc3(255, 255, 255));
		} else {
			GameObject::setGlowColor(col);
		}
	}

	void setObjectColor(const cocos2d::ccColor3B& cor) {
		if (playerBools[39] && m_objectType != GameObjectType::Decoration) {
			GameObject::setObjectColor(ccc3(255, 255, 255));
		} else {
			GameObject::setObjectColor(cor);
		}
	}

    virtual void update(float time2) {
		if (playerBools[34]) {
			bool m_isGlowDisabled = true;
		}
		if (playerBools[11]) {
			bool m_particleAdded = true;
   			bool m_hasParticles = false;
		}
		GameObject::update(time2);
	}
    
	virtual void activateObject() {
		bool a = this->m_hasBeenActivated;
    	bool b = this->m_hasBeenActivatedP2;
		GameObject::activateObject();
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode) {
    		if (this->m_hasBeenActivated && !a) g_activated_objects.push_back(this);
        	if (this->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(this);
    	}
	}
};