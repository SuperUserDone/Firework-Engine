#include "core/components/Component.hpp"

namespace FW
{
namespace Core
{

Component::Component() {}

/*******************************************************************************/

bool Component::is_loaded() const { return m_is_loaded; }

/*******************************************************************************/

Component::~Component() {}

} // namespace Core
} // namespace FW