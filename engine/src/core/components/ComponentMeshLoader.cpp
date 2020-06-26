#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( //
        m_path,                               //
        aiProcess_Triangulate |               //
            aiProcess_FlipUVs |               //
            aiProcess_JoinIdenticalVertices | //
            aiProcess_OptimizeMeshes |        //
            aiProcess_GenNormals              //
    );

    if (!scene)
    {
        return;
    }

    aiMesh *Mesh1 = scene->mMeshes[0];

    std::vector<Render::Vertex> vertices;

    for (int i = 0; i < Mesh1->mNumVertices; i++)
    {
        Render::Vertex vert;

        vert.pos = {Mesh1->mVertices[i].x, //
                    Mesh1->mVertices[i].y, //
                    Mesh1->mVertices[i].z};

        vert.normal = {Mesh1->mNormals[i].x, //
                       Mesh1->mNormals[i].y, //
                       Mesh1->mNormals[i].z};

        if (Mesh1->mTextureCoords[0])
        {
            vert.uv = {Mesh1->mTextureCoords[0][i].x, //
                       Mesh1->mTextureCoords[0][i].y};
        }
        else
            vert.uv = {0.0f, 0.0f};

        vertices.push_back(vert);
    }

    std::vector<uint32_t> indices;

    for (unsigned int i = 0; i < Mesh1->mNumFaces; i++)
    {
        aiFace face = Mesh1->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    auto temp_comp = std::make_shared<ComponentMesh>(vertices, indices);
    m_parent->add_component(temp_comp);
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

void ComponentMeshLoader::tick() const {}

/*******************************************************************************/

ComponentMeshLoader::~ComponentMeshLoader() {}

} // namespace Core
} // namespace FW