#include "io/binary/BinaryBuffer.hpp"

#include <cstring>

namespace FW
{
namespace IO
{

/*******************************************************************************/

BinaryBuffer::BinaryBuffer() {}

/*******************************************************************************/

BinaryBuffer::BinaryBuffer(const std::string &path) { load_from_file(path); }

/*******************************************************************************/

BinaryBuffer::BinaryBuffer(const std::vector<uint8_t> &data) : m_data(data) {}

/*******************************************************************************/

bool BinaryBuffer::load_from_file(const std::string &path) { return true; }

/*******************************************************************************/

bool BinaryBuffer::save_to_file(const std::string &path) { return true; }

/*******************************************************************************/

void BinaryBuffer::resize(int size) { m_data.resize(size); }

/*******************************************************************************/

template <typename T>
void BinaryBuffer::set(uint32_t offset, const T &value)
{
    if (offset + sizeof(value) > m_data.size())
        offset = m_data.size() - sizeof(value);

    memcpy(&m_data[offset], &value, sizeof(value));
}

/*******************************************************************************/

template <typename T>
void BinaryBuffer::get(uint32_t offset, int size, T &value)
{
    if (offset + size > m_data.size())
        m_data.resize(offset + size);

    memcpy(&value, &m_data[offset], size);
}

/*******************************************************************************/

void BinaryBuffer::set_buffer(uint32_t offset, const std::vector<uint8_t> &buf)
{
    if (offset + buf.size() > m_data.size())
        m_data.resize(offset + buf.size());

    memcpy(&m_data[offset], &buf[0], buf.size());
}

/*******************************************************************************/

void BinaryBuffer::set_buffer(uint32_t offset, BinaryBufferPtr buf) {}

/*******************************************************************************/

void BinaryBuffer::set_string(uint32_t offset, const std::string &str) {}

/*******************************************************************************/

std::vector<uint8_t> BinaryBuffer::get_buffer(uint32_t offset, int len)
{
    return std::vector<uint8_t>();
}

/*******************************************************************************/

BinaryBufferPtr BinaryBuffer::get_binary_buffer(uint32_t offset, int len)
{
    return BinaryBufferPtr(nullptr);
}

/*******************************************************************************/

std::string BinaryBuffer::get_string(uint32_t offset, int maxlen) { return ""; }

/*******************************************************************************/

uint8_t &BinaryBuffer::operator[](size_t index) { return m_data[index]; }

/*******************************************************************************/

const uint8_t &BinaryBuffer::operator[](size_t index) const
{
    return m_data[index];
}

/*******************************************************************************/

BinaryBuffer::~BinaryBuffer() {}

} // namespace IO
} // namespace FW