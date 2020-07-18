#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

Object::Object() {}

/*******************************************************************************/

void Object::add_component(ComponentPtr comp)
{
    comp->set_parent(shared_from_this());
    m_components.push_back(comp);
}

/*******************************************************************************/

ComponentPtrVector Object::get_components() { return m_components; }

/*******************************************************************************/

ComponentPtrVector Object::get_components_type(ComponentType type)
{
    ComponentPtrVector temp;

    for (auto &&comp : m_components)
    {
        if (comp->get_type() == type)
            temp.push_back(comp);
    }

    return ComponentPtrVector(temp);
}

/*******************************************************************************/

int Object::get_component_count() { return m_components.size(); }

/*******************************************************************************/

bool Object::is_loaded() const { return m_loaded; }

/*******************************************************************************/

Object::~Object() {}

} // namespace Core
} // namespace FW