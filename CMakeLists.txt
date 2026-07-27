cmake_minimum_required(VERSION 3.21)

# 1. Fix CMake 4.x policy issue with legacy sub-dependencies
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

project(MainLevelRoulette VERSION 1.0.0)

# 2. Fix Clang 20 consteval error inside fmt library
add_compile_definitions(FMT_USE_CONSTEXPR=0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Please define the GEODE_SDK environment variable to point to your Geode SDK checkout")
endif()

# Add Geode SDK as a subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Set up dependencies, resources, and link Geode
setup_geode_mod(${PROJECT_NAME})
