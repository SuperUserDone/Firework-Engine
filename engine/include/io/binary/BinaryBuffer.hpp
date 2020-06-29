#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace FW
{
namespace IO
{

class BinaryBuffer;
typedef std::shared_ptr<BinaryBuffer> BinaryBufferPtr;

class BinaryBuffer
{
private:
    std::mutex m_lock;

    std::vector<uint8_t> m_data;

    template <typename T>
    void set(uint32_t offset, const T &value);
    template <typename T>
    void get(uint32_t offset, int size, T &value);

public:
    BinaryBuffer();
    BinaryBuffer(const std::vector<uint8_t> &data);
    BinaryBuffer(const std::string &path);

    bool load_from_file(const std::string &path);
    bool save_to_file(const std::string &path);

    void resize(int size);

    void set_buffer(uint32_t offset, const std::vector<uint8_t> &buf);
    void set_buffer(uint32_t offset, BinaryBufferPtr buf);
    void set_string(uint32_t offset, const std::string &str);

    std::vector<uint8_t> get_buffer(uint32_t offset, int len);
    BinaryBufferPtr get_binary_buffer(uint32_t offset, int len);
    std::string get_string(uint32_t offset, int maxlen = 32);

    uint8_t &operator[](size_t index);
    const uint8_t &operator[](size_t index) const;

    ~BinaryBuffer();
};

} // namespace IO
} // namespace FW
