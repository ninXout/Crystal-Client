cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(CrystalClient VERSION 1.0.0)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
target_include_directories(${PROJECT_NAME} PRIVATE 
    src/Utilities/DiscordRPC
)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/Utilities/DiscordRPC/libdiscord-rpc.a)

CPMAddPackage("gh:matcool/gd-imgui-cocos#3c7f7c2")

if (APPLE)
    target_compile_options(${PROJECT_NAME} PRIVATE -fno-inline)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    -DCommentType=CommentTypeDummy
)

target_link_libraries(${PROJECT_NAME} geode-sdk imgui-cocos)
create_geode_file(${PROJECT_NAME})