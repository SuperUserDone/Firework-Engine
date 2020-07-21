set(FIREWORK_SOURCE
"../glad/src/glad.c"
"../loguru/loguru.cpp"
"src/input/InputKeyboard.cpp"
"src/input/InputMouse.cpp"
"src/input/InputWindow.cpp"
"src/render/RenderServer.cpp"
"src/window/Window.cpp"
)

set(FIREWORK_LIBRARIES
    ${FREETYPE_LIBRARIES}
    ${PLATFORM_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${LUA_LIBRARIES}
    glfw
    simdjson
    tracy
    GL
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES})