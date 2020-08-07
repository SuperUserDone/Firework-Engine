#pragma once

#include <array>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "concurrentqueue.h"

#include "core/io/AssetBundle.hpp"

namespace FW
{
namespace Core
{

struct LoadCommand
{
    std::string res_path;
    std::shared_ptr<std::promise<std::shared_ptr<std::vector<uint8_t>>>> data;
};

class AssetManager
{
private:
    AssetManager(AssetManager const &) = delete;
    void operator=(AssetManager const &) = delete;

    std::unordered_map<std::string, AssetBundlePtr> m_asset_bundles;
    std::mutex m_asset_bundle_lock;

    AssetBundlePtr &get_bundle_async(const std::string &name);

    void load_worker();

    moodycamel::ConcurrentQueue<LoadCommand> m_worker_queue;

    std::array<std::thread, 2> m_load_workers;

public:
    AssetManager(const std::string &config_path);

    static AssetManager &init(const std::string &config_path)
    {
        static AssetManager instance(config_path);
        return instance;
    }
    static AssetManager &get_instance() { return init(""); }

    void load_bundle(const std::string &name);
    void unload_bundle(const std::string &name);

    std::future<std::shared_ptr<std::vector<uint8_t>>>
    load_data(const std::string &res_path);

    

    ~AssetManager();
};

} // namespace Core
} // namespace FW