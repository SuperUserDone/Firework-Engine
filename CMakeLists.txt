cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY CXX_STANDARD 20)

set(FIREWORK_VERSION_MAJOR "0" CACHE STRING "Major")
set(FIREWORK_VERSION_MINOR "0" CACHE STRING "Minor")
set(FIREWORK_VERSION_PATCH "0" CACHE STRING "Patch")
set(FIREWORK_VERSION_TWEAK "1" CACHE STRING "Tweak")

option(FIREWORK_PROFILER "Build with tracy profiler" ON)

project(Firework)

find_package(glfw3 3.3 REQUIRED)

include_directories(
    "engine/include"
    "glad/include"
    "glm/"
)

add_subdirectory("engine")
add_subdirectory("playground")