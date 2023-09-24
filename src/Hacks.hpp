#include "Includes.hpp"
#include <streambuf>
#include "./Renderer/Renderer.hpp"

#define mbo(type, class, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(class) + offset)

auto macros = Mod::get()->getConfigDir().append("Amethyst").append("Macros");
auto cb = Mod::get()->getConfigDir().append("Amethyst").append("ClickBot");
auto renderer = Mod::get()->getConfigDir().append("Amethyst").append("Renderer");
auto conf = Mod::get()->getConfigDir().append("Config");
auto betterBG = Mod::get()->getConfigDir().append("BetterBG");
