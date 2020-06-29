set(FIREWORK_SOURCE
"../glad/src/glad.c"
"src/core/Scene.cpp"
"src/core/Action.cpp"
"src/core/ActionQueue.cpp"
"src/core/components/Component.cpp"
"src/core/components/ComponentMaterial.cpp"
"src/core/components/ComponentMesh.cpp"
"src/core/components/ComponentMeshLoader.cpp"
"src/core/components/ComponentTransform.cpp"
"src/core/mesh/Mesh.cpp"
"src/core/objects/Object.cpp"
"src/core/objects/ObjectCamera.cpp"
"src/core/objects/ObjectLight.cpp"
"src/core/objects/ObjectBasic.cpp"
"src/io/binary/BinaryBuffer.cpp"
"src/render/Framebuffer.cpp"
"src/render/Material.cpp"
"src/render/MeshRenderer.cpp"
"src/render/Renderer.cpp"
"src/render/RenderPass.cpp"
"src/render/Shader.cpp"
"src/window/Window.cpp"
)

set(FIREWORK_LIBRARIES
    glfw
    simdjson
    ${ASSIMP_LIBRARIES}
    tracy
    pthread
    dl
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES} GL)