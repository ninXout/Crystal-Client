#pragma once

#include "../Includes.hpp"

enum PlayerType {
    Player1,
    Player2
};

enum EffectType {
    Static,
    Rainbow,
    Fade,
    None
};

enum AffectedType {
    Color1,
    Color2,
    Glow,
    WaveTrail,
    RegularTrail
};

class Icon {
    public:
        static Icon* get();
        void update(float dt);
        cocos2d::_ccColor3B getEffectColor(PlayerType player, EffectType effect, AffectedType affect);
        std::string getKeyForEffect(PlayerType, EffectType, AffectedType);
        void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
    
    protected:
        bool backsweep = false;
        float cycle = 0;
        float R, G, B;
};