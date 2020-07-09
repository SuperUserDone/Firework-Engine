#pragma once

#include <functional>
#include <memory>

#include "core/components/Component.hpp"
#include "render/Material.hpp"
#include "render/Types.hpp"

namespace FW
{
namespace Core
{

class ComponentMaterial : public Component,
                          public std::enable_shared_from_this<ComponentMaterial>
{
protected:
    Render::Material m_mat;

public:
    ComponentMaterial(const std::string &path);

    // Loading
    virtual void load_assets() override;
    virtual void load_ogl() override;
    virtual void update_data() override;

    virtual ComponentType get_type() override { return COMPONENT_MATERIAL; }

    // Rendering
    virtual void setup_render() override;
    virtual void render_forward(bool override_shaders) const override;

    // Updating
    virtual void tick() override;

    ~ComponentMaterial();
};

} // namespace Core
} // namespace FW