
#include "core/components/ComponentMesh.hpp"

namespace FW
{
namespace Core
{

ComponentMesh::ComponentMesh() {}

/*******************************************************************************/

void ComponentMesh::load_assets() {}

/*******************************************************************************/

void ComponentMesh::load_ogl() {}

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

void ComponentMesh::render_forward() const {}

/*******************************************************************************/

void ComponentMesh::tick() const {}

/*******************************************************************************/

ComponentMesh::~ComponentMesh() {}

} // namespace Core
} // namespace FW