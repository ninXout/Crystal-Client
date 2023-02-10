#include "hackpro.hpp"
#include "amethyst.hpp"

// hackpro.hpp is where all the bools for the hacks are
// dispatchKeyboardMSG is where the imgui is

cocos2d::CCScene* gui;
ImGuiNode* node;

using namespace tulip;
using namespace geode::cocos;

USE_GEODE_NAMESPACE();

class $modify(MainDispatcher, CCKeyboardDispatcher) {
	void saveMods() {
		std::ofstream clear("Crystal/config.cmp");
    	clear<<"";
		clear.close();
		std::fstream savefile;
savefile.open("Crystal/config.cmp", std::ios::app);
savefile << noclip << '\n';
savefile << deathEffect << '\n';
savefile << particles << '\n';
savefile << progressBar << '\n';
savefile << accpercentage << '\n';
savefile << nopulse << '\n';
savefile << freecopy << '\n';
savefile << unlockall << '\n';
savefile << hideatts << '\n';
savefile << hidepracatts << '\n';
savefile << safe << '\n';
savefile << pracmusic << '\n';
savefile << rainP1 << '\n';
savefile << rainP2 << '\n';
savefile << rainP1wave << '\n';
savefile << rainP2wave << '\n';
savefile << respawn << '\n';
savefile << startpos << '\n';
savefile << slider << '\n';
savefile << objlimit << '\n';
savefile << customobjlimit << '\n';
savefile << customlimit << '\n';
savefile << invis << '\n';
savefile << verify << '\n';
savefile << anticheat << '\n';
savefile << moon << '\n';
savefile << speed << '\n';
savefile << autoclick << '\n';
savefile << drawTrail << '\n';
savefile << noLimitTrail << '\n';
savefile << onDeath << '\n';
savefile << onlyHitbox << '\n';
savefile << fps << '\n';
savefile << levelinfo << '\n';
savefile << clicks << '\n';
savefile << jumps << '\n';
savefile << editorkey << '\n';
savefile << plugin << '\n';
savefile << zoomhack << '\n';
savefile << layout << '\n';
savefile << ldm << '\n';
savefile << randomLoop << '\n';
savefile << cheater << '\n';
savefile << ignoreESC << '\n';
savefile << noglow << '\n';
savefile << mirror << '\n';
savefile << anykey << '\n';
savefile << solidwave << '\n';
savefile << samedual << '\n';
savefile << complete << '\n';
savefile << uncomplete << '\n';
savefile << framestep << '\n';
savefile << noRot << '\n';
savefile << totalAtts << '\n';
savefile << lastDeath << '\n';
savefile << instantdeath << '\n';
savefile << dualcontrol << '\n';
savefile << notrail << '\n';
savefile << nospike << '\n';
savefile << forcefade << '\n';
savefile << forceenter << '\n';
savefile << accuracy << '\n';
savefile << unfocusmute << '\n';
savefile << freeze << '\n';
savefile << autoKill << '\n';
savefile << autoreset << '\n';
savefile << customMessage << '\n';
savefile << editorHitbox << '\n';
savefile << turnonHitbox << '\n';
savefile << attempts << '\n';
savefile << currentRun << '\n';
savefile << bestRun << '\n';
savefile << clickreset << '\n';
savefile << resetaccuracy << '\n';
savefile << nodim << '\n';
savefile << noclipDeaths << '\n';
savefile << author << '\n';
savefile << hideID << '\n';
savefile << cpswitch << '\n';
savefile << scrollzoom << '\n';
savefile << noclipP1 << '\n';
savefile << noclipP2 << '\n';
savefile << lastCheckpoint << '\n';
savefile << keybinds << '\n';
savefile << key_current << '\n';
savefile << mod_current << '\n';
savefile << key_current2 << '\n';
savefile << mod_current2 << '\n';
savefile << key_current3 << '\n';
savefile << mod_current3 << '\n';
savefile << key_current4 << '\n';
savefile << mod_current4 << '\n';
savefile << key_current5 << '\n';
savefile << mod_current5 << '\n';
savefile << pulse << '\n';
savefile << rainbowspeed << '\n';
savefile << confirmQuit << '\n';
savefile << message << '\n';
savefile << inputmirror << '\n';
savefile << pausecountdown << '\n';
savefile.close();
	}

	void loadMods() {
		std::fstream savefile;
		std::string line;
		savefile.open("Crystal/config.cmp", std::ios::in);
		if (savefile.is_open()) {
		getline(savefile, line);
		if (line == "1") {
			noclip = true;
		} else if (line == "0") {
			noclip = false;
		}
		getline(savefile, line);
		if (line == "1") {
			deathEffect = true;
		} else if (line == "0") {
			deathEffect = false;
		}
		getline(savefile, line);
		if (line == "1") {
			particles = true;
		} else if (line == "0") {
			particles = false;
		}
		getline(savefile, line);
		if (line == "1") {
			progressBar = true;
		} else if (line == "0") {
			progressBar = false;
		}
		getline(savefile, line);
		if (line == "1") {
			accpercentage = true;
		} else if (line == "0") {
			accpercentage = false;
		}
		getline(savefile, line);
		if (line == "1") {
			nopulse = true;
		} else if (line == "0") {
			nopulse = false;
		}
		getline(savefile, line);
		if (line == "1") {
			freecopy = true;
		} else if (line == "0") {
			freecopy = false;
		}
		getline(savefile, line);
		if (line == "1") {
			unlockall = true;
		} else if (line == "0") {
			unlockall = false;
		}
		getline(savefile, line);
		if (line == "1") {
			hideatts = true;
		} else if (line == "0") {
			hideatts = false;
		}
		getline(savefile, line);
		if (line == "1") {
			hidepracatts = true;
		} else if (line == "0") {
			hidepracatts = false;
		}
		getline(savefile, line);
		if (line == "1") {
			safe = true;
		} else if (line == "0") {
			safe = false;
		}
		getline(savefile, line);
		if (line == "1") {
			pracmusic = true;
		} else if (line == "0") {
			pracmusic = false;
		}
		getline(savefile, line);
		if (line == "1") {
			rainP1 = true;
		} else if (line == "0") {
			rainP1 = false;
		}
		getline(savefile, line);
		if (line == "1") {
			rainP2 = true;
		} else if (line == "0") {
			rainP2 = false;
		}
		getline(savefile, line);
		if (line == "1") {
			rainP1wave = true;
		} else if (line == "0") {
			rainP1wave = false;
		}
		getline(savefile, line);
		if (line == "1") {
			rainP2wave = true;
		} else if (line == "0") {
			rainP2wave = false;
		}
		getline(savefile, line);
		if (line == "1") {
			respawn = true;
		} else if (line == "0") {
			respawn = false;
		}
		getline(savefile, line);
		if (line == "1") {
			startpos = true;
		} else if (line == "0") {
			startpos = false;
		}
		getline(savefile, line);
		if (line == "1") {
			slider = true;
		} else if (line == "0") {
			slider = false;
		}
		getline(savefile, line);
		if (line == "1") {
			objlimit = true;
		} else if (line == "0") {
			objlimit = false;
		}
		getline(savefile, line);
		if (line == "1") {
			customobjlimit = true;
		} else if (line == "0") {
			customobjlimit = false;
		}
		getline(savefile, line);
		if (line == "1") {
			customlimit = true;
		} else if (line == "0") {
			customlimit = false;
		}
		getline(savefile, line);
		if (line == "1") {
			invis = true;
		} else if (line == "0") {
			invis = false;
		}
		getline(savefile, line);
		if (line == "1") {
			verify = true;
		} else if (line == "0") {
			verify = false;
		}
		getline(savefile, line);
		if (line == "1") {
			anticheat = true;
		} else if (line == "0") {
			anticheat = false;
		}
		getline(savefile, line);
		if (line == "1") {
			moon = true;
		} else if (line == "0") {
			moon = false;
		}
		getline(savefile, line);
		if (line == "1") {
			speed = true;
		} else if (line == "0") {
			speed = false;
		}
		getline(savefile, line);
		if (line == "1") {
			autoclick = true;
		} else if (line == "0") {
			autoclick = false;
		}
		getline(savefile, line);
		if (line == "1") {
			drawTrail = true;
		} else if (line == "0") {
			drawTrail = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noLimitTrail = true;
		} else if (line == "0") {
			noLimitTrail = false;
		}
		getline(savefile, line);
		if (line == "1") {
			onDeath = true;
		} else if (line == "0") {
			onDeath = false;
		}
		getline(savefile, line);
		if (line == "1") {
			onlyHitbox = true;
		} else if (line == "0") {
			onlyHitbox = false;
		}
		getline(savefile, line);
		if (line == "1") {
			fps = true;
		} else if (line == "0") {
			fps = false;
		}
		getline(savefile, line);
		if (line == "1") {
			levelinfo = true;
		} else if (line == "0") {
			levelinfo = false;
		}
		getline(savefile, line);
		if (line == "1") {
			clicks = true;
		} else if (line == "0") {
			clicks = false;
		}
		getline(savefile, line);
		if (line == "1") {
			jumps = true;
		} else if (line == "0") {
			jumps = false;
		}
		getline(savefile, line);
		if (line == "1") {
			editorkey = true;
		} else if (line == "0") {
			editorkey = false;
		}
		getline(savefile, line);
		if (line == "1") {
			plugin = true;
		} else if (line == "0") {
			plugin = false;
		}
		getline(savefile, line);
		if (line == "1") {
			zoomhack = true;
		} else if (line == "0") {
			zoomhack = false;
		}
		getline(savefile, line);
		if (line == "1") {
			layout = true;
		} else if (line == "0") {
			layout = false;
		}
		getline(savefile, line);
		if (line == "1") {
			ldm = true;
		} else if (line == "0") {
			ldm = false;
		}
		getline(savefile, line);
		if (line == "1") {
			randomLoop = true;
		} else if (line == "0") {
			randomLoop = false;
		}
		getline(savefile, line);
		if (line == "1") {
			cheater = true;
		} else if (line == "0") {
			cheater = false;
		}
		getline(savefile, line);
		if (line == "1") {
			ignoreESC = true;
		} else if (line == "0") {
			ignoreESC = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noglow = true;
		} else if (line == "0") {
			noglow = false;
		}
		getline(savefile, line);
		if (line == "1") {
			mirror = true;
		} else if (line == "0") {
			mirror = false;
		}
		getline(savefile, line);
		if (line == "1") {
			anykey = true;
		} else if (line == "0") {
			anykey = false;
		}
		getline(savefile, line);
		if (line == "1") {
			solidwave = true;
		} else if (line == "0") {
			solidwave = false;
		}
		getline(savefile, line);
		if (line == "1") {
			samedual = true;
		} else if (line == "0") {
			samedual = false;
		}
		getline(savefile, line);
		if (line == "1") {
			complete = true;
		} else if (line == "0") {
			complete = false;
		}
		getline(savefile, line);
		if (line == "1") {
			uncomplete = true;
		} else if (line == "0") {
			uncomplete = false;
		}
		getline(savefile, line);
		if (line == "1") {
			framestep = true;
		} else if (line == "0") {
			framestep = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noRot = true;
		} else if (line == "0") {
			noRot = false;
		}
		getline(savefile, line);
		if (line == "1") {
			totalAtts = true;
		} else if (line == "0") {
			totalAtts = false;
		}
		getline(savefile, line);
		if (line == "1") {
			lastDeath = true;
		} else if (line == "0") {
			lastDeath = false;
		}
		getline(savefile, line);
		if (line == "1") {
			instantdeath = true;
		} else if (line == "0") {
			instantdeath = false;
		}
		getline(savefile, line);
		if (line == "1") {
			dualcontrol = true;
		} else if (line == "0") {
			dualcontrol = false;
		}
		getline(savefile, line);
		if (line == "1") {
			notrail = true;
		} else if (line == "0") {
			notrail = false;
		}
		getline(savefile, line);
		if (line == "1") {
			nospike = true;
		} else if (line == "0") {
			nospike = false;
		}
		getline(savefile, line);
		if (line == "1") {
			forcefade = true;
		} else if (line == "0") {
			forcefade = false;
		}
		getline(savefile, line);
		if (line == "1") {
			forceenter = true;
		} else if (line == "0") {
			forceenter = false;
		}
		getline(savefile, line);
		if (line == "1") {
			accuracy = true;
		} else if (line == "0") {
			accuracy = false;
		}
		getline(savefile, line);
		if (line == "1") {
			unfocusmute = true;
		} else if (line == "0") {
			unfocusmute = false;
		}
		getline(savefile, line);
		if (line == "1") {
			freeze = true;
		} else if (line == "0") {
			freeze = false;
		}
		getline(savefile, line);
		if (line == "1") {
			autoKill = true;
		} else if (line == "0") {
			autoKill = false;
		}
		getline(savefile, line);
		if (line == "1") {
			autoreset = true;
		} else if (line == "0") {
			autoreset = false;
		}
		getline(savefile, line);
		if (line == "1") {
			customMessage = true;
		} else if (line == "0") {
			customMessage = false;
		}
		getline(savefile, line);
		if (line == "1") {
			editorHitbox = true;
		} else if (line == "0") {
			editorHitbox = false;
		}
		getline(savefile, line);
		if (line == "1") {
			turnonHitbox = true;
		} else if (line == "0") {
			turnonHitbox = false;
		}
		getline(savefile, line);
		if (line == "1") {
			attempts = true;
		} else if (line == "0") {
			attempts = false;
		}
		getline(savefile, line);
		if (line == "1") {
			currentRun = true;
		} else if (line == "0") {
			currentRun = false;
		}
		getline(savefile, line);
		if (line == "1") {
			bestRun = true;
		} else if (line == "0") {
			bestRun = false;
		}
		getline(savefile, line);
		if (line == "1") {
			clickreset = true;
		} else if (line == "0") {
			clickreset = false;
		}
		getline(savefile, line);
		if (line == "1") {
			resetaccuracy = true;
		} else if (line == "0") {
			resetaccuracy = false;
		}
		getline(savefile, line);
		if (line == "1") {
			nodim = true;
		} else if (line == "0") {
			nodim = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noclipDeaths = true;
		} else if (line == "0") {
			noclipDeaths = false;
		}	
		getline(savefile, line);
		if (line == "1") {
			author = true;
		} else if (line == "0") {
			author = false;
		}
		getline(savefile, line);
		if (line == "1") {
			hideID = true;
		} else if (line == "0") {
			hideID = false;
		}
		getline(savefile, line);
		if (line == "1") {
			cpswitch = true;
		} else if (line == "0") {
			cpswitch = false;
		}
		getline(savefile, line);
		if (line == "1") {
			scrollzoom = true;
		} else if (line == "0") {
			scrollzoom = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noclipP1 = true;
		} else if (line == "0") {
			noclipP1 = false;
		}
		getline(savefile, line);
		if (line == "1") {
			noclipP2 = true;
		} else if (line == "0") {
			noclipP2 = false;
		}
		getline(savefile, line);
		if (line == "1") {
			lastCheckpoint = true;
		} else if (line == "0") {
			lastCheckpoint = false;
		}
		std::string mod;
		std::string key;
		getline(savefile, mod);
		keybinds = stoi(mod);
		getline(savefile, key);
		key_current = stoi(key);
		getline(savefile, mod);
		mod_current = stoi(mod);
		getline(savefile, key);
		key_current2 = stoi(key);
		getline(savefile, mod);
		mod_current2 = stoi(mod);
		getline(savefile, key);
		key_current3 = stoi(key);
		getline(savefile, mod);
		mod_current3 = stoi(mod);
		getline(savefile, key);
		key_current4 = stoi(key);
		getline(savefile, mod);
		mod_current4 = stoi(mod);
		getline(savefile, key);
		key_current5 = stoi(key);
		getline(savefile, mod);
		mod_current5 = stoi(mod);
		getline(savefile, key);
		pulse = stof(key);
		getline(savefile, mod);
		rainbowspeed = stof(mod);
		getline(savefile, line);
		if (line == "1") {
			confirmQuit = true;
		} else if (line == "0") {
			confirmQuit = false;
		}
		getline(savefile, line);
		strcpy(message, line.c_str());
		getline(savefile, line);
		if (line == "1") {
			pausecountdown = true;
		} else if (line == "0") {
			pausecountdown = false;
		}
		getline(savefile, line);
		if (line == "1") {
			inputmirror = true;
		} else if (line == "0") {
			inputmirror = false;
		}
		savefile.close();
		}
	}

