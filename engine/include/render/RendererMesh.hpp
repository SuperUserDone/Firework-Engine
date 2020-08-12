#pragma once

#include <exception>
#include <stdexcept>

#include "core/misc/Mesh.hpp"
#include "render/RenderServer.hpp"
#include "render/Renderer.hpp"

namespace FW
{
namespace Render
{

// TODO Refactor

class RendererMesh : public Renderer
{
private:
    int m_id = 0;
    int m_context = 0;

    Core::MeshPtr m_mesh;

    bool m_init = false;

public:
    RendererMesh();
    RendererMesh(Core::MeshPtr mesh);

    virtual void set_mesh(Core::MeshPtr mesh);
    virtual Core::MeshPtr get_mesh();

    virtual void update() override;

    virtual void queue_render() override;

    ~RendererMesh();
};

} // namespace Render
} // namespace FW