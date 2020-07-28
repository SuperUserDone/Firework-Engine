#pragma once

#include <atomic>
#include <cstring>
#include <filesystem>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace FW
{
namespace Core
{

struct AssetBundleHeader
{
    uint32_t version;
    uint32_t block_count;
};

struct AssetBundleFileHeader
{
    std::string name;
    uint32_t parent_folder_id;
    uint32_t block_count;
    uint32_t compression_magic;
    uint32_t uncompressed_byte_size;
    uint32_t compressed_byte_size;

    uint64_t file_offset_start;

    std::vector<uint8_t> m_data;
};

struct AssetBundleFolderHeader
{
    std::string name;
    uint32_t folder_id;
    uint32_t parent_id;

    std::unordered_map<std::string, AssetBundleFileHeader *> files;
    std::unordered_map<std::string, AssetBundleFolderHeader *> folders;
};

class AssetBundle
{
private:
    std::unordered_map<uint32_t, AssetBundleFolderHeader *> m_folders;

    AssetBundleFolderHeader m_root;
    AssetBundleHeader m_header;

    std::thread m_tree_worker_thread;

    std::atomic_bool m_tree_done;

    void file_loading(uint8_t *data);
    void folder_loading(uint8_t *data);

    void tree_worker();

    std::string m_path;

public:
    AssetBundle();
    AssetBundle(const std::string &path);

    void build_dir_tree();
    void write(const std::string &path);

    void load_all();

    void add_folder(const std::string &res_path);
    void add_file(const std::string &res_path, std::vector<uint8_t> &data);

    void remove_folder(const std::string &res_path);
    void remove_file(const std::string &res_path);

    std::vector<uint8_t> &get_file_data(const std::string &res_path,
                                        bool cache = false) const;

    ~AssetBundle();
};

} // namespace Core
} // namespace FW