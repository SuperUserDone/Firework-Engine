#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Action.hpp"
#include "core/components/Component.hpp"
#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

class ObjectCamera : public Object
{
protected:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    uint m_camera_buffer;

    int last_x = 0;
    int last_y = 0;

public:
    ObjectCamera();

    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void unload();

    // Component
    virtual void add_component(std::shared_ptr<Component> comp);

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ObjectCamera();
};

} // namespace Core
} // namespace FW