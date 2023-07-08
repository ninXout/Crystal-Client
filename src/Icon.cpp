#include "Icon.hpp"
#include "CrystalProfile.hpp"

using namespace Crystal;
using namespace Icon;

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

void Icon::fade(float rgb1[4], float rgb2[4]) {
    R = rgb1[0] * cycle + rgb2[0] * (1-cycle);
    G = rgb1[1] * cycle + rgb2[1] * (1-cycle);
    B = rgb1[2] * cycle + rgb2[2] * (1-cycle);
}

cocos2d::_ccColor3B Icon::getEffectColor(EffectType effect, AffectedType affect) {
    if (effect == EffectType::Static) {
        switch (affect) {
            case P1Color1:
                colorConv(profile.StaticP1C1, R, G, B);
                break;
            case P1Color2:
                colorConv(profile.StaticP1C2, R, G, B);
                break;
            case P1Glow:
                colorConv(profile.StaticP1CG, R, G, B);
                break;
            case P1WaveTrail:
                colorConv(profile.StaticP1CW, R, G, B);
                break;
            case P1RegularTrail:
                colorConv(profile.StaticP1CR, R, G, B);
                break;
            case P2Color1:
                colorConv(profile.StaticP2C1, R, G, B);
                break;
            case P2Color2:
                colorConv(profile.StaticP2C2, R, G, B);
                break;
            case P2Glow:
                colorConv(profile.StaticP2CG, R, G, B);
                break;
            case P2WaveTrail:
                colorConv(profile.StaticP2CW, R, G, B);
                break;
            case P2RegularTrail:
                colorConv(profile.StaticP2CR, R, G, B);
                break;
        }
    }

    if (effect == EffectType::Fade) {
        switch (affect) {
            case P1Color1:
                fadeConv(profile.FadeP1C1E1, profile.FadeP1C1E2, R, G, B, cycle);
                break;
            case P1Color2:
                fadeConv(profile.FadeP1C2E1, profile.FadeP1C2E2, R, G, B, cycle);
                break;
            case P1Glow:
                fadeConv(profile.FadeP1GE1, profile.FadeP1GE2, R, G, B, cycle);
                break;
            case P1WaveTrail:
                fadeConv(profile.FadeP1WE1, profile.FadeP1WE2, R, G, B, cycle);
                break;
            case P1RegularTrail:
                fadeConv(profile.FadeP1RE1, profile.FadeP1RE2, R, G, B, cycle);
                break;
            case P2Color1:
                fadeConv(profile.FadeP2C1E1, profile.FadeP2C1E2, R, G, B, cycle);
                break;
            case P2Color2:
                fadeConv(profile.FadeP2C2E1, profile.FadeP2C2E2, R, G, B, cycle);
                break;
            case P2Glow:
                fadeConv(profile.FadeP2GE1, profile.FadeP2GE2, R, G, B, cycle);
                break;
            case P2WaveTrail:
                fadeConv(profile.FadeP2WE1, profile.FadeP2WE2, R, G, B, cycle);
                break;
            case P2RegularTrail:
                fadeConv(profile.FadeP2RE1, profile.FadeP2RE2, R, G, B, cycle);
                break;
        }
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

void Icon::update() {
    if (cycle >= 1.0) cycle = 0;
    cycle += 0.01;
    auto pl = PlayLayer::get();
    if (profile.P1Color1) {
        if (Crystal::profile.iconEffects[0]) {
            pl->m_player1->setColor(getEffectColor(Static, P1Color1));
        }
        if (Crystal::profile.iconEffects[1]) {
            pl->m_player1->setColor(getEffectColor(Fade, P1Color1));
        }
        if (Crystal::profile.iconEffects[2]) {
            pl->m_player1->setColor(getEffectColor(Rainbow, P1Color1));
        }
    }
    if (profile.P1Color2) {
        if (Crystal::profile.iconEffects[3]) {
            pl->m_player1->setSecondColor(getEffectColor(Static, P1Color2));
        }
        if (Crystal::profile.iconEffects[4]) {
            pl->m_player1->setSecondColor(getEffectColor(Fade, P1Color2));
        }
        if (Crystal::profile.iconEffects[5]) {
            pl->m_player1->setSecondColor(getEffectColor(Rainbow, P1Color2));
        }
    }
    if (profile.P1Glow) {
        if (Crystal::profile.iconEffects[6]) {
            pl->m_player1->setGlowColor(getEffectColor(Static, P1Glow));
        }
        if (Crystal::profile.iconEffects[7]) {
            pl->m_player1->setGlowColor(getEffectColor(Fade, P1Glow));
        }
        if (Crystal::profile.iconEffects[8]) {
            pl->m_player1->setGlowColor(getEffectColor(Rainbow, P1Glow));
        }
    }
    if (profile.P1Regular) {
        if (Crystal::profile.iconEffects[9]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Static, P1RegularTrail));
        }
        if (Crystal::profile.iconEffects[10]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Fade, P1RegularTrail));
        }
        if (Crystal::profile.iconEffects[11]) {
            pl->m_player1->m_regularTrail->setColor(getEffectColor(Rainbow, P1RegularTrail));
        }
    }
    if (profile.P1Wave) {
        if (Crystal::profile.iconEffects[12]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Static, P1WaveTrail));
        }
        if (Crystal::profile.iconEffects[13]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Fade, P1WaveTrail));
        }
        if (Crystal::profile.iconEffects[14]) {
            pl->m_player1->m_waveTrail->setColor(getEffectColor(Rainbow, P1WaveTrail));
        }
    }
    if (profile.P2Color1) {
        if (Crystal::profile.iconEffects[15]) {
            pl->m_player2->setColor(getEffectColor(Static, P2Color1));
        }
        if (Crystal::profile.iconEffects[16]) {
            pl->m_player2->setColor(getEffectColor(Fade, P2Color1));
        }
        if (Crystal::profile.iconEffects[17]) {
            pl->m_player2->setColor(getEffectColor(Rainbow, P2Color1));
        }
    }
    if (profile.P2Color2) {
        if (Crystal::profile.iconEffects[18]) {
            pl->m_player2->setSecondColor(getEffectColor(Static, P2Color2));
        }
        if (Crystal::profile.iconEffects[19]) {
            pl->m_player2->setSecondColor(getEffectColor(Fade, P2Color2));
        }
        if (Crystal::profile.iconEffects[20]) {
            pl->m_player2->setSecondColor(getEffectColor(Rainbow, P2Color2));
        }
    }
    if (profile.P2Glow) {
        if (Crystal::profile.iconEffects[21]) {
            pl->m_player2->setGlowColor(getEffectColor(Static, P2Glow));
        }
        if (Crystal::profile.iconEffects[22]) {
            pl->m_player2->setGlowColor(getEffectColor(Fade, P2Glow));
        }
        if (Crystal::profile.iconEffects[23]) {
            pl->m_player2->setGlowColor(getEffectColor(Rainbow, P2Glow));
        }
    }
    if (profile.P2Regular) {
        if (Crystal::profile.iconEffects[24]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Static, P2RegularTrail));
        }
        if (Crystal::profile.iconEffects[25]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Fade, P2RegularTrail));
        }
        if (Crystal::profile.iconEffects[26]) {
            pl->m_player2->m_regularTrail->setColor(getEffectColor(Rainbow, P2RegularTrail));
        }
    }
    if (profile.P2Wave) {
        if (Crystal::profile.iconEffects[27]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Static, P2WaveTrail));
        }
        if (Crystal::profile.iconEffects[28]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Fade, P2WaveTrail));
        }
        if (Crystal::profile.iconEffects[29]) {
            pl->m_player2->m_waveTrail->setColor(getEffectColor(Rainbow, P2WaveTrail));
        }
    }
}