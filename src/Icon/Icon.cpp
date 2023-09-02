#include "Icon.hpp"
#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

Icon* Icon::get() {
    static auto inst = new Icon;
    return inst;
}

void Icon::HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float fC = fV * fS; // Chroma
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;
  
  if(0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if(1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if(2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if(3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if(4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if(5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }
  
  fR += fM;
  fG += fM;
  fB += fM;
}

std::string Icon::getKeyForEffect(PlayerType pl, EffectType et, AffectedType at) {
    std::string key;

    switch (pl) {
        case Player1:
            key = "P1";
            break;
        case Player2:
            key = "P2";
            break;
    }

    switch (at) {
        case Color1:
            key += "C1";
            break;
        case Color2:
            key += "C2";
            break;
        case Glow:
            key += "G";
            break;
        case WaveTrail:
            key += "W";
            break;
        case RegularTrail:
            key += "R";
            break;
    }

    switch (et) {
        case Static:
            key += "_static";
            break;
        case Rainbow:
            key += "_rainbow";
            break;
        case Fade:
            key += "_fade";
            break;
        case None:
            break;
    }

    return key;
}

cocos2d::_ccColor3B Icon::getEffectColor(PlayerType player, EffectType effect, AffectedType affect) {
    if (effect == EffectType::Static) {
        R = getVar<float>(getKeyForEffect(player, effect, affect) + "-red");
        B = getVar<float>(getKeyForEffect(player, effect, affect) + "-blue");
        G = getVar<float>(getKeyForEffect(player, effect, affect) + "-green");
    }

    if (effect == EffectType::Fade) {
        R = getVar<float>(getKeyForEffect(player, effect, affect) + "1-red") * cycle + getVar<float>(getKeyForEffect(player, effect, affect) + "2-red") * (1 - cycle);
        B = getVar<float>(getKeyForEffect(player, effect, affect) + "1-blue") * cycle + getVar<float>(getKeyForEffect(player, effect, affect) + "2-blue") * (1 - cycle);
        G = getVar<float>(getKeyForEffect(player, effect, affect) + "1-green") * cycle + getVar<float>(getKeyForEffect(player, effect, affect) + "2-green") * (1 - cycle);
    }

	if (effect == EffectType::Rainbow) {
        float hue = fmod((cycle * 360), 360);
        float sat = 1;
        float vc = 1;
        HSVtoRGB(R, G, B, hue, sat, vc);
    }

	cocos2d::_ccColor3B out;
	out.r = R*255;
	out.g = G*255;
	out.b = B*255;
	return out;
}

void Icon::update(float dt) {
    if (cycle >= 1.0) backsweep = true;
    else if (cycle <= 0.0) backsweep = false;

    if (!backsweep) cycle += dt;
    else cycle -= dt;

    auto pl = PlayLayer::get();

    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player1, None, Color1)) && getVar<bool>(getKeyForEffect(Player1, (EffectType)i, Color1))) pl->m_player1->setColor(getEffectColor(Player1, (EffectType)i, Color1));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player1, None, Color2)) && getVar<bool>(getKeyForEffect(Player1, (EffectType)i, Color2))) pl->m_player1->setSecondColor(getEffectColor(Player1, (EffectType)i, Color2));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player1, None, Glow)) && getVar<bool>(getKeyForEffect(Player1, (EffectType)i, Glow))) pl->m_player1->m_iconGlow->setColor(getEffectColor(Player1, (EffectType)i, Glow));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player1, None, RegularTrail)) && getVar<bool>(getKeyForEffect(Player1, (EffectType)i, RegularTrail))) pl->m_player1->m_regularTrail->setColor(getEffectColor(Player1, (EffectType)i, RegularTrail));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player1, None, WaveTrail)) && getVar<bool>(getKeyForEffect(Player1, (EffectType)i, WaveTrail))) pl->m_player1->m_waveTrail->setColor(getEffectColor(Player1, (EffectType)i, WaveTrail));

    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player2, None, Color1)) && getVar<bool>(getKeyForEffect(Player2, (EffectType)i, Color1))) pl->m_player2->setColor(getEffectColor(Player2, (EffectType)i, Color1));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player2, None, Color2)) && getVar<bool>(getKeyForEffect(Player2, (EffectType)i, Color2))) pl->m_player2->setSecondColor(getEffectColor(Player2, (EffectType)i, Color2));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player2, None, Glow)) && getVar<bool>(getKeyForEffect(Player2, (EffectType)i, Glow))) pl->m_player2->m_iconGlow->setColor(getEffectColor(Player2, (EffectType)i, Glow));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player2, None, RegularTrail)) && getVar<bool>(getKeyForEffect(Player2, (EffectType)i, RegularTrail))) pl->m_player2->m_regularTrail->setColor(getEffectColor(Player2, (EffectType)i, RegularTrail));
    for (int i = 0; i < 3; i++) if (getVar<bool>(getKeyForEffect(Player2, None, WaveTrail)) && getVar<bool>(getKeyForEffect(Player2, (EffectType)i, WaveTrail))) pl->m_player2->m_waveTrail->setColor(getEffectColor(Player2, (EffectType)i, WaveTrail));
}

class $modify(PlayLayer) {
    void update(float dt) {
        Icon::get()->update(dt);

        PlayLayer::update(dt);

        if (getVar<bool>("solid_glow")) {
            m_player1->m_iconGlow->setOpacity(255);
            m_player1->m_iconGlow->setBlendFunc(m_player1->m_iconGlow->getBlendFunc());
        }
    }
};