	void crystal_exists(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{})
{
    std::cout << p;
    if(std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p)){
		//do nothing
	} else {
		std::filesystem::create_directories(p);
		/*
		std::fstream ini;
		ini.open("imgui.ini", std::ios::app);
		ini << "[Window][Dear ImGui Demo]"
		"Pos=164,499" << std::endl <<
		"Size=564,553" << std::endl <<
		"Collapsed=1" << std::endl << "[Window][Global]" <<
		"Pos=1001,5" << std::endl <<
		"Size=278,252" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Dev Settings]" <<
		"Pos=126,263" << std::endl <<
		"Size=382,272" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Player Icon]" <<
		"Pos=448,4" << std::endl <<
		"Size=219,215" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Display]" <<
		"Pos=7,4" << std::endl <<
		"Size=205,417" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Bypasses]" <<
		"Pos=221,1" << std::endl <<
		"Size=220,274" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Fun Stuff]" <<
		"Pos=223,279" << std::endl <<
		"Size=221,164" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Amethyst [BETA]]" <<
		"Pos=1007,264" << std::endl <<
		"Size=269,175" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Locked]" <<
		"Pos=344,438" << std::endl <<
		"Size=448,87" << std::endl <<
		"Collapsed=0" << std::endl << "[Window][Hitbox Viewer]" <<
		"Pos=449,225" << std::endl << "Size=216,177" << std::endl << "Collapsed=0" << std::endl << "[Window][General]" <<
		"Pos=677,6" << std::endl << "Size=319,707" <<
		"Collapsed=0" << std::endl;
		*/
	}
}

    bool dispatchKeyboardMSG(enumKeyCodes key, bool down) {
		auto platform = reinterpret_cast<PlatformToolbox*>(PlayLayer::get());
		node = ImGuiNode::create([]() {
			if (showing) {
				ImGuiStyle * style = &ImGui::GetStyle();

				if (theme == 1) {
					ImVec4* colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg]                = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab]             = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button]                 = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive]        = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab]                    = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram]          = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight]           = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  style->WindowPadding                     = ImVec2(8.00f, 8.00f);
  style->FramePadding                      = ImVec2(5.00f, 2.00f);
  style->CellPadding                       = ImVec2(6.00f, 6.00f);
  style->ItemSpacing                       = ImVec2(6.00f, 6.00f);
  style->ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
  style->TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
  style->IndentSpacing                     = 25;
  style->ScrollbarSize                     = 15;
  style->GrabMinSize                       = 10;
  style->WindowBorderSize                  = 1;
  style->ChildBorderSize                   = 1;
  style->PopupBorderSize                   = 1;
  style->FrameBorderSize                   = 1;
  style->TabBorderSize                     = 1;
  style->WindowRounding                    = 7;
  style->ChildRounding                     = 4;
  style->FrameRounding                     = 3;
  style->PopupRounding                     = 4;
  style->ScrollbarRounding                 = 9;
  style->GrabRounding                      = 3;
  style->LogSliderDeadzone                 = 4;
  style->TabRounding                       = 4;
				} else if (theme == 2) {
					style->Alpha = 1.0f;
        style->FrameRounding = 3.0f;
        style->Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
        style->Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style->Colors[ImGuiCol_Border]                = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
        style->Colors[ImGuiCol_BorderShadow]          = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
        style->Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
        style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        style->Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
        style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
        style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
        style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
        style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_Button]                = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_Header]                = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style->Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        style->Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				} else if (theme == 3) {
     
    	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
				}

				ImGui::Begin("General", &showing);
				if (ImGui::TreeNode("Noclip"))
    			{
        			ImGui::Checkbox("Noclip", &noclip);
					ImGui::Checkbox("Noclip Player 1", &noclipP1);
					ImGui::Checkbox("Noclip Player 2", &noclipP2);
        			ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("No Spikes", &nospike);
				ImGui::Checkbox("Disable Death Effect", &deathEffect);
				ImGui::Checkbox("Disable Particles", &particles);
				ImGui::Checkbox("Disable Progressbar", &progressBar);
				ImGui::Checkbox("Accurate Percentage", &accpercentage);
				ImGui::Checkbox("No Wave Pulse", &nopulse);
				ImGui::InputFloat("Wave Trail Size", &pulse, 0.01f, 10.00f, "%.2f");
				ImGui::Checkbox("Hide Attempts", &hideatts);
				ImGui::Checkbox("Hide Attempts in Practice Mode", &hidepracatts);
				ImGui::Checkbox("Practice Music Hack", &pracmusic);
				ImGui::Checkbox("Ignore ESC", &ignoreESC);
				ImGui::Checkbox("Confirm Quit", &confirmQuit);
				ImGui::Checkbox("Pause Countdown", &pausecountdown);
				ImGui::Checkbox("Auto LDM", &ldm);
				ImGui::Checkbox("Any Key Jump", &anykey);
				ImGui::Checkbox("Instant Death Respawn", &instantdeath);
				ImGui::Checkbox("Flipped Dual Controls", &dualcontrol);
				ImGui::Checkbox("Mirrored Dual Controls", &inputmirror);
				ImGui::Checkbox("StartPos Switcher", &startpos);
				ImGui::Checkbox("Respawn Bug Fix", &respawn);
				ImGui::Checkbox("Practice Orb Bug Fix", &practiceOrb);
				ImGui::Checkbox("Checkpoint Switcher [BETA]", &cpswitch);
				ImGui::Checkbox("Editor Scroll Zoom", &scrollzoom);
				ImGui::Checkbox("Solid Wave Trail", &solidwave);
				ImGui::Checkbox("Frame Stepper", &framestep);
				ImGui::Checkbox("Load from Last Checkpoint", &lastCheckpoint);
				ImGui::Checkbox("Auto Reset", &autoreset);
				ImGui::InputInt("Auto Reset Percentage", &autoresetnum, 1, 99);
				ImGui::Checkbox("Invisible Player", &invis);
				ImGui::Checkbox("No Trail", &notrail);
				ImGui::Checkbox("No Glow", &noglow);
				//ImGui::Checkbox("No Spikes", &dev);
				ImGui::Checkbox("No Mirror", &mirror);
				ImGui::Checkbox("Force Don't Fade", &forcefade);
				ImGui::Checkbox("Force Don't Enter", &forceenter);
				ImGui::Checkbox("Layout Mode", &layout);
				if (ImGui::TreeNode("Autoclicker"))
    			{
        			ImGui::Checkbox("Autoclicker", &autoclick);
					ImGui::SliderInt("Push Frames", &clickPush, 0, 10);
					ImGui::SliderInt("Release Frames", &clickRel, 0, 10);
					ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Suicide", &autoKill);
				ImGui::End();
				ImGui::Begin("Keybinds");
				ImGui::InputInt("Keybindings", &keybinds, 0, 3);
				if (keybinds >= 1) {
					if (ImGui::TreeNode("Keybind 1"))
    				{
        				ImGui::Combo("Keys", &key_current, keys, IM_ARRAYSIZE(keys));
						ImGui::Combo("Mods", &mod_current, mods, IM_ARRAYSIZE(mods));
						ImGui::Separator();
        				ImGui::TreePop();
    				}
				}
				if (keybinds >= 2) {
					if (ImGui::TreeNode("Keybind 2"))
    				{
        				ImGui::Combo("Keys", &key_current2, keys2, IM_ARRAYSIZE(keys2));
						ImGui::Combo("Mods", &mod_current2, mods2, IM_ARRAYSIZE(mods2));
						ImGui::Separator();
        				ImGui::TreePop();
    				}
				}
				if (keybinds >= 3) {
					if (ImGui::TreeNode("Keybind 3"))
    				{
        				ImGui::Combo("Keys", &key_current3, keys3, IM_ARRAYSIZE(keys3));
						ImGui::Combo("Mods", &mod_current3, mods3, IM_ARRAYSIZE(mods3));
						ImGui::Separator();
        				ImGui::TreePop();
    				}
				}
				if (keybinds >= 4) {
					if (ImGui::TreeNode("Keybind 4"))
    				{
        				ImGui::Combo("Keys", &key_current4, keys4, IM_ARRAYSIZE(keys4));
						ImGui::Combo("Mods", &mod_current4, mods4, IM_ARRAYSIZE(mods4));
						ImGui::Separator();
        				ImGui::TreePop();
    				}
				}
				if (keybinds >= 5) {
					if (ImGui::TreeNode("Keybind 5"))
    				{
        				ImGui::Combo("Keys", &key_current5, keys5, IM_ARRAYSIZE(keys5));
						ImGui::Combo("Mods", &mod_current5, mods5, IM_ARRAYSIZE(mods5));
						ImGui::Separator();
        				ImGui::TreePop();
    				}
				}
				ImGui::End();
				ImGui::Begin("Player Icon");
				ImGui::Checkbox("Random Icons (maybe)", &dev);
				if (ImGui::TreeNode("Rainbow"))
    			{
        			ImGui::Checkbox("Rainbow Player 1", &rainP1);
					ImGui::Checkbox("Rainbow Player 2", &rainP2);
					ImGui::Checkbox("Rainbow Player 1 (Wave)", &rainP1wave);
					ImGui::Checkbox("Rainbow Player 2 (Wave)", &rainP2wave);
					ImGui::InputFloat("Rainbow Effect Speed", &rainbowspeed, 0.1f, 50.0f, "%.1f");
					ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Same Color Dual", &samedual);
				ImGui::InputInt(" ", &customR1, 1, 255);
				//ImGui::SameLine();
				ImGui::InputInt(" ", &customG1, 1, 255);
				//ImGui::SameLine();
				ImGui::InputInt(" ", &customB1, 1, 255);
				ImGui::InputInt(" ", &customR2, 1, 255);
				//ImGui::SameLine();
				ImGui::InputInt(" ", &customG2, 1, 255);
				//ImGui::SameLine();
				ImGui::InputInt(" ", &customB2, 1, 255);
				ImGui::Checkbox("Custom Icon Color", &customColor);
				ImGui::End();
				ImGui::GetStyle().WindowRounding = 10.0f;
				ImGui::Begin("Display");
				if (ImGui::TreeNode("Customize Percentage"))
    			{
					ImGui::InputFloat("X Position", &percentXpos, 0.01f, 500.00f, "%.3f");
					ImGui::InputFloat("Y Position", &percentYpos, 0.01f, 500.00f, "%.3f");
					ImGui::InputFloat("Scale", &percentScale, 0.01f, 1.00f, "%.2f");
					ImGui::InputFloat("Opacity", &percentOpac, 0.01f, 255.00f, "%.2f");
        			ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Custom Message", &customMessage);
				ImGui::InputTextWithHint(" ", "Custom Message", message, IM_ARRAYSIZE(message));
				ImGui::Checkbox("FPS Display", &fps);
				if (ImGui::TreeNode("CPS and Clicks"))
    			{
					ImGui::Checkbox("CPS and Clicks", &clicks);
					ImGui::Checkbox("Reset clicks each attempt", &clickreset);
        			ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Jumps", &jumps);
				ImGui::Checkbox("Cheat Indicator", &cheater);
				ImGui::Checkbox("Last Death", &lastDeath);
				ImGui::Checkbox("Session Attempts", &attempts);
				ImGui::Checkbox("Best Run", &bestRun);
				ImGui::Checkbox("Run From", &currentRun);
				if (ImGui::TreeNode("Noclip Accuracy"))
    			{
					ImGui::Checkbox("Noclip Accuracy", &accuracy);
					ImGui::Checkbox("Increased Leniency", &lenient);
					ImGui::InputFloat("Kill at Accuracy", &killaccuracy, 0.00f, 99.99f, "%.2f");
					ImGui::Checkbox("Reset at Accuracy", &resetaccuracy);
        			ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Noclip Deaths", &noclipDeaths);
				ImGui::Checkbox("Total Attempts", &totalAtts);
				if (ImGui::TreeNode("Level Name and ID"))
    			{
					ImGui::Checkbox("Level Name and ID", &levelinfo);
					ImGui::Checkbox("Show Author", &author);
					ImGui::Checkbox("Hide Level ID", &hideID);
        			ImGui::Separator();
        			ImGui::TreePop();
    			}
				ImGui::Checkbox("Macro Status", &macroStatus);
				ImGui::End();
				ImGui::Begin("Bypasses");
				//ImGui::Checkbox("Anticheat Bypass", &anticheat);
				ImGui::Checkbox("Unlock All", &unlockall);
				ImGui::Checkbox("Object Limit Bypass", &objlimit);
				ImGui::Checkbox("Custom Object Object Limit Bypass", &customobjlimit);
				ImGui::Checkbox("Custom Object Limit Bypass", &customlimit);
				ImGui::Checkbox("Verify Bypass", &verify);
				ImGui::Checkbox("Copy Bypass", &freecopy);
				ImGui::Checkbox("Slider Bypass", &slider);
				ImGui::Checkbox("Editor Zoom Bypass", &zoomhack);
				ImGui::Checkbox("Instant Complete", &complete);
				ImGui::End();
				ImGui::Begin("Shortcuts");
				//ImGui::Checkbox("Main Menu Image Background", &dev);
				//ImGui::Checkbox("Menu Loop Randomizer", &randomLoop);
				//ImGui::Checkbox("Moonjump", &moon);
				//ImGui::Checkbox("Superspeed", &speed);
				//ImGui::Checkbox("Freeze", &freeze);
				if (manualNONG) {
					ImGui::InputTextWithHint("Manual Replace", "Manual Replace", replacing, IM_ARRAYSIZE(replacing));
				}
				ImGui::Checkbox("Manual Replace", &manualNONG);
				ImGui::InputTextWithHint("Replace", "Replace", replaceWith, IM_ARRAYSIZE(replaceWith));
				static ImGuiComboFlags flags = 0;
				const char* combo_preview_value = items[item_current_idx];
				/*
				if (ImGui::BeginCombo("NONGs", combo_preview_value, flags))
        		{
            		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            		{
                		const bool is_selected = (item_current_idx == n);
                		if (ImGui::Selectable(items[n], is_selected)) item_current_idx = n;

                		// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                		if (is_selected) ImGui::SetItemDefaultFocus();
            		}
            		ImGui::EndCombo();
        		}
				*/
				ImGui::Checkbox("Enable NONG Loader", &EnableNONGLoader);
				if (ImGui::Button("Open Songs Folder")) {
					system("open ~/Library/Caches");
				}
				if (ImGui::Button("Open Crystal Folder")) {
					system("open Crystal");
				}
				if (ImGui::Button("Open Resources Folder")) {
					system("open Resources");
				}
				if (ImGui::Button("Open GD Settings")) {
					OptionsLayer::addToCurrentScene(false);
				}
				if (ImGui::Button("Toggle Practice Mode")) {
					if (PlayLayer::get()) PlayLayer::get()->togglePracticeMode(PlayLayer::get()->m_isPracticeMode == false);
				}
				if (ImGui::Button("Restart Level")) {
					if (PlayLayer::get()) PlayLayer::get()->resetLevel();
				}
				ImGui::End();
				ImGui::Begin("Hitbox Viewer");
				ImGui::Checkbox("Turn On Hitboxes", &turnonHitbox);
				ImGui::Checkbox("Show Hitboxes on Death", &onDeath);
				ImGui::Checkbox("Show only Hitboxes", &onlyHitbox);
				ImGui::Checkbox("Show Hitbox trail", &drawTrail);
				ImGui::Checkbox("Don't limit Hitbox trail", &noLimitTrail);
				ImGui::Checkbox("Show Hitboxes in Editor", &editorHitbox);
				ImGui::End();
				ImGui::Begin("Variable Changer");
				ImGui::Combo(" ", &variable_index, variables, IM_ARRAYSIZE(variables));
				ImGui::InputTextWithHint("Value", "Value", stringVC, IM_ARRAYSIZE(stringVC));
				ImGui::Checkbox("Apply", &applyVC);
				ImGui::End();
				ImGui::Begin("Amethyst [BETA]");
				ImGui::Checkbox("Enable Amethyst [BETA]", &amethyst);
				ImGui::Checkbox("Record", &recording);
				ImGui::SameLine();
				ImGui::Checkbox("Replay", &replay);
				ImGui::InputTextWithHint("Macro Name", "Macro Name", macroname, IM_ARRAYSIZE(macroname));
				ImGui::Checkbox("Click Bot", &clickBot);
				ImGui::Checkbox("Smooth Frames", &smoothFrames);
				if (ImGui::Button("Save Macro")) {
					std::string stringname;
    				std::stringstream ss;
    				ss << macroname;
    				ss >> stringname;
					std::fstream myfile("Crystal/Amethyst/Macros/" + stringname + ".thyst", std::ios::app);
					if (myfile.is_open()) {
						myfile << macroSpeed;
						myfile << std::get<std::deque<float>>(Player1Data["Xpos"]).size() << "\n";
						myfile << std::get<std::deque<float>>(Player1Data["Ypos"]).size() << "\n";
						myfile << std::get<std::deque<float>>(Player1Data["Rotation"]).size() << "\n";
						myfile << std::get<std::deque<bool>>(Player1Data["Pushed"]).size() << "\n";
						for (float xpos : std::get<std::deque<float>>(Player1Data["Xpos"])) myfile << std::setprecision(10) << std::fixed << xpos << "\n";
						for (float ypos : std::get<std::deque<float>>(Player1Data["Ypos"])) myfile << std::setprecision(10) << std::fixed << ypos << "\n";
						for (float rotation : std::get<std::deque<float>>(Player1Data["Rotation"])) myfile << std::setprecision(10) << std::fixed << rotation << "\n";
						for (bool pushed : std::get<std::deque<bool>>(Player1Data["Pushed"])) myfile << pushed << "\n";
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Load Macro")) {
					std::string line;
					std::fstream myfile;
					std::string stringname;
    				std::stringstream ss;
    				ss << macroname;
    				ss >> stringname;
					myfile.open(("Crystal/Amethyst/Macros/" + stringname + ".thyst"), std::ios::in);
					if (myfile.is_open()) {
						std::get<std::deque<float>>(Player1Data["Xpos"]).clear();
						std::get<std::deque<float>>(Player1Data["Ypos"]).clear();
						std::get<std::deque<float>>(Player1Data["Rotation"]).clear();
						std::get<std::deque<bool>>(Player1Data["Pushed"]).clear();

						getline(myfile, line);
						macroSpeed = stof(line);
						getline(myfile, line);
						int XposLines = stoi(line);
						getline(myfile, line);
						int YposLines = stoi(line);
						getline(myfile, line);
						int RotationLines = stoi(line);
						getline(myfile, line);
						int PushedLines = stoi(line);
						bool pushed1;
						for (int lineno = 1; lineno <= XposLines; lineno++) { getline(myfile, line); std::get<std::deque<float>>(Player1Data["Xpos"]).insert(std::get<std::deque<float>>(Player1Data["Xpos"]).end(), stof(line)); }
						for (int lineno = 1; lineno <= YposLines; lineno++) { getline(myfile, line); std::get<std::deque<float>>(Player1Data["Ypos"]).insert(std::get<std::deque<float>>(Player1Data["Ypos"]).end(), stof(line)); }
						for (int lineno = 1; lineno <= RotationLines; lineno++) { getline(myfile, line); std::get<std::deque<float>>(Player1Data["Rotation"]).insert(std::get<std::deque<float>>(Player1Data["Rotation"]).end(), stof(line)); }
						for (int lineno = 1; lineno <= PushedLines; lineno++) { getline(myfile, line); std::stringstream(line) >> pushed1; std::get<std::deque<bool>>(Player1Data["Pushed"]).insert(std::get<std::deque<bool>>(Player1Data["Pushed"]).end(), pushed1); }
					}
				}
				if (ImGui::Button("Clear Macro")) {
					std::get<std::deque<float>>(Player1Data["Xpos"]).clear();
					std::get<std::deque<float>>(Player1Data["Ypos"]).clear();
					std::get<std::deque<float>>(Player1Data["Rotation"]).clear();
					std::get<std::deque<bool>>(Player1Data["Pushed"]).clear();
				}
				if (ImGui::Button("Stepback")) {
					system("screencapture -x quiet.jpg");
				}
				ImGui::End();
				ImGui::Begin("Global");
				ImGui::InputInt("FPS Bypass", &bypass, 0, 1000);
				ImGui::Checkbox("Apply Bypass", &applybypass);
				//ImGui::SliderFloat("Speedhack", &speedhack, 0.01f, 10.00f);
				ImGui::InputFloat("Speedhack", &speedhack, 0.01f, 10.0f, "%.2f");
				if (!classicspeed) CCDirector::sharedDirector()->getScheduler()->setTimeScale(speedhack);
				ImGui::Checkbox("Speedhack only while Playing", &classicspeed);
				ImGui::InputInt("Theme", &theme, 1, 5);
				ImGui::Checkbox("Safe Mode", &safe);
				ImGui::Checkbox("No Rotation", &noRot);
				ImGui::Checkbox("No Layer Color Blending", &nodim);
				ImGui::Checkbox("Mute on Unfocus", &unfocusmute);
				//ImGui::Checkbox("Show Locked Features", &dev);
				ImGui::End();
				if (dev) {
					ImGui::Begin("Locked");
					ImGui::Text("This feature hasn't been implemented yet. Sorry!");
					ImGui::End();
				}
				//ImGui::ShowDemoWindow();
			}
		});
		cocos2d::CCLayer* touchlayer;
        if (down && key == KEY_Tab) {
			if (purchase) crystal_exists("./Crystal/");
            if (!showing && purchase) {
				loadMods();
				if (node) {
					gui = CCScene::create();
					node->setZOrder(999999);
					CCSprite* shoplifting = CCSprite::create("shoplifter.jpg");
					shoplifting->setPositionX(500);
					shoplifting->setPositionY(50);
					shoplifting->setScale(0.5);
					gui->addChild(shoplifting);
					gui->addChild(node);
					CCDirector::sharedDirector()->getRunningScene()->addChild(gui);
				}
				platform->showCursor();
				showing = true;
			} else {
				if (purchase) {
					gui->removeFromParent();
					saveMods();
				}
				gui = nullptr;
				if (PlayLayer::get()) platform->hideCursor();
				showing = false;
			}
            return true;
        };
		/*
		if (down && (key == KEY_L || key == KEY_K || key == KEY_J || key == KEY_P || key == KEY_O || key == KEY_M || key == KEY_N || key == KEY_Shift)) {
			if (GJBaseGameLayer::get() && clickready) {
				if (anykey) GJBaseGameLayer::get()->pushButton(1, true);
				clickready = false;
			}
			return true;
		}
		//(key == KEY_L || key == KEY_K || key == KEY_J || key == KEY_P || key == KEY_O || key == KEY_M || key == KEY_N || key == KEY_Shift)
		if (!down && (key == KEY_L || key == KEY_K || key == KEY_J || key == KEY_P || key == KEY_O || key == KEY_M || key == KEY_N || key == KEY_Shift)) {
			if (GJBaseGameLayer::get() && !clickready) {
				if (anykey) GJBaseGameLayer::get()->releaseButton(1, true);
				clickready = true;
			}
			return true;
		}
		*/
		//!down && ((key == customKey && mod_current == 8) ||  (key == customKey2 || mod_current2 == 8) || (key == customKey3 || mod_current3 == 8))
		if (down && ((key == customKey && mod_current == 8) ||  (key == customKey2 && mod_current2 == 8) || (key == customKey3 && mod_current3 == 8))) {
			if (GJBaseGameLayer::get() && clickready) {
				GJBaseGameLayer::get()->pushButton(1, true);
				clickready = false;
			}
			return true;
		}
		if (!down && ((key == customKey && mod_current == 8) ||  (key == customKey2 && mod_current2 == 8) || (key == customKey3 && mod_current3 == 8))) {
			if (GJBaseGameLayer::get() && !clickready) {
				GJBaseGameLayer::get()->releaseButton(1, true);
				clickready = true;
			}
			return true;
		}
		if (down && ((key == customKey && mod_current == 9) ||  (key == customKey2 && mod_current2 == 9) || (key == customKey3 && mod_current3 == 9))) {
			if (GJBaseGameLayer::get() && clickready2) {
				GJBaseGameLayer::get()->pushButton(1, false);
				clickready2 = false;
			}
			return true;
		}
		if (!down && ((key == customKey && mod_current == 9) ||  (key == customKey2 && mod_current2 == 9) || (key == customKey3 && mod_current3 == 9))) {
			if (GJBaseGameLayer::get() && !clickready2) {
				GJBaseGameLayer::get()->releaseButton(1, false);
				clickready2 = true;
			}
			return true;
		}
				/*
		CONTROLLER_A = 0x3E9,
        CONTROLLER_B = 0x3EA,
        CONTROLLER_Y = 0x3EB,
        CONTROLLER_X = 0x3EC,
        CONTROLLER_Start = 0x3ED,
        CONTROLLER_Back = 0x3EE,
        CONTROLLER_RB = 0x3EF,
        CONTROLLER_LB = 0x3F0,
        CONTROLLER_RT = 0x3F1,
        CONTROLLER_LT = 0x3F2,
        CONTROLLER_Up = 0x3F3,
        CONTROLLER_Down = 0x3F4,
        CONTROLLER_Left = 0x3F5,
        CONTROLLER_Right = 0x3F6
		*/
		if (PlayLayer::get() && down && (key == CONTROLLER_RB || key == CONTROLLER_LB || key == CONTROLLER_A || key == CONTROLLER_B || key == CONTROLLER_Y || key == CONTROLLER_X || key == CONTROLLER_Up || key == CONTROLLER_Down || key == CONTROLLER_Left || key == CONTROLLER_Right)) {
			GJBaseGameLayer::get()->pushButton(1, false);
			return true;
		}
		if (PlayLayer::get() && !down && (key == CONTROLLER_RB || key == CONTROLLER_LB || key == CONTROLLER_A || key == CONTROLLER_B || key == CONTROLLER_Y || key == CONTROLLER_X || key == CONTROLLER_Up || key == CONTROLLER_Down || key == CONTROLLER_Left || key == CONTROLLER_Right)) {
			GJBaseGameLayer::get()->releaseButton(1, false);
			return true;
		}
		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down);
	};
};

class $modify(MenuLayer) {
	bool init() {
		/*
		auto res = web::fetch("https://pastebin.com/raw/F4BzqDRG");
		if (!res) {
    		FLAlertLayer::create(
				"LMAO how",
				"If you manage to get this error, DM ninXout#3265 with proof (preferably a screenshot). This won't actually affect anything in game, the error was patched.",
				"Close"
			)->show();
			purchase = false;
		}
		*/
		std::string data = "shaurya InkZie awesomeoverkill";
		std::string user = GJAccountManager::sharedState()->m_username;
		if (data.find(user) != std::string::npos) {
    		purchase = true;
		} else {
			purchase = false;
		}
		
		MenuLayer::init();
		purchase = true;
		if (purchase) {
			auto dispatch = reinterpret_cast<MainDispatcher*>(AppDelegate::get());
			dispatch->loadMods();
		}
		return true;
	}
};

float formerY;

class $modify(CCMouseDispatcher) {
	bool dispatchScrollMSG(float x, float y) {
		if ((y > formerY) && EditorUI::get()) {
			EditorUI::get()->zoomIn(nullptr);
			formerY = y;
			return true;
		}
		return CCMouseDispatcher::dispatchScrollMSG(x,y);
	}
};

CCNode* getChildByFnRecursive(CCNode* node, std::function<bool(CCNode*)> fn) {
    if (fn(node)) return node;

    auto children = node->getChildren();
    if (!children) return nullptr;

    for (int i = 0; i < children->count(); ++i) {
        auto child = getChildByFnRecursive((cocos2d::CCNode*)children->objectAtIndex(i), fn);
        if(child)
            return child;
    }

    return nullptr;
} // layout mode :) make sure to put everything under a bool. Okay

class Patch2 : public Patch {
 public:
 	Patch2(byte_array patch, byte_array original, uintptr_t address) : Patch() {
 		m_patch = patch;
 		m_original = original;
 		m_address = (void*)address;
 		m_owner = Mod::get();
 	}

	Patch2(char patch, char original, uintptr_t address) : Patch() {
 		m_patch = {patch};
 		m_original = {original};
 		m_address = (void*)(base::get() + address);
 		m_owner = Mod::get();
 	}
};

GEODE_API void GEODE_DLL geode_load(Mod* m) {
	fps_shower_init();
		Patch2* lol = new Patch2('\xeb', '\x76', base::get() + 0x18D811);
		lol->apply();
		Patch2* lol2 = new Patch2('\xeb', '\x76', base::get() + 0x18D7D9);
		lol2->apply();


		Patch2* lol3 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x25332);
		lol3->apply();
		Patch2* lol4 = new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, base::get() + 0x2533f);
		lol4->apply();

		(new Patch2('\xeb', '\x7c', 0x18bfa))->apply();
		(new Patch2('\xeb', '\x7c', 0x18f25))->apply();
		(new Patch2('\xeb', '\x7c', 0x1b991))->apply();

		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x949cd))->apply();
		(new Patch2({'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, {'\x66', '\x0f', '\x1f', '\x44', '\x00', '\x00'}, 0x94b1d))->apply();

		(new Patch2({'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\x98', '\x00', '\x00', '\x00', '\x90'}, 0x1d67c))->apply();
		(new Patch2({'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, {'\x90', '\x90', '\x90', '\x90', '\x90', '\x90'}, 0x1d869))->apply();

		(new Patch2({'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, {'\xe9', '\xa7', '\x00', '\x00', '\x00', '\x90'}, 0x1d72d))->apply();
}

class $modify(PlayerObject) {
	void playDeathEffect() {
		PlayLayer::get()->m_level->m_normalPercent = 100;
		if (!deathEffect) {
			PlayerObject::playDeathEffect();
		}
		if (instantdeath) {
			PlayLayer::get()->resetLevel();
		}
		if (pracmusic) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
		}
	}
	void addAllParticles() {
		if (!particles) {
			PlayerObject::addAllParticles();
		}
	}
	void update(float spe) {		
		if (m_waveTrail && solidwave) {
			//m_waveTrail->setBlendFunc(getBlendFunc()); // removes the blending of it
		}
		if (invis) {
			PlayerObject::setVisible(false);
		}
		if (moon) {
			m_gravity = 20;
		}
		if (amethyst && replay && !smoothFrames && PlayLayer::get()) {
			//(*reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this) + 0x760)) = std::get<std::deque<double>>(Player1Data["Yvelo"])[frame - 1];
		}
		PlayerObject::update(spe);
	}
	void ringJump(GameObject* ring) {
		bool a;
		bool b;
		a = ring->m_hasBeenActivated;
    	b = ring->m_hasBeenActivatedP2;
		PlayerObject::ringJump(ring);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode && practiceOrb) {
        	if (ring->m_hasBeenActivated && !a) g_activated_objects.push_back(ring);
        	if (ring->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(ring);
    	}
	}
	void saveToCheckpoint(PlayerCheckpoint* g) {
		PlayerObject::saveToCheckpoint(g);
		if (cpswitch) {
			g->retain();
		//g_startPoses.push_back({reinterpret_cast<CheckpointObject*>(g), g->getPosition()});
		g_checkpointsPos.push_back(g->getPosition());
        g_checkpointsIG.push_back(g);
		g_checkpointIndex += 1;
		auto label = std::to_string(g_checkpointIndex + 1) + "/" + std::to_string(g_checkpointsIG.size());
		g_checkpointText->setString(label.c_str());
		}
	}
};

class $(LevelInfoLayer) {
	static LevelInfoLayer* create(GJGameLevel* g) {
		if (freecopy) {
			//g->m_passwordSeed = 20; // it can be anything
			//g->m_passwordRand = g->m_passwordSeed + 1;
		}

		if (ldm) {
			g->m_lowDetailModeToggled = true;
		}
		
		//getNONGs();
		//findsong = std::to_string(level->m_songID);

		return LevelInfoLayer::create(g);
	}
};

class $modify(GameManager) {
		bool isIconUnlocked(int a, IconType b) {
			auto icon = GameManager::isIconUnlocked(a,b);
			if (unlockall) {
				return true;
			} else {
				return icon;
			}
		} 
		bool isColorUnlocked(int a, bool b) {
			auto color = GameManager::isColorUnlocked(a,b);
			if (unlockall) {
				return true;
			} else {
				return color;
			}
		}
};

class $modify(GJGameLevel) {
	void savePercentage(int i, bool b, int i2, int i3, bool b2) {
		if (!safe) {
			GJGameLevel::savePercentage(i, b, i2, i3, true);
		}
		if (uncomplete) {
			GJGameLevel::savePercentage(0, false, 0, 0, true);
		}
	}
};

class $modify(CCLayerColor) {
	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::create(yk);
		}
	}

	static cocos2d::CCLayerColor* create(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::create(ccc4(255,255,255,0), f1, f2);
		} else {
			return CCLayerColor::create(yk, f1, f2);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0));
		} else {
			return CCLayerColor::initWithColor(yk);
		}
	}

	bool initWithColor(cocos2d::_ccColor4B const& yk, float f1, float f2) {
		if (nodim) {
			return CCLayerColor::initWithColor(ccc4(255,255,255,0), 0, 0);
		} else {
			return CCLayerColor::initWithColor(yk, f1, f2);
		}
	}
};

class $modify(EditLevelLayer) {
	static EditLevelLayer* create(GJGameLevel* ok) {
		if (verify) {
			//ok->m_isVerifiedRand = 11;
			//ok->m_isVerifiedSeed = 10;
		}	
		if (ldm) {
			ok->m_lowDetailModeToggled = true;
		} 
		return EditLevelLayer::create(ok);
	}
};


class $modify(PlayerObject) {
	void playerDestroyed(bool idk) {
		PlayerObject::playerDestroyed(idk);
		s_drawOnDeath = true;
	}
	
	virtual void setRotation(float love) {
		if (noRot) {
			love = 0.0;
		}

		return PlayerObject::setRotation(love);
	}
};



class $modify(PlayLayer) {
	static inline HitboxNode* drawer;

	bool init(GJGameLevel* lvl) {
		drawer = HitboxNode::create();
		auto ret = PlayLayer::init(lvl);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		s_showOnDeath = onDeath;
		drawer->m_drawTrail = drawTrail;
		s_onlyHitboxes = onlyHitbox;
		if (s_showOnDeath) s_drawOnDeath = false;
		drawer->drawCircleHitbox(ccp(PlayLayer::get()->m_player1->getPositionX() + 30, PlayLayer::get()->m_player1->getPositionY()), 25, ccc4(255, 255, 255, 255));

		return ret;
	}
	void checkCollisions(PlayerObject* player, float uhh) {
		PlayLayer::checkCollisions(player, uhh);
		if (player == m_player1) {
			drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
	}
	void resetLevel() {
		if (s_showOnDeath) s_drawOnDeath = false;
        drawer->clearQueue();
        PlayLayer::resetLevel();
    }

	void update(float dt) {
		drawer->clear();
		//drawer->addToPlayer1Queue(m_player1->getObjectRect());
		if (!freeze) {
			PlayLayer::update(dt);
		}
		if (autoKill) {
			m_isDead = true;
			PlayLayer::resetLevel();
			autoKill = false; // so it doesnt loop
		}
		if (s_showOnDeath) {
			if (!turnonHitbox) return;
			if (!s_drawOnDeath) return;
			drawer->setVisible(true);
		}		

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				drawer->drawForObject(obj);
			}
		}
	}
};

static inline HitboxNode* drawer;

class $modify(HitboxLevelEditorLayer, LevelEditorLayer) {
	static inline bool paused = false;

	bool init(GJGameLevel* lvl) {
		drawer = HitboxNode::create();
		auto ret = LevelEditorLayer::init(lvl);
		drawer->setVisible(false);
		m_objectLayer->addChild(drawer, 32);

		s_drawer = drawer;

		// i hate bad practices
		drawer->m_drawTrail = drawTrail;
		s_noLimitTrail = noLimitTrail;
		return ret;
	}
	bool checkCollisions(PlayerObject* player, float uhh) {
		auto ret = LevelEditorLayer::checkCollisions(player, uhh);
		if (player == m_player1) {
			drawer->addToPlayer1Queue(m_player1->getObjectRect());
		}
		if (player == m_player2) {
			drawer->addToPlayer2Queue(m_player2->getObjectRect());
		}
		return ret;
	}
	void onPlaytest() {
		LevelEditorLayer::onPlaytest();
		if (editorHitbox) {
			drawer->setVisible(true);
		}
	}
	void onPausePlaytest() {
		LevelEditorLayer::onPausePlaytest();
		paused = true;
		this->updateHitboxEditor();
	}
	void updateHitboxEditor() {
		if (!paused) return;
		if (s_noLimitTrail) drawer->m_noLimitTrail = true;

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		if (m_player1) {
			float xp = m_player1->getPositionX();

			for (int s = sectionForPos(xp) - 10; s < sectionForPos(xp) + 10; ++s) {
				if (s < 0) continue;
				if (s >= m_sectionObjects->count()) break;
				auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
				for (size_t i = 0; i < this->getAllObjects()->count(); ++i) {
					auto obj = static_cast<GameObject*>(this->getAllObjects()->objectAtIndex(i));

					if (s_onlyHitboxes) obj->setOpacity(0);

					if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
					if (!obj->m_active) continue;

					drawer->drawForObject(obj);
				}
			}
		}
	}
	void onResumePlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
		LevelEditorLayer::onResumePlaytest();
	}
	void onStopPlaytest() {
		if (s_noLimitTrail) drawer->m_noLimitTrail = false;
		paused = false;
        drawer->clearQueue();
        if (editorHitbox) {
			drawer->setVisible(true);
		}
        LevelEditorLayer::onStopPlaytest();
    }

	void update(float dt) {
		drawer->clear();
		LevelEditorLayer::update(dt);

		if (m_player1) {
			drawer->drawForPlayer1(m_player1);
		}
		if (m_player2) {
			drawer->drawForPlayer2(m_player2);
		}

		float xp = m_player1->getPositionX();

		for (int s = sectionForPos(xp) - 5; s < sectionForPos(xp) + 6; ++s) {
			if (s < 0) continue;
			if (s >= m_sectionObjects->count()) break;
			auto section = static_cast<CCArray*>(m_sectionObjects->objectAtIndex(s));
			for (size_t i = 0; i < section->count(); ++i) {
				auto obj = static_cast<GameObject*>(section->objectAtIndex(i));

				if (s_onlyHitboxes) obj->setOpacity(0);

				if (obj->m_objectID != 749 && obj->getType() == GameObjectType::Decoration) continue;
				if (!obj->m_active) continue;

				drawer->drawForObject(obj);
			}
		}
	}
};

