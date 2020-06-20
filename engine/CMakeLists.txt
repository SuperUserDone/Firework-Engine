set(FIREWORK_SOURCE
    "src/window/Window.cpp"
    "../glad/src/glad.c"
)

set(FIREWORK_LIBRARIES
    glfw
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES} GL)