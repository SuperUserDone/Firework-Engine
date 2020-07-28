#pragma once

#include <future>
#include <string>
#include <vector>

namespace FW
{
namespace Core
{

class AssetManager
{
private:
    AssetManager(AssetManager const &) = delete;
    void operator=(AssetManager const &) = delete;

public:
    AssetManager();

    static AssetManager &get_instance()
    {
        static AssetManager instance;
        return instance;
    }

    void mount_bundle(const std::string &name);

    std::future<std::vector<uint8_t>>
    load_data(const std::string &res_path) const;

    ~AssetManager();
};

} // namespace Core
} // namespace FW