#include <variant>

//int frame = 0;
bool inLevel = false;
bool mouse1Down = false;
bool mouse2Down = false;
bool player1Dropping = false;
bool player2Dropping = false;

float nextXpos;
float nextYpos;
float nextRot;
float macroSpeed;
bool notDone = true;

// Dual Click
bool EnableDualClick = false;

// Spam
bool EnableSpam = false;

// Frame Advance
bool EnableFrameAdvance = false;
int FrameAdvanceKey = 0;
bool WaitForSetFrameAdvanceKeybind = false;

// Fake Clicks
bool EnableFakeClicks = false;
bool ClicksExist = false;

// RGB Menu
bool EnableRGBMenu = false;
bool EnableRGBMenuPrev = false;

// Menu Keybind
bool waitForFirstClick = false;

// Speedhack
float speedhackInputBox = 1.0f;
float speedhackSpeed = 1.0f;
bool speedhackBtnPressed = false;
void* channel;
bool initialized = false;
bool EnableSpeedhackAudio = false;
bool EnableFixRespawnTime = false;

// Practice Fix
bool EnablePracticeFix = false;

// FPS Bypass
float fpsbypassCapInput = 60.0f;
float fpsbypassCap = 60.0f;
bool fpsbypassBtnPressed = false;

// Macro Complete
bool showedMacroComplete = false;

// Macro Name Box
static char macroName[30] = "";

// ImGui
float BGColour[4] = { 0.12f, 0.12f, 0.12f, 1.0f };
float LightColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float DarkColour[4];
float VeryLightColour[4];
bool savedBtnPressed = false;
bool loadBtnPressed = false;
bool KeybindToggle = false;
bool showUI = true;
bool waitForSetKeybind = false;
int keybind = 0;
bool rewinding = false;
int maxFrame = 0;
bool SelectMacro = false;

ImVec4 RGBAtoIV4(float rgb[4]) {
	float newr = rgb[0];
	float newg = rgb[1];
	float newb = rgb[2];
	float newa = rgb[3];
	return ImVec4(newr, newg, newb, newa);
}

std::map<std::string, std::variant<std::deque<float>, std::deque<bool>, std::deque<double>, std::deque<int>>> Player1Data = {
	{"Xpos", std::deque<float>{}},
	{"Ypos", std::deque<float>{}},
	{"Rotation", std::deque<float>{}},
	{"Pushed", std::deque<bool>{}},
	{"Checkpoints", std::deque<int>{}},
	{"Yvelo", std::deque<double>{}},
	{"Dropping", std::deque<bool>{}}
};

std::map<std::string, std::variant<std::deque<float>, std::deque<bool>, std::deque<double>, std::deque<int>>> Player2Data = {
	{"Xpos", std::deque<float>{}},
	{"Ypos", std::deque<float>{}},
	{"Rotation", std::deque<float>{}},
	{"Pushed", std::deque<bool>{}},
	{"Yvelo", std::deque<double>{}},
	{"Dropping", std::deque<bool>{}}
};