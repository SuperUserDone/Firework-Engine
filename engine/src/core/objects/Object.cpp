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

bool Object::is_loaded() const { return m_loaded; }

/*******************************************************************************/

Object::~Object() {}

} // namespace Core
} // namespace FW