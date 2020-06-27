#include "core/ActionQueue.hpp"
#include "core/components/ComponentMesh.hpp"
namespace FW
{
namespace Core
{

/*******************************************************************************/

ComponentMesh::ComponentMesh(std::vector<Render::Vertex> &data,
                             std::vector<uint32_t> &indices)
    : m_renderer(data, indices)
{
    ActionQueue::get_instance().add_top_action(
        Action::new_action(std::bind(&ComponentMesh::load_assets, this),
                           std::bind(&ComponentMesh::load_ogl, this)));
    m_is_loaded = false;
}

/*******************************************************************************/

void ComponentMesh::load_assets() {}

/*******************************************************************************/

void ComponentMesh::load_ogl()
{
    if (!m_is_loaded)
        m_renderer.load_ogl();
    m_is_loaded = true;
}

/*******************************************************************************/

void ComponentMesh::update_data() {}

/*******************************************************************************/

void ComponentMesh::setup_render() {}

/*******************************************************************************/

void ComponentMesh::render_forward() const
{
    if (!m_is_loaded)
        return;
    m_renderer.render_forward();
}

/*******************************************************************************/

void ComponentMesh::tick() {}

/*******************************************************************************/

ComponentMesh::~ComponentMesh() {}

} // namespace Core
} // namespace FW