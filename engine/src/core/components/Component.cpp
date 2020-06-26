#include "core/components/Component.hpp"
#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

Component::Component() {}

/*******************************************************************************/

void Component::set_parent(std::shared_ptr<Object> obj) { m_parent = obj; }

/*******************************************************************************/

bool Component::is_loaded() const { return m_is_loaded; }

/*******************************************************************************/

Component::~Component() {}

} // namespace Core
} // namespace FW