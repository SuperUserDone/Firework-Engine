#include <algorithm>

#include "core/objects/ObjectBasic.hpp"

namespace FW
{
namespace Core
{

void ObjectBasic::load_assets() {}

/*******************************************************************************/

void ObjectBasic::load_ogl()
{
    std::for_each(std::begin(m_components), std::end(m_components),
                  [](std::shared_ptr<Component> comp) { comp->load_ogl(); });
    m_loaded = true;
}

/*******************************************************************************/

void ObjectBasic::unload() {}

/*******************************************************************************/

ObjectBasic::ObjectBasic() {}

/*******************************************************************************/

Action ObjectBasic::get_load_action()
{
    return Action(std::bind(&ObjectBasic::load_assets, this),
                  std::bind(&ObjectBasic::load_ogl, this));
}

/*******************************************************************************/

Action ObjectBasic::get_unload_action() {}

/*******************************************************************************/

Action ObjectBasic::get_update_action() {}

/*******************************************************************************/

bool ObjectBasic::should_gpu_update() const
{
    return m_loaded && !m_is_static && m_changed;
}

/*******************************************************************************/

void ObjectBasic::setup_render() {}

/*******************************************************************************/

void ObjectBasic::render_forward() const
{
    std::for_each(
        std::begin(m_components), std::end(m_components),
        [](std::shared_ptr<Component> comp) { comp->render_forward(); });
}

/*******************************************************************************/

void ObjectBasic::tick() {}

/*******************************************************************************/

ObjectBasic::~ObjectBasic() {}

} // namespace Core
} // namespace FW