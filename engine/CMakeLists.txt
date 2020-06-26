set(FIREWORK_SOURCE
"../glad/src/glad.c"
"src/core/Scene.cpp"
"src/core/Action.cpp"
"src/core/ActionQueue.cpp"
"src/core/components/Component.cpp"
"src/core/components/ComponentMesh.cpp"
"src/core/components/ComponentMeshLoader.cpp"
"src/core/objects/Object.cpp"
"src/core/objects/ObjectCamera.cpp"
"src/core/objects/ObjectLight.cpp"
"src/core/objects/ObjectBasic.cpp"
"src/render/Framebuffer.cpp"
"src/render/MeshRenderer.cpp"
"src/render/Renderer.cpp"
"src/render/RenderPass.cpp"
"src/window/Window.cpp"
)

set(FIREWORK_LIBRARIES
    glfw
    ${ASSIMP_LIBRARIES}
    pthread
    dl
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES} GL)