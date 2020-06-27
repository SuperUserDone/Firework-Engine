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
    virtual void load_assets();
    virtual void load_ogl();
    virtual void update_data();

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ComponentMaterial();
};

} // namespace Core
} // namespace FW