//are you done implementing layout mode. Nope lol alr
//apparently i can spectate you (see you scrolling) yea ik

class $(MyGameObject, GameObject) {
	CCSprite* m_backgroundLayer;
	bool m_realVisible;
	cocos2d::_ccColor3B m_realColor;

	void setVisible(bool v) {
		if (layout) {
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

		if (layout && m_objectType != GameObjectType::Decoration) {
			CCSpritePlus::setOpacity(255);
			if (m_glowSprite)
				m_glowSprite->setOpacity(255);
		}
	}

	void setGlowColor(cocos2d::_ccColor3B const& col) {
		if (layout) {
			GameObject::setGlowColor(ccc3(255, 255, 255));
		} else {
			GameObject::setGlowColor(col);
		}
	}

	void setObjectColor(const cocos2d::ccColor3B& cor) {
		if (layout && m_objectType != GameObjectType::Decoration) {
			GameObject::setObjectColor(ccc3(255, 255, 255));
		} else {
			GameObject::setObjectColor(cor);
		}
	}
};

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
};

class FPSOverlay : public cocos2d::CCNode {
 protected:
    static inline FPSOverlay* s_sharedState = 0;

    cocos2d::CCLabelBMFont* m_label;
    cocos2d::extension::CCScale9Sprite* m_backdrop;
    int m_frames;
    double m_accumulate;
    double m_resetInterval;

