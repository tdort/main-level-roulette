cmake_minimum_required(VERSION 3.21)
project(MainLevelRoulette VERSION 1.0.0)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Please define the GEODE_SDK environment variable to point to your Geode SDK checkout")
endif()

include($ENV{GEODE_SDK}/CMakeShared.cmake)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

setup_geode_mod(${PROJECT_NAME})
