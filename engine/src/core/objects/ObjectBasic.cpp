#include <algorithm>

#include "core/ActionQueue.hpp"
#include "core/objects/ObjectBasic.hpp"

namespace FW
{
namespace Core
{

void ObjectBasic::load_assets() {}

/*******************************************************************************/

void ObjectBasic::load_ogl() { m_loaded = true; }

/*******************************************************************************/

void ObjectBasic::unload() {}

/*******************************************************************************/

ObjectBasic::ObjectBasic() {}

/*******************************************************************************/

void ObjectBasic::setup_render() {}

/*******************************************************************************/

void ObjectBasic::render_forward() const
{
    std::for_each(std::begin(m_components), std::end(m_components),
                  [](std::shared_ptr<Component> comp) {
                      comp->setup_render();
                      comp->render_forward();
                  });
}

/*******************************************************************************/

void ObjectBasic::tick() {}

/*******************************************************************************/

ObjectBasic::~ObjectBasic() {}

} // namespace Core
} // namespace FW