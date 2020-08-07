#include "core/manager/AssetManager.hpp"

#include <simdjson.h>

// TODO document

namespace FW
{
namespace Core
{

AssetManager::AssetManager(const std::string &config_path)
{
    simdjson::dom::parser json_parser;
    simdjson::dom::element json_dom = json_parser.load(config_path);

    for (auto &&bundle : json_dom["bundles"])
    {
        std::string name = std::string(bundle["name"]);
        bool cache = false;
        bool debug = bundle["debug"];

        std::string debug_prefix = "";
        std::string debug_path = name;
        if (debug)
        {
            debug_prefix = std::string(bundle["debug_prefix"]);
            debug_path = std::string(bundle["debug_path"]);
            m_asset_bundles[name] =
                std::make_shared<AssetBundle>(debug_path, debug_prefix);
        }
        else
        {
            m_asset_bundles[name] = std::make_shared<AssetBundle>(name);
        }
    }
}

AssetBundlePtr &AssetManager::get_bundle_async(const std::string &name)
{
    std::lock_guard<std::mutex> lock(m_asset_bundle_lock);

    return m_asset_bundles[name];
}

void AssetManager::load_worker()
{
    LoadCommand cmd;
    while (m_worker_queue.try_dequeue(cmd))
    {
        std::string core = cmd.res_path.substr(0, cmd.res_path.find(":"));

        if (core == "")
            throw std::invalid_argument("Core name invalid");

        cmd.data->set_value(
            get_bundle_async(core)->get_file_data(cmd.res_path));
    }
}

void AssetManager::load_bundle(const std::string &name) {}

void AssetManager::unload_bundle(const std::string &name) {}

std::future<std::shared_ptr<std::vector<uint8_t>>>
AssetManager::load_data(const std::string &res_path)
{
    LoadCommand cmd;
    cmd.data =
        std::make_shared<std::promise<std::shared_ptr<std::vector<uint8_t>>>>();
    cmd.res_path = res_path;

    m_worker_queue.enqueue(cmd);

    for (auto &&worker : m_load_workers)
    {
        if (!worker.joinable())
        {
            worker = std::thread(&AssetManager::load_worker, this);
            break;
        }
    }

    return cmd.data->get_future();
}

AssetManager::~AssetManager()
{
    for (auto &&worker : m_load_workers)
    {
        if (worker.joinable())
            worker.join();
    }
}

} // namespace  Core
} // namespace FW