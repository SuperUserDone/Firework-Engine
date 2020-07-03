#include "core/ActionQueue.hpp"
#include "core/components/ComponentMaterial.hpp"

namespace FW
{
namespace Core
{

ComponentMaterial::ComponentMaterial(const std::string &path) : m_mat(path)
{
    ActionQueue::get_instance().add_top_action(Action::new_action( //
        [this]() { this->load_assets(); },                            //
        [this]() { this->load_ogl(); }));
    
    m_is_loaded = false;
}

/*******************************************************************************/

void ComponentMaterial::load_assets() { m_mat.load_assets(); }

/*******************************************************************************/

void ComponentMaterial::load_ogl()
{
    m_mat.load_ogl();
    m_is_loaded = true;
}

/*******************************************************************************/

void ComponentMaterial::update_data() {}

/*******************************************************************************/

void ComponentMaterial::setup_render() {}

/*******************************************************************************/

void ComponentMaterial::render_forward() const
{
    if (m_is_loaded)
        m_mat.activate();
}

/*******************************************************************************/

void ComponentMaterial::tick() {}

/*******************************************************************************/

ComponentMaterial::~ComponentMaterial() {}

} // namespace Core
} // namespace FW