cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FIREWORK_VERSION_MAJOR 0 CACHE STRING "Major")
set(FIREWORK_VERSION_MINOR 0 CACHE STRING "Minor")
set(FIREWORK_VERSION_PATCH 0 CACHE STRING "Patch")
set(FIREWORK_VERSION_TWEAK 1 CACHE STRING "Tweak")

set(FIREWORK_TRACY_PROFILER OFF)

project(Firework)

find_package(glfw3 3.3 REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(ASSIMP REQUIRED assimp)
pkg_check_modules(FREETYPE REQUIRED freetype2)

set(SIMDJSON_JUST_LIBRARY ON CACHE STRING "Build just the library, nothing else." FORCE)
add_subdirectory(simdjson EXCLUDE_FROM_ALL)

include_directories(
    "${ASSIMP_INCLUDE_DIRS}"
    "${FREETYPE_INCLUDE_DIRS}"
    "${PROJECT_BINARY_DIR}"
    "engine/include"
    "glad/include"
    "simdjson/include"
    "glm/"
    "tracy/"
    "loguru/"
    "imgui/"
    "imgui/examples"
)

if(${FIREWORK_TRACY_PROFILER})
add_definitions(-DTRACY_ENABLE)
endif()

add_definitions(-W -Wall -pedantic -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-value -Wno-sign-compare)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(tracy SHARED "tracy/TracyClient.cpp")

configure_file(engine/include/Version.hpp.in Version.hpp)

add_subdirectory("engine")
add_subdirectory("playground")
add_subdirectory("gunpowder")