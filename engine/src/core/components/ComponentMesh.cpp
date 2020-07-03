#include "core/ActionQueue.hpp"
#include "core/components/ComponentMesh.hpp"
namespace FW
{
namespace Core
{

/*******************************************************************************/

ComponentMesh::ComponentMesh(MeshPtr mesh) : m_renderer(mesh)
{
    ActionQueue::get_instance().add_top_action(Action::new_action( //
        [this]() { this->load_assets(); },                            //
        [this]() { this->load_ogl(); }));

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