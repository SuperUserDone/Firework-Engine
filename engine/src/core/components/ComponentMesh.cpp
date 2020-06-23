#include "core/components/ComponentMesh.hpp"

namespace FW
{
namespace Core
{

ComponentMesh::ComponentMesh()
    : m_renderer({{{-0.5f, -0.5f, 0.0f}}, //
                  {{0.5f, -0.5f, 0.0f}},  //
                  {{0.0f, 0.5f, 0.0f}}})
{
}

/*******************************************************************************/

void ComponentMesh::load_assets() {}

/*******************************************************************************/

void ComponentMesh::load_ogl()
{
    m_renderer.load_ogl();
    m_is_loaded = true;
}

/*******************************************************************************/

void ComponentMesh::update_data() {}

/*******************************************************************************/

bool ComponentMesh::should_update() const
{
    return !m_is_static && m_is_loaded && m_changed;
}

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

void ComponentMesh::tick() const {}

/*******************************************************************************/

ComponentMesh::~ComponentMesh() {}

} // namespace Core
} // namespace FW