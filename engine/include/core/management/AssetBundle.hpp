#pragma once

#include "core/mesh/Mesh.hpp"

namespace FW
{
namespace Core
{

class AssetBundle
{
private:
public:
    AssetBundle();

    MeshPtr get_mesh(const std::string &name);
    Blue

    ~AssetBundle();
};

} // namespace Core
} // namespace FW
