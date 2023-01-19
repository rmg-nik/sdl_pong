#include "Font.hpp"
#include "Graphics.hpp"

#include <stdexcept>

#include <SDL_ttf.h>
#include <SDL.h>

using namespace sdl_pong;

Font::Font(MemoryBlock memory_block, int size, GraphicsWeakPtr graphics)
    : m_font_data(std::move(memory_block))
    , m_graphics{ graphics }
{
    SDL_RWops* rwops = SDL_RWFromConstMem(m_font_data.GetData(), static_cast<int>(m_font_data.GetLength()));
    if (!rwops)
        throw std::runtime_error(std::string("Font.Font: ") + SDL_GetError());

    m_font = TTF_OpenFontRW(rwops, 1, size);
    if (!m_font)
        throw std::runtime_error(std::string("Font.Font: ") + TTF_GetError());
}

Font::~Font()
{
    TTF_CloseFont((TTF_Font*)m_font);
}

TexturePtr Font::RenderText(std::string_view text, Color color)
{
    auto graphics = m_graphics.lock();
    if (!graphics)
        throw std::runtime_error("Font.RenderText: graphics is not valid");

    auto sfc = TTF_RenderText_Blended((TTF_Font*)m_font, text.data(), { color.r, color.g, color.b, color.a });
    if (!sfc)
        throw std::runtime_error(std::string("Font.RenderText: ") + TTF_GetError());

    TexturePtr ret;
    try
    {
        ret = graphics->CreateTexture(sfc);
        SDL_FreeSurface(sfc);
    }
    catch (...)
    {
        SDL_FreeSurface(sfc);
        throw;
    }
    
    return ret;
}
