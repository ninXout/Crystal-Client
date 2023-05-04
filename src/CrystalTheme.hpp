#pragma once

#include "json.hpp"
#include "Includes.hpp"
#include "CrystalProfile.hpp"

using json2 = nlohmann::json;

struct CrystalTheme {
    float rDir = -0.05;
    float gDir = 0.05;
    float bDir = -0.05;

    float BGColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float LightColour[4] = { 0.262715f,
                            0.624691f,
                            0.818605f,
                            1.0f };
    float TitleColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
    float DarkColour[4];
    float VeryLightColour[4];

    float borderRounding = 0;
    float scrollbarSize = 12;
    float scrollbarRounding = 12;

    bool RGBAccent = false;
    bool borders = false;
    bool rounded = false;
    bool titlebar = false;
    bool invisBG = false;
    bool diffTitleBar = false;

    static ImVec4 RGBAtoIV4(float rgb[4]) {
        float newr = rgb[0];
        float newg = rgb[1];
        float newb = rgb[2];
        float newa = rgb[3];
        return ImVec4(newr, newg, newb, newa);
    }
};

static inline CrystalTheme theme;