 public:
    static FPSOverlay* sharedState() {
        if (!FPSOverlay::s_sharedState) {
            auto ret = FPSOverlay::s_sharedState = new FPSOverlay();
            ret->init();
        }
        return FPSOverlay::s_sharedState;
    }

 private:
    cocos2d::CCSize getBackdropSize() {
        auto textSize = m_label->getContentSize();
        return cocos2d::CCSizeMake(2 * 6 + textSize.width * 2, 2 * 6 + textSize.height * 2);
    }

 public:
    bool init() {
        m_frames = 0;
        m_resetInterval = 1.0;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
		auto corner = CCDirector::sharedDirector()->getScreenTop();
        
        m_label = cocos2d::CCLabelBMFont::create("No FPS", "bigFont.fnt");
        m_label->setPosition(5 , corner - 305);
		m_label->setScale(0.4);
		m_label->setAnchorPoint({0, 0.5});
		m_label->setOpacity(100);
        addChild(m_label, 2);        

        m_backdrop = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
        m_backdrop->setContentSize(getBackdropSize());
        m_backdrop->setPosition({2, winSize.height - 2});
        m_backdrop->setAnchorPoint(cocos2d::CCPoint(0, 1));
        m_backdrop->setOpacity(0);
        m_backdrop->setScale(0.166666);
        addChild(m_backdrop, 1);

        return true;
    }

