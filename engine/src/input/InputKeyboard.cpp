#include "input/InputKeyboard.hpp"

namespace FW
{
namespace Input
{

bool InputKeyboard::is_key_down(const KeyCode &code)
{
    if (!m_window)
        return false;

    if (glfwGetKey(m_window, code))
        return true;

    return false;
}

bool InputKeyboard::is_key_down(const std::string &mapped_name)
{
    return false;
}

void InputKeyboard::key_callback(GLFWwindow *window, int key, int scancode,
                                 int action, int mods)
{
}

void InputKeyboard::character_callback(GLFWwindow *window,
                                       unsigned int codepoint)
{
}

} // namespace Input
} // namespace FW