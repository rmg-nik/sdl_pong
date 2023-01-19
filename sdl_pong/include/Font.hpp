#pragma once

#include "fwd.hpp"
#include "MemoryBlock.hpp"
#include "Color.hpp"

#include <string_view>
#include <cstdint>

namespace sdl_pong
{
    class Font
    {
    public:

        Font(MemoryBlock memory_block, int size, GraphicsWeakPtr graphics);

        Font(const Font&) = delete;

        Font& operator=(const Font&) = delete;

        ~Font();

        TexturePtr RenderText(std::string_view text, Color color);

    private:

        MemoryBlock m_font_data;

        void* m_font{ nullptr };

        GraphicsWeakPtr m_graphics;
    };
}
