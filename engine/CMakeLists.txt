set(FIREWORK_SOURCE
"../glad/src/glad.c"
"../loguru/loguru.cpp"
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
"src/input/InputKeyboard.cpp"
"src/input/InputMouse.cpp"
"src/input/InputWindow.cpp"
"src/input/Keymap.cpp"
"src/io/binary/BinaryBuffer.cpp"
"src/render/CubeMap.cpp"
"src/render/Framebuffer.cpp"
"src/render/Material.cpp"
"src/render/MeshRenderer.cpp"
"src/render/Renderer.cpp"
"src/render/RenderPass.cpp"
"src/render/Shader.cpp"
"src/render/Texture.cpp"
"src/scripting/lua/LuaState.cpp"
"src/scripting/lua/LuaScript.cpp"
"src/ui/ImguiData.cpp"
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