    void update(float dt) {
    	updateLabel(dt);
    }

    void updateLabel(float dt) {
		const auto now = std::chrono::high_resolution_clock::now();

		const std::chrono::duration<float> diff = now - previous_frame;
		frame_time_sum += diff.count();
		frame_count++;

		if (std::chrono::duration<float>(now - last_update).count() > 1.0f) {
			last_update = now;
			const auto fps = static_cast<int>(std::roundf(static_cast<float>(frame_count) / frame_time_sum));
			frame_time_sum = 0.f;
			frame_count = 0;
			m_label->setString((std::to_string(fps) + " FPS").c_str());
            m_backdrop->setContentSize(getBackdropSize());
		}

		previous_frame = now;
/*
    	++m_frames;
        m_accumulate += dt;

        if (m_accumulate > m_resetInterval) {
            float framerate = m_frames / m_accumulate;
            framerate = round(framerate * 10) / 10;
            m_frames = 0;
            m_accumulate = 0;
            
            std::stringstream stream;
        	stream << framerate << " FPS";
            m_label->setString(stream.str().c_str());
            m_backdrop->setContentSize(getBackdropSize());
        }
		*/
    }
};

class $modify(GameObject) {
	virtual void update(float time2) {
		if (noglow) {
			bool m_isGlowDisabled = true;
		}
		if (particles) {
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


class $modify(AchievementNotifier) {
    void willSwitchToScene(cocos2d::CCScene* newScene) {
		if (showing) {
			showing = false;
			gui->removeFromParent();
		}

        AchievementNotifier::willSwitchToScene(newScene);
        
		/*
        if (FPSOverlay::sharedState()->getParent() != newScene) {
            FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(newScene->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
        }
		*/
    }
};

void fps_shower_init() {
	geode::Loader::get()->queueInGDThread([](){
		cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(FPSOverlay::sharedState(), 0, true);
		auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
		if (scene) {
			auto layer = reinterpret_cast<cocos2d::CCNode*>(scene->getChildren()->objectAtIndex(0));
			if (layer) layer->addChild(FPSOverlay::sharedState(), 100001);
			FPSOverlay::sharedState()->setVisible(false);
		}
	});
}

class $modify(CCScheduler) {
	void update(float f3) {
		if (applybypass) {
			cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.0 / bypass);
		}
		//if (!classicspeed) CCScheduler::update(f3 * speedhack);
		CCScheduler::update(f3);
		if (shouldQuit && PlayLayer::get()) {
			PlayLayer::get()->PlayLayer::onQuit();
			shouldQuit = false;
		}
	}
};

class $modify(zoomHack, EditorUI) {
	void zoomIn(cocos2d::CCObject* sender) {
		if (zoomhack) {
			zoom = zoom + 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomIn(sender);
		}
	}

	void zoomOut(cocos2d::CCObject* sender) {
		if (zoomhack) {
			zoom = zoom - 0.1;
			EditorUI::updateZoom(zoom);
		} else {
			EditorUI::zoomOut(sender);
		}
	}
};

class $modify(GJBaseGameLayer) {
	void pushButton(int i, bool b) {
		pushing = true;
		if (b) mouse1Down = true;
	    if (!b) mouse2Down = true;
		if (amethyst && recording) push.push_back(PlayLayer::get()->m_player1->getPositionX());
		//if (amethyst && recording) pushpos.push_back(PlayLayer::get()->m_player1->getPositionY());
		if (dualcontrol) {
			if (!b) GJBaseGameLayer::pushButton(i,true);
			if (b) GJBaseGameLayer::pushButton(i,false);
		} else if (inputmirror) {
			GJBaseGameLayer::pushButton(i,true);
			GJBaseGameLayer::pushButton(i,false);
		} else {
			GJBaseGameLayer::pushButton(i,b);
		}
		clickscount++;
	}

	void releaseButton(int i, bool b) {
		pushing = false;
		if (b) mouse1Down = false;
	    if (!b) mouse2Down = false;
		if (amethyst && recording) rel.push_back(PlayLayer::get()->m_player1->getPositionX());
		if (amethyst && recording) relpos.push_back(PlayLayer::get()->m_player1->getPositionY());
        if (dualcontrol) {
			if (!b) GJBaseGameLayer::releaseButton(i,true);
			if (b) GJBaseGameLayer::releaseButton(i,false);
		} else if (inputmirror) {
			GJBaseGameLayer::releaseButton(i,true);
			GJBaseGameLayer::releaseButton(i,false);
		} else {
			GJBaseGameLayer::releaseButton(i,b);
		}
	}

	void bumpPlayer(PlayerObject* player, GameObject* object) {
		bool a = object->m_hasBeenActivated;
    	bool b = object->m_hasBeenActivatedP2;
		GJBaseGameLayer::bumpPlayer(player, object);
		if (PlayLayer::get() && PlayLayer::get()->m_isPracticeMode) {
        	if (object->m_hasBeenActivated && !a) g_activated_objects.push_back(object);
        	if (object->m_hasBeenActivatedP2 && !b) g_activated_objects_p2.push_back(object);
    	}
	}
};

void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
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

float g = 0;
// wacky way to convert pure hue to rgb
cocos2d::_ccColor3B getRainbow(float offset) {
	float R;
	float G;
	float B;

	float hue = fmod(g + offset, 360);
	//geode::log << hue;
	float sat = 1;
	float vc = 1;
	HSVtoRGB(R, G, B, hue, sat, vc);

	cocos2d::_ccColor3B out;
	out.r = R*255;
	out.g = G*255;
	out.b = B*255;
	return out;
}

class $modify(Main, PlayLayer) {
	void updateIndex(bool increment) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (m_isTestMode) {
			g_startPosText->setOpacity(255);
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
		}

		if (increment) {
			g_startPosIndex++;
			if (m_isPracticeMode) g_checkpointIndex++;
		} else {
			g_startPosIndex--;
			if (m_isPracticeMode) g_checkpointIndex--;
		}

		if (g_startPosIndex == g_startPoses.size()) {
			g_startPosIndex = -1;
		} else if (g_startPosIndex < -1) {
			g_startPosIndex = g_startPoses.size() - 1;
		}



		auto colorPulseBegin = CCTintTo::create(0.0, 0, 255, 0);
		auto colorPulseEnd = CCTintTo::create(0.5, 255, 255, 255);

		auto opacityPulseBegin = CCFadeTo::create(0.0, 255);
		auto opacityPulseEnd = CCFadeTo::create(0.5, 50);

		if (m_isTestMode) {
			auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
			g_startPosText->setString(label.c_str());
			g_startPosText->runAction(CCSequence::create(colorPulseBegin, colorPulseEnd, nullptr));
			g_startPosText->runAction(CCSequence::create(opacityPulseBegin, opacityPulseEnd, nullptr));
		}

		if (m_isTestMode) {
			m_startPosCheckpoint = nullptr;
			if (g_startPosIndex == -1) {
				m_startPos = nullptr;
				m_playerStartPosition = ccp(0, 105);
			} else {
				m_startPos = g_startPoses[g_startPosIndex].first;
				m_playerStartPosition = g_startPoses[g_startPosIndex].second;
			}
		}

		resetLevel();
		if (m_isPracticeMode) {
			GameSoundManager::sharedManager()->stopBackgroundMusic();
			load = true;
		}
		if (m_isTestMode) g_startPosText->setOpacity(50);
		if (m_isPaused)
			GameSoundManager::sharedManager()->stopBackgroundMusic();
	}

	void addObject(GameObject* g) {
		if (noglow) g->m_isGlowDisabled = true;
		if (forcefade) g->m_isDontFade = true;
		if (forceenter) g->m_isDontEnter = true;
		PlayLayer::addObject(g);
		if (startpos) {
			if (g->m_objectID == 31) {
				g->retain();
				g_startPoses.push_back({reinterpret_cast<StartPosObject*>(g), g->getPosition()});
				g_startPosIndex += 1;
				auto label = std::to_string(g_startPosIndex + 1) + "/" + std::to_string(g_startPoses.size());
				g_startPosText->setString(label.c_str());
			}
		}
	}	

	void resetLevel() {
		auto gj = reinterpret_cast<PlayerObject*>(PlayLayer::get());
		notDone = true;
		posIterate = 1;
		if (cpswitch && m_isPracticeMode) load = true;
		if (noclipDeaths) {
			noclip_deaths = deathwait = 0;
		}
		if (respawn) {
			if (m_isTestMode || m_isPracticeMode) {
				smoothOut = 2;
			}
		}
		if (bestRun) {
			bestEnd2 = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		pushIterate = releaseIterate = 0;
		PlayLayer::resetLevel();
	if (!m_isPracticeMode) {
		frame = 0;
		maxFrame = 0;
	}
	else {
		//if (std::get<std::deque<int>>(Player1Data["Checkpoints"]).size() == 0) { std::get<std::deque<int>>(Player1Data["Checkpoints"]).insert(std::get<std::deque<int>>(Player1Data["Checkpoints"]).begin(), 0); }
/*
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player1Data["Xpos"]).size())) { if (std::get<std::deque<float>>(Player1Data["Xpos"]).size() != 0) { std::get<std::deque<float>>(Player1Data["Xpos"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player1Data["Ypos"]).size())) { if (std::get<std::deque<float>>(Player1Data["Ypos"]).size() != 0) { std::get<std::deque<float>>(Player1Data["Ypos"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player1Data["Rotation"]).size())) { if (std::get<std::deque<float>>(Player1Data["Rotation"]).size() != 0) { std::get<std::deque<float>>(Player1Data["Rotation"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<bool>>(Player1Data["Pushed"]).size())) { if (std::get<std::deque<bool>>(Player1Data["Pushed"]).size() != 0) { std::get<std::deque<bool>>(Player1Data["Pushed"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<double>>(Player1Data["Yvelo"]).size())) { if (std::get<std::deque<double>>(Player1Data["Yvelo"]).size() != 0) { std::get<std::deque<double>>(Player1Data["Yvelo"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<bool>>(Player1Data["Dropping"]).size())) { if (std::get<std::deque<bool>>(Player1Data["Dropping"]).size() != 0) { std::get<std::deque<bool>>(Player1Data["Dropping"]).pop_back(); } else { break; } };

		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player2Data["Xpos"]).size())) { if (std::get<std::deque<float>>(Player2Data["Xpos"]).size() != 0) { std::get<std::deque<float>>(Player2Data["Xpos"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player2Data["Ypos"]).size())) { if (std::get<std::deque<float>>(Player2Data["Ypos"]).size() != 0) { std::get<std::deque<float>>(Player2Data["Ypos"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<float>>(Player2Data["Rotation"]).size())) { if (std::get<std::deque<float>>(Player2Data["Rotation"]).size() != 0) { std::get<std::deque<float>>(Player2Data["Rotation"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<bool>>(Player2Data["Pushed"]).size())) { if (std::get<std::deque<bool>>(Player2Data["Pushed"]).size() != 0) { std::get<std::deque<bool>>(Player2Data["Pushed"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<double>>(Player2Data["Yvelo"]).size())) { if (std::get<std::deque<double>>(Player2Data["Yvelo"]).size() != 0) { std::get<std::deque<double>>(Player2Data["Yvelo"]).pop_back(); } else { break; } };
		while ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() < (int)(std::get<std::deque<bool>>(Player1Data["Dropping"]).size())) { if (std::get<std::deque<bool>>(Player1Data["Dropping"]).size() != 0) { std::get<std::deque<bool>>(Player1Data["Dropping"]).pop_back(); } else { break; } };

		while (std::get<std::deque<float>>(Player1Data["Xpos"]).back() > GJBaseGameLayer::get()->m_player1->getPositionX()) {
			frame--;
				std::get<std::deque<bool>>(Player1Data["Pushed"]).pop_back();
				std::get<std::deque<float>>(Player1Data["Rotation"]).pop_back();
				std::get<std::deque<float>>(Player1Data["Ypos"]).pop_back();
				std::get<std::deque<float>>(Player1Data["Xpos"]).pop_back();
		}
		
		if ((int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back() != 0) { frame = (int)std::get<std::deque<int>>(Player1Data["Checkpoints"]).back(); }
		else {
			frame = 0;
			maxFrame = 0;
		}
*/
	}
		if (m_checkpoints->count() == 0) {
        	g_activated_objects.clear();
        	g_activated_objects_p2.clear();
        	g_orbCheckpoints.clear();
    	} else {
			if (practiceOrb && m_isPracticeMode) {
				const auto [p1, p2] = g_orbCheckpoints.back();
        		g_activated_objects.erase(
            		g_activated_objects.begin() + p1,
            		g_activated_objects.end()
        		);
        		g_activated_objects_p2.erase(
            		g_activated_objects_p2.begin() + p2,
            		g_activated_objects_p2.end()
        		);
        		for (const auto& object : g_activated_objects) {
            		object->m_hasBeenActivated = true;
        		}
        		for (const auto& object : g_activated_objects_p2) {
            		object->m_hasBeenActivatedP2 = true;
        		}
			}
    	}
		if (cheater) {
			bad = "Not Cheating";
			g_cheating->setColor(ccc3(0,255,0));
		}
		if (recording && amethyst && m_isPracticeMode && smoothFrames) {
            while (push.back() >= m_player1->getPositionX() && push.size() > 0 && m_isPracticeMode) {
				push.pop_back();
			}

			while (rel.back() >= m_player1->getPositionX() && rel.size() > 0 && m_isPracticeMode) {
				rel.pop_back();
			}
        }
		if (clickreset) clickscount = 0;
		finished = false;
		if (currentRun) {
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from %.0lf%%", start);
			g_run->setString(str);
		}
		if (bestRun) {
			bestStart2 = (m_player1->getPositionX() / m_levelLength) * 100;
			if ((bestEnd2 - bestStart2) > (bestEnd - bestStart)) {
				bestStart = bestStart2;
				bestEnd = bestEnd2;
			}
			display = "Best Run: " + std::to_string(bestStart) + " to " + std::to_string(bestEnd);
			g_bestRun->setString(display.c_str());
		}
		if (accuracy) {
			frames = noclipped_frames = 0;
		}
	}

	void destroyPlayer(PlayerObject* p, GameObject* g) {
		if (g == m_antiCheatObject) {
			return PlayLayer::destroyPlayer(p,g);
		}
		if (frames>20 && accuracy) {
			noclipped_frames++;
			if ((100*(1.0 - (noclipped_frames/(m_time * 500)))) <= killaccuracy) {
				if (!resetaccuracy) {
					PlayLayer::destroyPlayer(p, g);
				} else {
					resetLevel();
				}
				char str[20];
				sprintf(str, "%.2f%%", killaccuracy);
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(str);
			}
		}
		if (frames>20 && noclipDeaths) {
			deathwait++;
			if (deathwait >= 25) {
				noclip_deaths++;
				deathwait = 0;
			} 
		}
		if (anticheat) {
			bool m_antiCheatPassed = true;
			bool m_shouldTryToKick = false;
			bool m_hasCheated = false;
		}
		if (nospike) {
			if (g->m_objectID != 8 || g->m_objectID != 39 || g->m_objectID != 103) {
				PlayLayer::destroyPlayer(p,g);
			}
		}
		if (moon) {
			p->m_yAccel = 100;
		}
		if (!noclip) {
			if (noclipP1) {
				if (p == m_player2) PlayLayer::destroyPlayer(p,g);
			} else if (noclipP2) {
				if (p == m_player1) PlayLayer::destroyPlayer(p,g);
			} else if (!noclipP1 && !noclipP2) {
				PlayLayer::destroyPlayer(p,g);
			}
		}
	}

	void fullReset() {
		if (lastCheckpoint && m_isPracticeMode) {
			loadLastCheckpoint();
			resetLevel();
		} else {
			PlayLayer::fullReset();
		}
	}

//GJBaseGameLayer::get()->m_player1->

	void checkCollisions(PlayerObject* p, float g) {
			frames++;

		if (anticheat) {
			m_antiCheatPassed = true;
			m_shouldTryToKick = false;
			m_hasCheated = false;
		}

		if (complete) GJBaseGameLayer::get()->m_player1->setPositionY(1050);
		if (complete) GJBaseGameLayer::get()->m_player1->setPositionX(m_levelLength - 200);

			auto p1 = GJBaseGameLayer::get()->m_player1;
		auto p2 = GJBaseGameLayer::get()->m_player2;

		if (p1->getPositionX() == 0) { 
				frame = 0;
			}
			else { 
				frame += (1 / macroSpeed);
			}

		if (frame > maxFrame) { maxFrame = frame; }

		if ((amethyst && replay && !smoothFrames)) {
			if (std::get<std::deque<float>>(Player1Data["Xpos"]).back() < p1->getPositionX()) {
				frame -= 4;
				//p->setPositionX(std::get<std::deque<float>>(Player1Data["Xpos"]).back());
			}
			if (frame != 0) {
					p1->setPositionX(std::get<std::deque<float>>(Player1Data["Xpos"])[(frame - 1)]);
					p1->setPositionY(std::get<std::deque<float>>(Player1Data["Ypos"])[(frame - 1)]);
					p1->setRotation(std::get<std::deque<float>>(Player1Data["Rotation"])[(frame - 1)]);
					if (std::get<std::deque<bool>>(Player1Data["Pushed"])[(frame)] && !mouse1Down) { 
						GJBaseGameLayer::get()->pushButton(1, true); 
						if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3.ogg", 1, 1, 1);
						mouse1Down = true;
					}
					if (!std::get<std::deque<bool>>(Player1Data["Pushed"])[(frame)] && mouse1Down) { 
						GJBaseGameLayer::get()->releaseButton(1, true); 
						if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3rel.ogg", 1, 1, 1);
						mouse1Down = false; 
					}
					p2->setPositionX(std::get<std::deque<float>>(Player2Data["Xpos"])[(frame - 1)]);
					p2->setPositionY(std::get<std::deque<float>>(Player2Data["Ypos"])[(frame - 1)]);
					p2->setRotation(std::get<std::deque<float>>(Player2Data["Rotation"])[(frame - 1)]);
					if (std::get<std::deque<bool>>(Player2Data["Pushed"])[(frame)] && !mouse2Down) { 
						GJBaseGameLayer::get()->pushButton(1, false); 
						//if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3.ogg", 1, 1, 1);
						mouse2Down = true;
					}
					if (!std::get<std::deque<bool>>(Player2Data["Pushed"])[(frame)] && mouse2Down) { 
						GJBaseGameLayer::get()->releaseButton(1, false); 
						//if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3rel.ogg", 1, 1, 1);
						mouse2Down = false; 
					}
			}
		}
		//double yAcc = (*reinterpret_cast<double*>(reinterpret_cast<uintptr_t>(this) + 0x760));
		if (amethyst && recording && !smoothFrames) {
			if (frame > 0) {
					macroSpeed = CCDirector::sharedDirector()->getScheduler()->getTimeScale();
					std::get<std::deque<float>>(Player1Data["Xpos"]).insert(std::get<std::deque<float>>(Player1Data["Xpos"]).end(), p1->getPositionX());
					std::get<std::deque<float>>(Player1Data["Ypos"]).insert(std::get<std::deque<float>>(Player1Data["Ypos"]).end(), p1->getPositionY());
					std::get<std::deque<float>>(Player1Data["Rotation"]).insert(std::get<std::deque<float>>(Player1Data["Rotation"]).end(), p1->getRotation());
					std::get<std::deque<bool>>(Player1Data["Pushed"]).insert(std::get<std::deque<bool>>(Player1Data["Pushed"]).end(), mouse1Down);
					//std::get<std::deque<double>>(Player1Data["Yvelo"]).insert(std::get<std::deque<double>>(Player1Data["Yvelo"]).end(), yAcc);
					std::get<std::deque<float>>(Player2Data["Xpos"]).insert(std::get<std::deque<float>>(Player2Data["Xpos"]).end(), p2->getPositionX());
					std::get<std::deque<float>>(Player2Data["Ypos"]).insert(std::get<std::deque<float>>(Player2Data["Ypos"]).end(), p2->getPositionY());
					std::get<std::deque<float>>(Player2Data["Rotation"]).insert(std::get<std::deque<float>>(Player2Data["Rotation"]).end(), p2->getRotation());
					std::get<std::deque<bool>>(Player2Data["Pushed"]).insert(std::get<std::deque<bool>>(Player2Data["Pushed"]).end(), mouse2Down);
			}
		}

			if (autoclick) {
				clickframe++;
				if (clickframe == clickPush) {
					GJBaseGameLayer::get()->pushButton(1, true);
				}
				if (clickframe >= (clickPush + clickRel)) {
					GJBaseGameLayer::get()->releaseButton(1, true);
					clickframe = 0;
				}
			}

			PlayLayer::checkCollisions(p, g);

			if (accuracy && !finished) {
				char ok[20];
				sprintf(ok, "%.2f%%", 100*(1.0 - (noclipped_frames/(m_time * 500))));
				reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
			}
	}

	void levelComplete() {
		finished = true;
		PlayLayer::levelComplete();
	}

	void updateProgressbar() {
		PlayLayer::updateProgressbar();	
		int resetPercentage = (m_player1->getPositionX() / m_levelLength) * 100;
		if ((resetPercentage == autoresetnum) && autoreset) {
			resetLevel();
		}
		if (accpercentage) {
			double percent = (m_player1->getPositionX() / m_levelLength) * 100;
			if (percent > 100.00) {
				percent = 100.00;
			}
			char str[64];
			sprintf(str, "%.2lf%%", percent);
			this->m_percentLabel->setString(str);
		}
	}

	void update(float f4) {
		if (g >= 360) // mod 360
			g = 0;
		else
			g += rainbowspeed; // a good rotation
		col = getRainbow(0);
		colInverse = getRainbow(180);

		if (m_player1) {
			if (rainP1) m_player1->setColor(col);
			if (rainP2) m_player1->setSecondColor(colInverse);
			if (notrail) m_player1->m_waveTrail->setVisible(false);
			//if (m_player1->m_waveTrail)
				//if (rainP1wave) m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			if (rainP2) m_player2->setColor(colInverse);
			if (rainP1) m_player2->setSecondColor(col);
			//if (m_player2->m_waveTrail)
				//if (rainP2wave) m_player2->m_waveTrail->setColor(colInverse);
		}


		if (accuracy) {
			percent = (m_player1->getPositionX() / m_levelLength) * 100;
		}
		if (customMessage) {
			g_message->setString(message);
		}
		if (cheater) {
			if (noclip || speedhack<1 || nospike || mirror || framestep || autoclick || layout || complete || moon) {
				bad = "Cheating";
				g_cheating->setColor(ccc3(155,0,0));
			}

			g_cheating->setString(bad.c_str());

		}
		if (pausecountdown) {
			if (freezeCount) {
				GameSoundManager::sharedManager()->stopBackgroundMusic();
				countdown++;
				if (countdown <= 60) {
					g_pauseCount->setString("3");
				} else if (countdown <= 120 && countdown > 60) {
					g_pauseCount->setString("2");
				} else if (countdown <= 180 && countdown > 120) {
					g_pauseCount->setString("1");
				} else if (countdown <= 240 && countdown > 180) {
					freezeCount = false;
					startMusic();
					g_pauseCount->setOpacity(0);
					countdown = 0;
				}
			}
		}
		if (noclipDeaths) {
			std::string nd = "Noclip Deaths: " + std::to_string(noclip_deaths);
			font->setString(nd.c_str());
		}
		if (jumps) {
			std::string nd = "Total Jumps: " + std::to_string(m_level->m_jumps);
			g_jumps->setString(nd.c_str());
		}
		if (samedual) {
			m_player2->setSecondColor(secondary);
			m_player2->setColor(primary);
			m_player2->m_waveTrail->setColor(primary);
		}
		if (clicks) {
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
		}
		m_percentLabel->setPositionX(percentXpos);
		m_percentLabel->setPositionY(percentYpos);
		m_percentLabel->setScale(percentScale);
		m_percentLabel->setOpacity(percentOpac);
		if (progressBar) {
			m_sliderGrooveSprite->setVisible(false);
		} else {
			m_sliderGrooveSprite->setVisible(true);
			m_percentLabel->setPositionX(m_percentLabel->getPositionX());
		}
		if (hideatts) {
			m_attemptLabel->setVisible(false);
		}
		if (hidepracatts) {
			if (m_isPracticeMode) m_attemptLabel->setVisible(false);
		}
		if (attempts) {
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);
		}
		if (totalAtts) {
			std::string at = "Global Atts: " + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
		}
		if (lastDeath) {
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death: %.0lf%%", start);
			g_death->setString(str);
		}
		if (replay && smoothFrames && amethyst) {
			frames = m_player1->getPositionX();
			auto mpl = reinterpret_cast<GJBaseGameLayer*>(GJBaseGameLayer::get());
			if (std::find(push.begin(), push.end(), m_player1->getPositionX()) != push.end()) {
				mpl->GJBaseGameLayer::pushButton(1, true);
				if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3.ogg", 1, 1, 1);
			}
			if (std::find(rel.begin(), rel.end(), m_player1->getPositionX()) != rel.end()) {
				mpl->GJBaseGameLayer::releaseButton(1, true);
				if (!m_isDead && clickBot) GameSoundManager::sharedManager()->playEffect("Crystal/Amethyst/ClickBot/3rel.ogg", 1, 1, 1);
			}
			PlayLayer::update(1.0/60.0);
		}
		if (respawn) {
			if (!smoothOut) {
				return update(f4);
			}

			float time = cocos2d::CCDirector::sharedDirector()->getAnimationInterval();
			if (smoothOut != 0 && f4 - time < 1) {
				smoothOut --;
			}

			PlayLayer::update(time);
		} else {
			if (framestep) {
				if (stepready) {
					PlayLayer::update(f4);
				}
			} else {
				if (classicspeed) {
					PlayLayer::update(f4 * speedhack);
				} else {
					if (!freezeCount) PlayLayer::update(f4);
				}
			}
		}
	}

	void markCheckpoint() {
		if (practiceOrb) g_orbCheckpoints.push_back({g_activated_objects.size(), g_activated_objects_p2.size()});
		PlayLayer::markCheckpoint();
		std::get<std::deque<int>>(Player1Data["Checkpoints"]).insert(std::get<std::deque<int>>(Player1Data["Checkpoints"]).end(), frame);
	}

	void removeLastCheckpoint() {
		if (practiceOrb) g_orbCheckpoints.pop_back();
		PlayLayer::removeLastCheckpoint();
		if (std::get<std::deque<int>>(Player1Data["Checkpoints"]).size() > 0) std::get<std::deque<int>>(Player1Data["Checkpoints"]).pop_back();
	}

	void startMusic() {
		if (pracmusic) {
			auto p = m_isPracticeMode;
			m_isPracticeMode = false; // pretend there is no practice mode
			PlayLayer::startMusic();
			m_isPracticeMode = p;
		} else {
			PlayLayer::startMusic();
		}
	}

	void onQuit() {
		FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
		if (!shouldQuit && confirmQuit && !m_hasLevelCompleteMenu && !CCDirector::sharedDirector()->getKeyboardDispatcher()->getShiftKeyPressed()) {
			geode::createQuickPopup(
    "Confirm Quit",            // title
    "Are you sure you would like to Quit?",   // content
    "Cancel", "Quit",      // buttons
    [](auto, bool btn2) {
        if (btn2) {
            shouldQuit = true;
        }
    }
);
		} else {
			PlayLayer::onQuit();
		}
	}

	void togglePracticeMode(bool p) {
		if (pracmusic) {
			if (!m_isPracticeMode && p) {
				// receate function without the music restart
				m_isPracticeMode = p;
				m_UILayer->toggleCheckpointsMenu(p);
				PlayLayer::startMusic();
				this->stopActionByTag(18);
				//if (p) stopActionByTag(0x12);
			} else {
				PlayLayer::togglePracticeMode(p);
			}
		}
		else {
			PlayLayer::togglePracticeMode(p);
		}
	}

	void resume() {
		PlayLayer::resume();
		if (pausecountdown) freezeCount = true;
		if (pausecountdown) g_pauseCount->setOpacity(255);
	}

	void toggleFlipped(bool one, bool two) {
		if (!mirror) {
			PlayLayer::toggleFlipped(one, two);
		}
	}

	void setAnchoredPosition(CCNode* label, int anchorPos) {
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (anchorPos == 1) {
			label->setPosition(5, corner - 10);
		} else if (anchorPos == 2) {
			label->setPosition(5, corner - 25);
		} else if (anchorPos == 3) {
			label->setPosition(5, corner - 40);
		} else if (anchorPos == 4) {
			label->setPosition(5, corner - 55);
		} else if (anchorPos == 5) {
			label->setPosition(5, corner - 70);
		} else if (anchorPos == 6) {
			label->setPosition(5, corner - 85);
		} else if (anchorPos == 7) {
			label->setPosition(5, corner - 100);
		} else if (anchorPos == 8) {
			label->setPosition(5, corner - 115);
		} else if (anchorPos == 9) {
			label->setPosition(5, corner - 130);
		} else if (anchorPos == 10) {
			label->setPosition(5, corner - 145);
		} else if (anchorPos == 11) {
			label->setPosition(5, corner - 160);
		} else if (anchorPos == 12) {
			label->setPosition(5, corner - 175);
		} else if (anchorPos == 13) {
			label->setPosition(5, corner - 190);
		} else if (anchorPos == 14) {
			label->setPosition(5, corner - 205);
		}
	}

	void startGame() {
		PlayLayer::startGame();
		if (fps) {
			FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(CCDirector::sharedDirector()->getRunningScene()->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
		}
	}

	bool init(GJGameLevel* gl) {
		leftDisplay = 0;
		auto corner = CCDirector::sharedDirector()->getScreenTop();
		if (startpos) {
			rightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			leftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_startPosText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_startPosIndex = -1;
			g_startPoses = {};
			
		}
		if (cpswitch) {
			CPrightButton = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
			CPleftButton = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
			g_checkpointText = CCLabelBMFont::create("0/0", "bigFont.fnt");
			g_checkpointIndex = -1;
			g_checkpointsIG = {};
			
		}
		if (customMessage) {
			g_message = CCLabelBMFont::create(message, "bigFont.fnt");
		}
		if (jumps) {
			g_jumps = CCLabelBMFont::create("Total Jumps: 0", "bigFont.fnt");
		}
		if (attempts) {
			g_atts = CCLabelBMFont::create("Attempts: 0", "bigFont.fnt");
		}
		if (currentRun) {
			g_run = CCLabelBMFont::create("Run from ???", "bigFont.fnt");
		}
		if (bestRun) {
			g_bestRun = CCLabelBMFont::create("Best Run: 0 to 0", "bigFont.fnt");
		}
		if (levelinfo) {
			g_levelInfo = CCLabelBMFont::create("Unnamed (No ID)", "bigFont.fnt");
		}
		if (clicks) {
			g_clicks = CCLabelBMFont::create("?? Clicks", "bigFont.fnt");
			clickscount = 0;
		}
		if (cheater) {
			g_cheating = CCLabelBMFont::create("Not Cheating", "bigFont.fnt");
		}
		if (totalAtts) {
			g_tatts = CCLabelBMFont::create("Global Atts: ??", "bigFont.fnt");
		}
		if (lastDeath) {
			g_death = CCLabelBMFont::create("Last Death: ???", "bigFont.fnt");
		}
		if (noclipDeaths) {
			font = CCLabelBMFont::create("Noclip Deaths: ???", "bigFont.fnt");
		}
		if (accuracy) {
			text = CCLabelBMFont::create("100%", "bigFont.fnt");
		}
		if (macroStatus) {
			g_macro = CCLabelBMFont::create("Playing: 0/0", "bigFont.fnt");
		}
		if (pausecountdown) {
			g_pauseCount = CCLabelBMFont::create("Not Paused", "goldFont.fnt");
		}
		

			PlayLayer::init(gl);

		frame = 0;
		maxFrame = 0;
		if (variable_index == 0 && applyVC) {
			gl->m_levelName = stringVC;
		} else if (variable_index == 1 && applyVC) {
			gl->m_levelDesc = stringVC;
		} else if (variable_index == 2 && applyVC) {
			gl->m_creatorName = stringVC;
		} else if (variable_index == 3 && applyVC) {
			gl->m_attempts = std::stoi(stringVC);
		} else if (variable_index == 4 && applyVC) {
			gl->m_jumps = std::stoi(stringVC);
		}
		if (customColor) {
			m_player1->setColor(ccc3(customR1, customG1, customB1));
			m_player1->setSecondColor(ccc3(customR2, customG2, customB2));
		}
		if (complete) {
			//gl->savePercentage(100, false, 100, 100, true);
		}
		if (startpos) {
			g_startPosText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				g_startPosText->setPosition(245 , corner - 275);
			}
			g_startPosText->setScale(0.5);
			g_startPosText->setAnchorPoint({0, 0.5});
			g_startPosText->setOpacity(50);
			rightButton->::Main::setPosition(220 , corner - 275);
			rightButton->setScale(0.5);
			rightButton->setAnchorPoint({0, 0.5});
			rightButton->setOpacity(50);
			leftButton->::Main::setPosition(310 , corner - 275);
			leftButton->setRotation(180);
			leftButton->setScale(0.5);
			leftButton->setAnchorPoint({0, 0.5});
			leftButton->setOpacity(50);

			if (!m_isTestMode) {
				g_startPosText->setVisible(false);
				rightButton->setVisible(false);
				leftButton->setVisible(false);
			}
			addChild(g_startPosText, 1000);
			addChild(rightButton, 1000);
			addChild(leftButton, 1000);
		}
		if (cpswitch) {
			g_checkpointText->setPosition(252 , corner - 275);
			if (g_startPoses.size() > 9) {
				//g_checkpointText->setPosition(245 , corner - 275);
			}
			g_checkpointText->setScale(0.5);
			g_checkpointText->setAnchorPoint({0, 0.5});
			g_checkpointText->setOpacity(50);
			CPrightButton->::Main::setPosition(220 , corner - 275);
			CPrightButton->setScale(0.5);
			CPrightButton->setAnchorPoint({0, 0.5});
			CPrightButton->setOpacity(50);
			CPleftButton->::Main::setPosition(310 , corner - 275);
			CPleftButton->setRotation(180);
			CPleftButton->setScale(0.5);
			CPleftButton->setAnchorPoint({0, 0.5});
			CPleftButton->setOpacity(50);

			if (!m_isPracticeMode) {/*
				g_checkpointText->setVisible(false);
				CPrightButton->setVisible(false);
				CPleftButton->setVisible(false);
				*/
			}
			addChild(g_checkpointText, 1000);
			addChild(CPrightButton, 1000);
			addChild(CPleftButton, 1000);
		}
		if (progressBar) {
			m_percentLabel->setPositionX(259.638);
		}
			percentXpos = m_percentLabel->getPositionX();
			percentYpos = m_percentLabel->getPositionY();
			percentScale = m_percentLabel->getScale();
			percentOpac = m_percentLabel->getOpacity();
		if (m_isTestMode) leftDisplay = 1;
		if (customMessage) {
			leftDisplay++;
			setAnchoredPosition(g_message, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_message->setScale(0.4);
			g_message->setAnchorPoint({0, 0.5});
			g_message->setOpacity(100);
			addChild(g_message, 1001);
		}
		if (cheater) {
			leftDisplay++;
			setAnchoredPosition(g_cheating, leftDisplay);
			//g_cheating->setPosition(5 , corner - 10);
			g_cheating->setScale(0.4);
			g_cheating->setAnchorPoint({0, 0.5});
			g_cheating->setOpacity(100);
			addChild(g_cheating, 1001);
		}
		if (currentRun) {
			leftDisplay++;
			setAnchoredPosition(g_run, leftDisplay);
			//g_run->setPosition(5 , corner - 70);
			g_run->setScale(0.4);
			g_run->setAnchorPoint({0, 0.5});
			g_run->setOpacity(100);
			double start = (m_player1->getPositionX() / m_levelLength) * 100;
			char str[64];
			sprintf(str, "Run from: %.0lf%%", start);
			g_run->setString(str);

			addChild(g_run, 1000);
		}
		if (jumps) {
			leftDisplay++;
			setAnchoredPosition(g_jumps, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_jumps->setScale(0.4);
			g_jumps->setAnchorPoint({0, 0.5});
			g_jumps->setOpacity(100);
			std::string po = "Total Jumps:" + std::to_string(gl->m_jumps);
			g_jumps->setString(po.c_str());
			addChild(g_jumps, 1001);
		}
		if (totalAtts) {
			leftDisplay++;
			setAnchoredPosition(g_tatts, leftDisplay);
			//g_tatts->setPosition(5 , corner - 55);
			g_tatts->setScale(0.4);
			g_tatts->setAnchorPoint({0, 0.5});
			g_tatts->setOpacity(100);
			std::string at = "Global Atts:" + std::to_string(m_level->m_attempts);
			g_tatts->setString(at.c_str());
			addChild(g_tatts, 1001);
		}
		if (lastDeath) {
			leftDisplay++;
			setAnchoredPosition(g_death, leftDisplay);
			//g_death->setPosition(5 , corner - 130);
			g_death->setScale(0.4);
			g_death->setAnchorPoint({0, 0.5});
			g_death->setOpacity(100);
			double start = m_lastDeathPercent;
			char str[64];
			sprintf(str, "Last Death:%.0lf%%", start);
			g_death->setString(str);

			addChild(g_death, 1000);
		}
		if (noclipDeaths) {
			leftDisplay++;
			setAnchoredPosition(font, leftDisplay);
			//g_tatts->setPosition(5 , corner - 160);
			font->setScale(0.4);
			font->setAnchorPoint({0, 0.5});
			font->setOpacity(100);
			addChild(font, 1001);
		}
		if (attempts) {
			leftDisplay++;
			setAnchoredPosition(g_atts, leftDisplay);
			//g_atts->setPosition(5 , corner - 40);
			g_atts->setScale(0.4);
			g_atts->setAnchorPoint({0, 0.5});
			g_atts->setOpacity(100);
			auto work = m_currentAttempt;
			char str[64];
			sprintf(str, "Attempts: %0d", work);
			g_atts->setString(str);

			addChild(g_atts, 1000);
		}
		if (bestRun) {
			leftDisplay++;
			setAnchoredPosition(g_bestRun, leftDisplay);
			//g_bestRun->setPosition(5 , corner - 85);
			g_bestRun->setScale(0.4);
			g_bestRun->setAnchorPoint({0, 0.5});
			g_bestRun->setOpacity(100);
			bestEnd = 0;
			bestStart = 0;
			bestEnd2 = 0;
			bestStart2 = 0;
			bestStart = (m_player1->getPositionX() / m_levelLength) * 100;
			addChild(g_bestRun, 1001);
		}
		if (levelinfo) {
			leftDisplay++;
			setAnchoredPosition(g_levelInfo, leftDisplay);
			std::string display;
			g_levelInfo->setScale(0.4);
			g_levelInfo->setAnchorPoint({0, 0.5});
			g_levelInfo->setOpacity(100);
			std::string levelName = gl->m_levelName;
			std::string levelAuthor = gl->m_creatorName;
			std::string levelID = std::to_string(gl->m_levelID);
			if (hideID) {
				levelID = "--------";
			} else if (levelID<"22" && levelID>"0" || levelID == "3" || levelID == "4" || levelID == "5" || levelID == "6" || levelID == "7" || levelID == "8" || levelID == "9") {
				levelAuthor = "RobTop"; // this wasnt working from Polargeist (3) to Cycles (9) so i had to do that lmao
			} else if (levelID == "0") {
				levelID = "Copy";
			}
			if (author) {
				display = levelName + " by " + levelAuthor + " (" + levelID + ")";
			} else {
				display = levelName + " (" + levelID + ")";
			}
			g_levelInfo->setString(display.c_str());
			addChild(g_levelInfo, 1001);
		}
		if (clicks) {
			leftDisplay++;
			setAnchoredPosition(g_clicks, leftDisplay);
			//g_clicks->setPosition(5 , corner - 115);
			g_clicks->setScale(0.4);
			g_clicks->setAnchorPoint({0, 0.5});
			g_clicks->setOpacity(100);
			std::string display2 = std::to_string(clickscount) + " clicks";
			g_clicks->setString(display2.c_str());
			addChild(g_clicks, 1001);
		}
		if (accuracy) {
			leftDisplay++;
			setAnchoredPosition(text, leftDisplay);
			//text->setPosition(5 , corner - 145);
			text->setAnchorPoint({0, 0.5});
			text->setTag(31403);
			text->setScale(0.4);
			text->setOpacity(100);
			addChild(text, 1000);
			frames = noclipped_frames = 0;
		}
		if (macroStatus) {
			leftDisplay++;
			setAnchoredPosition(g_macro, leftDisplay);
			//text->setPosition(5 , corner - 145);
			g_macro->setAnchorPoint({0, 0.5});
			g_macro->setScale(0.4);
			g_macro->setOpacity(100);
			std::string macroInputs = "Playing: " + std::to_string(pushIterate) + "/" + std::to_string(push.size());
			g_macro->setString(macroInputs.c_str());
			addChild(g_macro, 1000);
		}
		if (pausecountdown) {
			g_pauseCount->setPosition({ CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 175 });
			g_pauseCount->setAnchorPoint({0, 0.5});
			g_pauseCount->setOpacity(0);
			addChild(g_pauseCount, 1000);
		}
		secondary = m_player2->getColor();
		primary = m_player1->getColor();
		return true;
	}
};

class $(UILayer) {
	void customKeybind(int current, cocos2d::enumKeyCodes key) {
	if (current == 0) {
		if (current == key_current) customKey = KEY_A;
		if (current == key_current2) customKey2 = KEY_A;
		if (current == key_current3) customKey3 = KEY_A;
		if (current == key_current4) customKey4 = KEY_A;
		if (current == key_current5) customKey5 = KEY_A;
	} else if (current == 1) {
		if (current == key_current) customKey = KEY_B;
		if (current == key_current2) customKey2 = KEY_B;
		if (current == key_current3) customKey3 = KEY_B;
		if (current == key_current4) customKey4 = KEY_B;
		if (current == key_current5) customKey5 = KEY_B;
	} else if (current == 2) {
		if (current == key_current) customKey = KEY_C;
		if (current == key_current2) customKey2 = KEY_C;
		if (current == key_current3) customKey3 = KEY_C;
		if (current == key_current4) customKey4 = KEY_C;
		if (current == key_current5) customKey5 = KEY_C;
	} else if (current == 3) {
		if (current == key_current) customKey = KEY_D;
		if (current == key_current2) customKey2 = KEY_D;
		if (current == key_current3) customKey3 = KEY_D;
		if (current == key_current4) customKey4 = KEY_D;
		if (current == key_current5) customKey5 = KEY_D;
	} else if (current == 4) {
		if (current == key_current) customKey = KEY_E;
		if (current == key_current2) customKey2 = KEY_E;
		if (current == key_current3) customKey3 = KEY_E;
		if (current == key_current4) customKey4 = KEY_E;
		if (current == key_current5) customKey5 = KEY_E;
	} else if (current == 5) {
		if (current == key_current) customKey = KEY_F;
		if (current == key_current2) customKey2 = KEY_F;
		if (current == key_current3) customKey3 = KEY_F;
		if (current == key_current4) customKey4 = KEY_F;
		if (current == key_current5) customKey5 = KEY_F;
	} else if (current == 6) {
		if (current == key_current) customKey = KEY_G;
		if (current == key_current2) customKey2 = KEY_G;
		if (current == key_current3) customKey3 = KEY_G;
		if (current == key_current4) customKey4 = KEY_G;
		if (current == key_current5) customKey5 = KEY_G;
	} else if (current == 7) {
		if (current == key_current) customKey = KEY_H;
		if (current == key_current2) customKey2 = KEY_H;
		if (current == key_current3) customKey3 = KEY_H;
		if (current == key_current4) customKey4 = KEY_H;
		if (current == key_current5) customKey5 = KEY_H;
	} else if (current == 8) {
		if (current == key_current) customKey = KEY_I;
		if (current == key_current2) customKey2 = KEY_I;
		if (current == key_current3) customKey3 = KEY_I;
		if (current == key_current4) customKey4 = KEY_I;
		if (current == key_current5) customKey5 = KEY_I;
	} else if (current == 9) {
		if (current == key_current) customKey = KEY_J;
		if (current == key_current2) customKey2 = KEY_J;
		if (current == key_current3) customKey3 = KEY_J;
		if (current == key_current4) customKey4 = KEY_J;
		if (current == key_current5) customKey5 = KEY_J;
	} else if (current == 10) {
		if (current == key_current) customKey = KEY_K;
		if (current == key_current2) customKey2 = KEY_K;
		if (current == key_current3) customKey3 = KEY_K;
		if (current == key_current4) customKey4 = KEY_K;
		if (current == key_current5) customKey5 = KEY_K;
	} else if (current == 11) {
		if (current == key_current) customKey = KEY_L;
		if (current == key_current2) customKey2 = KEY_L;
		if (current == key_current3) customKey3 = KEY_L;
		if (current == key_current4) customKey4 = KEY_L;
		if (current == key_current5) customKey5 = KEY_L;
	} else if (current == 12) {
		if (current == key_current) customKey = KEY_M;
		if (current == key_current2) customKey2 = KEY_M;
		if (current == key_current3) customKey3 = KEY_M;
		if (current == key_current4) customKey4 = KEY_M;
		if (current == key_current5) customKey5 = KEY_M;
	} else if (current == 13) {
		if (current == key_current) customKey = KEY_N;
		if (current == key_current2) customKey2 = KEY_N;
		if (current == key_current3) customKey3 = KEY_N;
		if (current == key_current4) customKey4 = KEY_N;
		if (current == key_current5) customKey5 = KEY_N;
	} else if (current == 14) {
		if (current == key_current) customKey = KEY_O;
		if (current == key_current2) customKey2 = KEY_O;
		if (current == key_current3) customKey3 = KEY_O;
		if (current == key_current4) customKey4 = KEY_O;
		if (current == key_current5) customKey5 = KEY_O;
	} else if (current == 15) {
		if (current == key_current) customKey = KEY_P;
		if (current == key_current2) customKey2 = KEY_P;
		if (current == key_current3) customKey3 = KEY_P;
		if (current == key_current4) customKey4 = KEY_P;
		if (current == key_current5) customKey5 = KEY_P;
	} else if (current == 16) {
		if (current == key_current) customKey = KEY_Q;
		if (current == key_current2) customKey2 = KEY_Q;
		if (current == key_current3) customKey3 = KEY_Q;
		if (current == key_current4) customKey4 = KEY_Q;
		if (current == key_current5) customKey5 = KEY_Q;
	} else if (current == 17) {
		if (current == key_current) customKey = KEY_R;
		if (current == key_current2) customKey2 = KEY_R;
		if (current == key_current3) customKey3 = KEY_R;
		if (current == key_current4) customKey4 = KEY_R;
		if (current == key_current5) customKey5 = KEY_R;
	} else if (current == 18) {
		if (current == key_current) customKey = KEY_S;
		if (current == key_current2) customKey2 = KEY_S;
		if (current == key_current3) customKey3 = KEY_S;
		if (current == key_current4) customKey4 = KEY_S;
		if (current == key_current5) customKey5 = KEY_S;
	} else if (current == 19) {
		if (current == key_current) customKey = KEY_T;
		if (current == key_current2) customKey2 = KEY_T;
		if (current == key_current3) customKey3 = KEY_T;
		if (current == key_current4) customKey4 = KEY_T;
		if (current == key_current5) customKey5 = KEY_T;
	} else if (current == 20) {
		if (current == key_current) customKey = KEY_U;
		if (current == key_current2) customKey2 = KEY_U;
		if (current == key_current3) customKey3 = KEY_U;
		if (current == key_current4) customKey4 = KEY_U;
		if (current == key_current5) customKey5 = KEY_U;
	} else if (current == 21) {
		if (current == key_current) customKey = KEY_V;
		if (current == key_current2) customKey2 = KEY_V;
		if (current == key_current3) customKey3 = KEY_V;
		if (current == key_current4) customKey4 = KEY_V;
		if (current == key_current5) customKey5 = KEY_V;
	} else if (current == 22) {
		if (current == key_current) customKey = KEY_W;
		if (current == key_current2) customKey2 = KEY_W;
		if (current == key_current3) customKey3 = KEY_W;
		if (current == key_current4) customKey4 = KEY_W;
		if (current == key_current5) customKey5 = KEY_W;
	} else if (current == 23) {
		if (current == key_current) customKey = KEY_X;
		if (current == key_current2) customKey2 = KEY_X;
		if (current == key_current3) customKey3 = KEY_X;
		if (current == key_current4) customKey4 = KEY_X;
		if (current == key_current5) customKey5 = KEY_X;
	} else if (current == 24) {
		if (current == key_current) customKey = KEY_Y;
		if (current == key_current2) customKey2 = KEY_Y;
		if (current == key_current3) customKey3 = KEY_Y;
		if (current == key_current4) customKey4 = KEY_Y;
		if (current == key_current5) customKey5 = KEY_Y;
	} else if (current == 25) {
		if (current == key_current) customKey = KEY_Z;
		if (current == key_current2) customKey2 = KEY_Z;
		if (current == key_current3) customKey3 = KEY_Z;
		if (current == key_current4) customKey4 = KEY_Z;
		if (current == key_current5) customKey5 = KEY_Z;
	} else if (current == 26) {
		if (current == key_current) customKey = KEY_Left;
		if (current == key_current2) customKey2 = KEY_Left;
		if (current == key_current3) customKey3 = KEY_Left;
		if (current == key_current4) customKey4 = KEY_Left;
		if (current == key_current5) customKey5 = KEY_Left;
	} else if (current == 27) {
		if (current == key_current) customKey = KEY_Right;
		if (current == key_current2) customKey2 = KEY_Right;
		if (current == key_current3) customKey3 = KEY_Right;
		if (current == key_current4) customKey4 = KEY_Right;
		if (current == key_current5) customKey5 = KEY_Right;
	} else if (current == 28) {
		if (current == key_current) customKey = KEY_One;
		if (current == key_current2) customKey2 = KEY_One;
		if (current == key_current3) customKey3 = KEY_One;
		if (current == key_current4) customKey4 = KEY_One;
		if (current == key_current5) customKey5 = KEY_One;
	} else if (current == 29) {
		if (current == key_current) customKey = KEY_Two;
		if (current == key_current2) customKey2 = KEY_Two;
		if (current == key_current3) customKey3 = KEY_Two;
		if (current == key_current4) customKey4 = KEY_Two;
		if (current == key_current5) customKey5 = KEY_Two;
	} else if (current == 30) {
		if (current == key_current) customKey = KEY_Three;
		if (current == key_current2) customKey2 = KEY_Three;
		if (current == key_current3) customKey3 = KEY_Three;
		if (current == key_current4) customKey4 = KEY_Three;
		if (current == key_current5) customKey5 = KEY_Three;
	} else if (current == 31) {
		if (current == key_current) customKey = KEY_Four;
		if (current == key_current2) customKey2 = KEY_Four;
		if (current == key_current3) customKey3 = KEY_Four;
		if (current == key_current4) customKey4 = KEY_Four;
		if (current == key_current5) customKey5 = KEY_Four;
	} else if (current == 32) {
		if (current == key_current) customKey = KEY_Five;
		if (current == key_current2) customKey2 = KEY_Five;
		if (current == key_current3) customKey3 = KEY_Five;
		if (current == key_current4) customKey4 = KEY_Five;
		if (current == key_current5) customKey5 = KEY_Five;
	}
}

	void customMod(int current) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		bool hitbox = true;
		float tempSpeed = 1;
		if (current == 0) {
			noclip = !noclip;
		} else if (current == 1) {
			autoKill = !autoKill;
		} else if (current == 2) {
			PlayLayer::get()->resetLevel();
		} else if (current == 3) {
			if (speedhack != 1) {
				tempSpeed = speedhack;
				speedhack = 1;
			} else {
				speedhack = tempSpeed;
			}
		} else if (current == 4) {
			s_showOnDeath = !s_showOnDeath;
		} else if (current == 5) {
			if (autoclick) {
				autoclick = false;
				GJBaseGameLayer::get()->releaseButton(1,true);
			} else {
				autoclick = true;
			}
		} else if (current == 6) {
			mpl->updateIndex(false);
		} else if (current == 7) {
			mpl->updateIndex(true);
		} else if (current == 10) {
			PlayLayer::get()->markCheckpoint();
		} else if (current == 11) {
			PlayLayer::get()->removeLastCheckpoint();
		}
	}

	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<Main*>(PlayLayer::get());
		customKeybind(key_current, customKey);
		customKeybind(key_current2, customKey2);
		customKeybind(key_current3, customKey3);
		customKeybind(key_current4, customKey4);
		customKeybind(key_current5, customKey5);
		if (kc == KEY_F) {
			if (framestep) {
				stepready = true;
				stepready = false;
			}
		} else if (kc == customKey && keybinds >= 1) {
			customMod(mod_current);
		} else if (kc == customKey2 && keybinds >= 2) {
			customMod(mod_current2);
		} else if (kc == customKey3 && keybinds >= 3) {
			customMod(mod_current3);
		} else if (kc == customKey4 && keybinds >= 4) {
			customMod(mod_current4);
		} else if (kc == customKey5 && keybinds >= 5) {
			customMod(mod_current5);
		} else {
			UILayer::keyDown(kc);
		}
	}
};

class $modify(PauseLayer) {
	void keyDown(cocos2d::enumKeyCodes key) {
		if (key == KEY_Escape) {
			if (!ignoreESC) {
				PauseLayer::keyDown(key);
			}
		} else {
			PauseLayer::keyDown(key);
		}
	}
};

//std::filesystem::path yes = std::filesystem::current_path() / "Resources" / "MenuSongs";
//std::filesystem::path nongspath = std::filesystem::current_path() / "Resources" / "NONGs";

void getNONGs() {
	/*
	NONGs.clear();
    for (auto& p : std::filesystem::directory_iterator(nongspath)) {
		NONGs.push_back(p.path().filename().string());
	}
	for (int i = 1; i < NONGs.size() + 1; i++) {
		items[i] = NONGs[i - 1].c_str();
	}
	*/
}

class $modify(GameSoundManager) {
  	void playBackgroundMusic(gd::string song, bool b1, bool b2) {

  	if ((std::string(song) == "menuLoop.mp3") && randomLoop) {
		//song = getRandomSong();
	}  // random menu loop

	//findsong = replacing;
	replacesong = replaceWith;

	if (item_current_idx > 0 && EnableNONGLoader) {
    	//GameSoundManager::playBackgroundMusic("NONGs/" + replacesong, b1, b2);
	} else {
		//GameSoundManager::playBackgroundMusic(song, b1, b2);
	}
	GameSoundManager::playBackgroundMusic(song, b1, b2);
	}
};

class $modify(HardStreak) {
	void updateStroke(float f) {
		if (nopulse) m_pulseSize = pulse;
		if (solidwave) m_isSolid = true;
		if (rainP1wave && PlayLayer::get()) this->setColor(col);
		if (solidwave) this->setBlendFunc(getBlendFunc());
		HardStreak::updateStroke(f);
	}
};