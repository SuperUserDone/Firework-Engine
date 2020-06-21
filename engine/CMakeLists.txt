set(FIREWORK_SOURCE
"../glad/src/glad.c"
"src/core/Scene.cpp"
"src/render/Action.cpp"
"src/render/Framebuffer.cpp"
"src/render/Renderer.cpp"
"src/render/RenderPass.cpp"
"src/window/Window.cpp"
)

set(FIREWORK_LIBRARIES
    glfw
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES} GL)