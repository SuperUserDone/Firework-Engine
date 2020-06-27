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
}

/*******************************************************************************/

void Material::load_ogl()
{
    if (!m_loaded)
        m_shader.load_ogl();

    m_loaded = true;
}

/*******************************************************************************/

void Material::activate() const
{
    if (m_loaded)
        m_shader.activate();
}

/*******************************************************************************/

Material::~Material() {}

} // namespace Render
} // namespace FW