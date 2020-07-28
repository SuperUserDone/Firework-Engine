#include "core/io/AssetBundle.hpp"

#include <fstream>

namespace FW
{
namespace Core
{

void AssetBundle::file_loading(uint8_t *data)
{
    if (data == nullptr)
        throw std::invalid_argument(
            "Got null in a internal function! This should not happen.");

    AssetBundleFileHeader header;

    for (size_t i = 4; i < 0x104; i++)
    {
        if ((char)data[i] == '\0')
            break;

        header.name.push_back((char)data[i]);
    }

    memcpy(&header.parent_folder_id, &data[0x104], 4);
    memcpy(&header.block_count, &data[0x108], 4);
    memcpy(&header.compression_magic, &data[0x10C], 4);
    memcpy(&header.uncompressed_byte_size, &data[0x110], 8);
    memcpy(&header.compressed_byte_size, &data[0x118], 8);
}

void AssetBundle::folder_loading(uint8_t *data)
{
    if (data == nullptr)
        throw std::invalid_argument(
            "Got null in a internal function! This should not happen.");
}

void AssetBundle::tree_worker()
{
    std::ifstream file(m_path, std::ios::binary);

    if (!file)
        throw std::runtime_error("Failed to load bundle " + m_path +
                                 "! Invalid path/other");

    file.seekg(0, file.end);
    uint64_t length = file.tellg();
    file.seekg(0, file.beg);

    uint32_t magic = 0;
    file.read((char *)&magic, 4);
    file.read((char *)&m_header.version, 4);
    file.read((char *)&m_header.block_count, 4);

    if (magic != 0x42415746)
        throw std::runtime_error("Failed to load bundle " + m_path +
                                 "! Invalid File Magic");

    file.seekg(512);
    uint64_t block_offset = 1;

    while ((block_offset + 1) * 512 <= length)
    {
        file.seekg(512 * block_offset);

        uint32_t block_magic = 0;
        file.read((char *)&block_magic, 4);

        file.seekg(512 * block_offset);

        uint8_t *data = new uint8_t[512];

        file.read((char *)data, 512);

        switch (block_magic)
        {
        case 0x444c4f46:
            folder_loading(data);
            break;

        case 0x454c4946:
            file_loading(data);
            break;

        default:
            throw std::runtime_error("Invalid magic number in file block");
            break;
        }

        delete[] data;
    }

    m_tree_done = true;
}

AssetBundle::AssetBundle() { m_tree_done = true; }

AssetBundle::AssetBundle(const std::string &path)
{
    m_tree_done = false;
    m_path = path;

    build_dir_tree();
}

void AssetBundle::build_dir_tree()
{
    if (m_tree_worker_thread.joinable())
        m_tree_worker_thread.join();
    m_tree_worker_thread = std::thread(&AssetBundle::tree_worker, this);
}

void AssetBundle::write(const std::string &path) {}

void AssetBundle::load_all() {}

void AssetBundle::add_folder(const std::string &res_path) {}

void AssetBundle::add_file(const std::string &res_path,
                           std::vector<uint8_t> &data)
{
}

void AssetBundle::remove_file(const std::string &res_path) {}

void AssetBundle::remove_folder(const std::string &res_path) {}

std::vector<uint8_t> &AssetBundle::get_file_data(const std::string &res_path,
                                                 bool cache) const
{
}

AssetBundle::~AssetBundle()
{
    if (m_tree_worker_thread.joinable())
        m_tree_worker_thread.join();
}

} // namespace Core
} // namespace FW