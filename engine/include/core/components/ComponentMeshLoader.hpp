#pragma once

#include <memory>
#include <string>
#include <vector>

#include "core/ActionQueue.hpp"
#include "core/components/Component.hpp"
#include "render/Types.hpp"

namespace FW
{
namespace Core
{

class ComponentMeshLoader : public Component
{
protected:
    std::string m_path;

public:
    ComponentMeshLoader(const std::string &path);

    // Loading
    virtual void load_assets() override;
    virtual void load_ogl() override;
    virtual void update_data() override;

    virtual ComponentType get_type() override { return COMPONENT_MESH_LOADER; }

    // Rendering
    virtual void setup_render() override;
    virtual void render_forward(bool override_shaders) const override;

    // Updating
    virtual void tick() override;

    ~ComponentMeshLoader();
};

} // namespace Core
} // namespace FW