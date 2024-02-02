cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(CrystalClient VERSION 1.0.0 LANGUAGES OBJCXX CXX)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/CrystalClient/CrystalClient.cpp
    src/CrystalUI/CrystalUI.cpp
    src/CrystalUI/Blur.cpp
    src/CrystalUI/ImGuiHelper.cpp
    src/Mods/Player/noclip.cpp
    src/Mods/Level/PracticeMusic.cpp
    src/Mods/Level/SafeMode.cpp
    src/Mods/Bypass/UnlockAll.cpp
    src/Mods/Bypass/InstantComplete.cpp
    src/Mods/Global/Speedhack.cpp
    src/Mods/Amethyst/Amethyst.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# CPMAddPackage("gh:ninXout/gd-imgui-cocos#6f014e3")
add_subdirectory(../../GitHub/gd-imgui-cocos ${CMAKE_CURRENT_BINARY_DIR}/gd-imgui-cocos_build)
target_link_libraries(${PROJECT_NAME} imgui-cocos)

setup_geode_mod(${PROJECT_NAME})
