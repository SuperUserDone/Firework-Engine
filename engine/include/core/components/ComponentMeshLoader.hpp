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
    virtual void load_assets();
    virtual void load_ogl();
    virtual void update_data();

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick() const;

    ~ComponentMeshLoader();
};

} // namespace Core
} // namespace FW