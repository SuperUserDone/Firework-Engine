#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <loguru.hpp>

#include "core/components/ComponentMesh.hpp"
#include "core/components/ComponentMeshLoader.hpp"
#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

ComponentMeshLoader::ComponentMeshLoader(const std::string &path) : m_path(path)
{
    ActionQueue::get_instance().add_top_action(
        Action::new_action(std::bind(&ComponentMeshLoader::load_assets, this),
                           std::bind(&ComponentMeshLoader::load_ogl, this)));
}

/*******************************************************************************/

void ComponentMeshLoader::load_assets()
{
    LOG_F(INFO, "Importing model %s", m_path.c_str());
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( //
        m_path,                               //
        aiProcess_Triangulate |               //
            aiProcess_FlipUVs |               //
            aiProcess_JoinIdenticalVertices | //
            aiProcess_CalcTangentSpace        //
    );

    if (!scene)
    {
        LOG_F(ERROR, "Failed to open model %s / unsupported format",
              m_path.c_str());
        return;
    }

    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh *m_temp_mesh = scene->mMeshes[i];

        std::vector<Render::Vertex> vertices;

        for (int i = 0; i < m_temp_mesh->mNumVertices; i++)
        {
            Render::Vertex vert;

            vert.pos = {m_temp_mesh->mVertices[i].x, //
                        m_temp_mesh->mVertices[i].y, //
                        m_temp_mesh->mVertices[i].z};

            vert.normal = {m_temp_mesh->mNormals[i].x, //
                           m_temp_mesh->mNormals[i].y, //
                           m_temp_mesh->mNormals[i].z};

            vert.tangent = {m_temp_mesh->mTangents[i].x, //
                            m_temp_mesh->mTangents[i].y, //
                            m_temp_mesh->mTangents[i].z};

            vert.bitangent = {m_temp_mesh->mBitangents[i].x, //
                              m_temp_mesh->mBitangents[i].y, //
                              m_temp_mesh->mBitangents[i].z};

            if (m_temp_mesh->mTextureCoords[0])
            {
                vert.uv = {m_temp_mesh->mTextureCoords[0][i].x, //
                           m_temp_mesh->mTextureCoords[0][i].y};
            }
            else
                vert.uv = {0.0f, 0.0f};

            vertices.push_back(vert);
        }

        std::vector<uint32_t> indices;

        for (unsigned int i = 0; i < m_temp_mesh->mNumFaces; i++)
        {
            aiFace face = m_temp_mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        auto temp_comp = std::make_shared<ComponentMesh>(
            std::make_shared<Mesh>(vertices, indices));

        while (!m_parent)
        {
        }
        m_parent->add_component(temp_comp);
    }
    m_is_loaded = true;
}

/*******************************************************************************/

void ComponentMeshLoader::load_ogl() { m_is_loaded = true; }

/*******************************************************************************/

void ComponentMeshLoader::update_data() { m_is_loaded = true; }

/*******************************************************************************/

void ComponentMeshLoader::setup_render() {}

/*******************************************************************************/

void ComponentMeshLoader::render_forward() const {}

/*******************************************************************************/

void ComponentMeshLoader::tick() {}

/*******************************************************************************/

ComponentMeshLoader::~ComponentMeshLoader() {}

} // namespace Core
} // namespace FW