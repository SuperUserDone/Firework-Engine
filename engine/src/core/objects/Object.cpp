#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

Object::Object() {}

bool Object::is_loaded() const { return m_loaded; }

Object::~Object() {}

} // namespace Core
} // namespace FW