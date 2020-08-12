#include "render/RendererMesh.hpp"

namespace FW
{
namespace Render
{

RendererMesh::RendererMesh() { m_mesh = std::make_shared<Core::Mesh>(); }

RendererMesh::RendererMesh(Core::MeshPtr mesh)
{
    if (!mesh)
        throw std::invalid_argument("Mesh cannot be null");
    m_mesh = mesh;
}

void RendererMesh::set_mesh(Core::MeshPtr mesh)
{
    if (!mesh)
        throw std::invalid_argument("Mesh cannot be null");
    m_mesh = mesh;
}

Core::MeshPtr RendererMesh::get_mesh() { return m_mesh; }

void RendererMesh::update()
{
    if (!m_mesh)
        throw std::invalid_argument("Mesh cannot be null");

    if (m_init)
        return;

    if (m_mesh->is_static() && m_init)
        return;

    Backend::ModelCreateParams params;

    params.asset_context = 0;
    params.mesh = m_mesh.get();

    auto p = RenderServer::get_instance().create_model(params);

    m_id = p.get();
    m_init = true;
}

void RendererMesh::queue_render()
{
    update();

    Backend::DrawCommand cmd;

    cmd.type = Backend::DRAW_COMMAND_MODEL;
    cmd.data.model.model = m_id;
    cmd.data.model.props.material = 0;

    RenderServer::get_instance().add_to_opaque_drawlist(cmd);
}

RendererMesh::~RendererMesh()
{ // TODO destroy in memory
}

} // namespace Render
} // namespace FW