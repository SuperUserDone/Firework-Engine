#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/Action.hpp"
#include "core/components/Component.hpp"
#include "core/components/ComponentTransform.hpp"
#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

class ObjectCamera : public Object
{
protected:
    glm::mat4 m_projection;

    uint m_camera_buffer;

    std::shared_ptr<ComponentTransform> m_transform;

    int last_x = 0;
    int last_y = 0;

    std::atomic_bool m_ready;

public:
    ObjectCamera();

    // Loading
    virtual void load_assets() override;
    virtual void load_ogl() override;
    virtual void unload() override;

    // Special transforms
    virtual void look_at(const glm::vec3 &target);

    // Component
    virtual void add_component(std::shared_ptr<Component> comp);

    // Rendering
    virtual void setup_render() override;
    virtual void render_forward(bool override_shaders) const override;

    // Updating
    virtual void tick() override;

    ~ObjectCamera();
};

} // namespace Core
} // namespace FW