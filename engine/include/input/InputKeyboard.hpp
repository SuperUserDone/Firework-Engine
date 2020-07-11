#pragma once

#include <atomic>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "input/Keymap.hpp"

namespace FW
{
namespace Input
{

class InputKeyboard
{
private:
    static inline GLFWwindow *m_window = nullptr;

public:
    static Keymap m_keymap;

    static bool is_key_down(const std::string &mapped_name);
    static bool is_key_down(const KeyCode &code);

    static void set_window(GLFWwindow *window) { m_window = window; }

    static void character_callback(GLFWwindow *window, unsigned int codepoint);
};

} // namespace Input
} // namespace FW