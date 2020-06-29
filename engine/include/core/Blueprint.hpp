#pragma once

#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

class Blueprint
{
private:
public:
    Blueprint();

    ObjectPtr get_instance();

    ~Blueprint();
};

} // namespace Core
} // namespace FW
