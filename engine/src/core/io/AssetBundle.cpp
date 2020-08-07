#include "core/io/AssetBundle.hpp"

#include <fstream>

#include <simdjson.h>


// TODO comment
namespace FW
{
namespace Core
{

void AssetBundle::file_loading(uint8_t *data)
{
    if (data == nullptr)
        throw std::invalid_argument(
            "Got null in a internal function! This should not happen.");
}

void AssetBundle::folder_loading(uint8_t *data)
{
    if (data == nullptr)
        throw std::invalid_argument(
            "Got null in a internal function! This should not happen.");
}

void AssetBundle::tree_worker()
{
    if (m_debug)
    {
        simdjson::dom::parser json_parser;
        simdjson::dom::element json_dom = json_parser.load(m_path);

        for (auto &&i : json_dom["build"])
        {
            m_debug_lookup[std::string(i["final"])] =
                m_debug_base + std::string(i["disk"]);
        }

        m_tree_done = true;
        return;
    }
    else
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
                throw std::runtime_error("Invalid magic number in block");
                break;
            }

            delete[] data;
        }
        m_tree_done = true;
    }
}

AssetBundle::AssetBundle() { m_tree_done = true; }

AssetBundle::AssetBundle(const std::string &path)
{
    m_tree_done = false;
    m_path = path;

    m_debug_base = "";

    m_debug = false;

    build_dir_tree();
}

AssetBundle::AssetBundle(const std::string &path, const std::string &debug_base)
{
    m_tree_done = false;
    m_path = path;

    m_debug_base = debug_base;

    m_debug = true;

    build_dir_tree();
}

void AssetBundle::build_dir_tree()
{
    if (m_tree_worker_thread.joinable())
        m_tree_worker_thread.join();
    m_tree_worker_thread = std::thread(&AssetBundle::tree_worker, this);
    m_tree_worker_thread.join();
}

void AssetBundle::write(const std::string &path) { load_all(); }

void AssetBundle::load_all() {}

void AssetBundle::unload_all() {}

std::shared_ptr<std::vector<uint8_t>>
AssetBundle::get_file_data(const std::string &res_path, bool cache) const
{
    if (m_tree_worker_thread.joinable())
        m_tree_worker_thread.join();

    if (m_debug)
    {
        std::string mod_path = res_path;
        mod_path = mod_path.erase(0, mod_path.find("://") + 3);

        std::ifstream file(m_debug_lookup[mod_path], std::ios::binary);

        file.seekg(0, file.end);
        uint64_t length = file.tellg();
        file.seekg(0, file.beg);

        std::shared_ptr<std::vector<uint8_t>> file_data =
            std::make_shared<std::vector<uint8_t>>();

        file_data->resize(length);

        file.read((char *)file_data->data(), length);
        return file_data;
    }
    else
        return std::make_shared<std::vector<uint8_t>>();
}

AssetBundle::~AssetBundle()
{
    if (m_tree_worker_thread.joinable())
        m_tree_worker_thread.join();

    unload_all();
}

} // namespace Core
} // namespace FW