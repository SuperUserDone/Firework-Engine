set(FIREWORK_SOURCE
"../glad/src/glad.c"
"../loguru/loguru.cpp"
"src/core/io/AssetBundle.cpp"
"src/core/manager/AssetManager.cpp"
"src/core/manager/SceneManager.cpp"
"src/core/misc/Material.cpp"
"src/core/misc/Mesh.cpp"
"src/core/misc/Texture.cpp"
"src/core/objects/components/Component.cpp"
"src/core/objects/components/ComponentRenderer.hpp"
"src/core/objects/components/ComponentScript.hpp"
"src/core/objects/Camera.cpp"
"src/core/objects/Object.cpp"
"src/core/Scene.cpp"
"src/input/InputKeyboard.cpp"
"src/input/InputMouse.cpp"
"src/input/InputWindow.cpp"
"src/render/RendererMesh.cpp"
"src/render/RenderServer.cpp"
"src/render/ogl/RenderDummy.cpp"
"src/render/ogl/RenderOpengl.cpp"
"src/window/Window.cpp"
)

set(FIREWORK_LIBRARIES
    ${FREETYPE_LIBRARIES}
    ${PLATFORM_LIBRARIES}
    ${ASSIMP_LIBRARIES}
    glfw
    simdjson
    tracy
    GL
)

add_library(FireworkEngine SHARED ${FIREWORK_SOURCE})
target_link_libraries(FireworkEngine ${FIREWORK_LIBRARIES})