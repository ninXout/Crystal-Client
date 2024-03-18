#pragma once

#include "../Mods/Display/Display.hpp"

using namespace CrystalClient;

inline double getPercentage() {
    if (!PlayLayer::get()) return 0;

    double ret = ((PlayLayer::get()->m_player1->getPositionX()) / PlayLayer::get()->m_levelLength) * 100;
    if (ret < 0) ret = 0;
    if (ret > 100) ret = 100;

    return ret;
}

inline bool shouldNotSave() {
    bool noclipCheck = getSavedVar<bool>("noclip");
    if (getSavedVar<bool>("count_clean_noclip") && (getTempVar<int>("noclip_deaths") == 0)) noclipCheck = false;
    bool regularChecks = (noclipCheck || (getSavedVar<float>("speed") != 1 && getSavedVar<bool>("speedhack")) || getSavedVar<bool>("no_mirror") || getSavedVar<bool>("framestep") || 
            getSavedVar<bool>("autoclicker") || getSavedVar<bool>("layout_mode") || getSavedVar<bool>("AT_record") || getSavedVar<bool>("AT_replay") || getSavedVar<float>("FPS") > 360.0 ||
            getSavedVar<bool>("jump_hack"));
    return regularChecks;
}

// patching utils !! :D

template <class T, class P>
inline T& from(P* ptr, std::intptr_t offset) { // geode mafia will come for my family and my kids
    return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(ptr) + offset);
}

inline std::vector<unsigned char> toBytes(float f) {
    std::vector<unsigned char> data(sizeof(f));
    std::memcpy(data.data(), &f, sizeof(f));
    return data;
}

inline float fromBytes(const std::vector<unsigned char>& data) {
    float f;
    if (data.size() != sizeof(f))
        throw std::runtime_error{"Size of data in vector and float do not match"};
    std::memcpy(&f, data.data(), sizeof(f));
    return f;
}