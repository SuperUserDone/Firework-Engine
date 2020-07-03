#include "core/ActionQueue.hpp"
#include "render/Material.hpp"

#include <simdjson.h>

namespace FW
{
namespace Render
{

Material::Material(const std::string &mat_path) : m_path(mat_path)
{
    m_loaded = false;
}

/*******************************************************************************/

void Material::load_assets()
{
    simdjson::dom::parser parser;
    simdjson::dom::element dom = parser.load(m_path);
    simdjson::dom::element mat = dom["material"];

    std::string vert(mat["vertex"].get_string().value());
    std::string frag(mat["fragment"].get_string().value());

    m_shader.set_frag(frag);
    m_shader.set_vert(vert);

    Core::ActionQueue &queue = Core::ActionQueue::get_instance();

    m_albedo = std::make_shared<Texture>(
        std::string(mat["textures"]["albedo"].get_string().value()));
    m_normal = std::make_shared<Texture>(
        std::string(mat["textures"]["normal"].get_string().value()));
    m_metalic = std::make_shared<Texture>(
        std::string(mat["textures"]["metalic"].get_string().value()));
    m_roughness = std::make_shared<Texture>(
        std::string(mat["textures"]["roughness"].get_string().value()));

    queue.add_med_action(Core::ActionPtr(new Core::Action( //
        [this]() { this->m_albedo->async_safe_load(); },   //
        [this]() { this->m_albedo->sync_only_load(); })));
        
    queue.add_med_action(Core::ActionPtr(new Core::Action( //
        [this]() { this->m_normal->async_safe_load(); },   //
        [this]() { this->m_normal->sync_only_load(); })));

    queue.add_med_action(Core::ActionPtr(new Core::Action( //
        [this]() { this->m_metalic->async_safe_load(); },   //
        [this]() { this->m_metalic->sync_only_load(); })));

    queue.add_med_action(Core::ActionPtr(new Core::Action( //
        [this]() { this->m_roughness->async_safe_load(); },   //
        [this]() { this->m_roughness->sync_only_load(); })));


}

/*******************************************************************************/

void Material::load_ogl()
{
    if (m_loaded)
        return;
    m_shader.load_ogl();

    m_loaded = true;
}

/*******************************************************************************/

void Material::activate() const
{
    if (!m_loaded)
        return;

    m_shader.activate();
    m_albedo->bind(0);
    m_normal->bind(1);
    m_metalic->bind(2);
    m_roughness->bind(3);
}

/*******************************************************************************/

Material::~Material() {}

} // namespace Render
} // namespace FW