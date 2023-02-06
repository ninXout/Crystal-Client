cmake_minimum_required(VERSION 3.3.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CrystalClient VERSION 1.0.0)

set(IMGUI_COCOS_TARGET geode-sdk)

file(GLOB SOURCES
	src/*.cpp
    src/*.hpp
)

# Set up the mod binary
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

set(GEODE_LINK_NIGHTLY ON)
add_subdirectory($ENV{GEODE_SDK} $ENV{GEODE_SDK}/build)

include(cmake/CPM.cmake)
CPMAddPackage("gh:matcool/gd-imgui-cocos#f8d86e6")

target_link_libraries(CrystalClient imgui-cocos)

target_link_libraries(CrystalClient "-framework OpenGL")

target_link_libraries(${PROJECT_NAME} geode-sdk)

create_geode_file(${PROJECT_NAME})
