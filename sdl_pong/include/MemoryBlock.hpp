#pragma once

#include <cstddef>
#include <utility>

namespace sdl_pong
{
    class MemoryBlock
    {
    public:

        MemoryBlock(std::size_t length)
            : m_data{ new  std::byte[length]}
            , m_length{ length }
        {

        }

        MemoryBlock(std::byte* data = nullptr, std::size_t length = 0)
            : m_data{ data }
            , m_length{ length }
        {

        }

        MemoryBlock(MemoryBlock&& other) noexcept
            : m_data{ nullptr }
            , m_length{ 0 }
        {
            *this = std::move(other);
        }

        MemoryBlock& operator= (MemoryBlock&& other) noexcept
        {
            if (this != &other)
            {
                delete[] m_data;
                m_data = other.m_data;
                m_length = other.m_length;

                other.m_data = nullptr;
                other.m_length = 0;
            }
            return *this;
        }

        MemoryBlock(const MemoryBlock&) = delete;

        MemoryBlock& operator=(const MemoryBlock&) = delete;

        ~MemoryBlock()
        {
            delete[] m_data;
        }

        std::byte* GetData() const { return m_data; }

        std::size_t GetLength() const { return m_length; }

    private:

        std::byte* m_data{ nullptr };

        std::size_t m_length{ 0 };
    };
}
