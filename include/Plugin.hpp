#pragma once

#include <Geode/Geode.hpp>
#include <Geode/loader/Dispatch.hpp>

inline static void AddPlugin(const char* the, bool* thing) {
    geode::DispatchEvent<const char*>("ninxout.crystalclient/addPluginName", the).post();
    geode::DispatchEvent<bool*>("ninxout.crystalclient/addPluginBool", thing).post();
}