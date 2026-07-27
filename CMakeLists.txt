cmake_minimum_required(VERSION 3.21) [cite: 1]

# 1. Fix CMake policy version issue with legacy dependencies (e.g. TulipHook/result)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

project(MainLevelRoulette VERSION 1.0.0) [cite: 1]

if (NOT DEFINED ENV{GEODE_SDK}) [cite: 1]
    message(FATAL_ERROR "Please define the GEODE_SDK environment variable to point to your Geode SDK checkout") [cite: 1]
endif() [cite: 1]

# 2. Prevent Clang 20 from failing on fmt 10.1.1 constexpr/consteval checks
add_compile_definitions(FMT_USE_CONSTEVAL=0)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wno-invalid-constexpr -Wno-deprecated-literal-operator)
endif()

include($ENV{GEODE_SDK}/CMakeShared.cmake) [cite: 1]

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp) [cite: 1]
add_library(${PROJECT_NAME} SHARED ${SOURCES}) [cite: 1]

target_include_directories(${PROJECT_NAME} PRIVATE src) [cite: 1]

setup_geode_mod(${PROJECT_NAME}) [cite: 1]
