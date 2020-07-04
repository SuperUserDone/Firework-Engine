#pragma once

#include <GLFW/glfw3.h>

namespace FW
{
namespace Core
{

inline double get_time() { return glfwGetTime(); }
inline void reset_time() { glfwSetTime(0.0); }

} // namespace Core
} // namespace FW
