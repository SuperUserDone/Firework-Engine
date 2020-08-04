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

class AssetBundle;

typedef std::shared_ptr<AssetBundle> AssetBundlePtr;

class AssetBundle
{
private:
    mutable std::thread m_tree_worker_thread;

    std::atomic_bool m_tree_done;

    mutable std::unordered_map<std::string, std::string> m_debug_lookup;

    void file_loading(uint8_t *data);
    void folder_loading(uint8_t *data);

    void tree_worker();

    std::string m_path;
    std::string m_debug_base;

    bool m_debug = false;

public:
    AssetBundle();
    AssetBundle(const std::string &path);
    AssetBundle(const std::string &path, const std::string &debug_base);

    void build_dir_tree();
    void write(const std::string &path);

    void load_all();
    void unload_all();

    std::vector<uint8_t> get_file_data(const std::string &res_path,
                                       bool cache = false) const;

    ~AssetBundle();
};

} // namespace Core
} // namespace FW