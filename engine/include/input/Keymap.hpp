#pragma once

#include <atomic>
#include <map>
#include <string>
#include <unordered_map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "input/KeyCodes.hpp"

namespace FW
{
namespace Input
{

class Keymap
{
private:
    std::unordered_map<std::string, KeyCode> m_lookup_table;

public:
    Keymap() {}

    void set_mapping(const std::string &name, KeyCode code); // TODO

    KeyCode get_mapping(const std::string &name); // TODO
};

} // namespace Input
} // namespace FW