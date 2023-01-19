#include "Texture.hpp"

#include <stdexcept>
#include <cassert>

#include <SDL.h>


using namespace sdl_pong;

Texture::Texture(SDL_Texture* texture, int w, int h)
    : m_texture{ texture }
    , m_width{ w }
    , m_height{ h }
{
    assert(m_texture);
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

SDL_Texture* Texture::GetSdlTexture() const
{
    return m_texture;
}

int Texture::GetWidth() const
{
    return m_width;
}

int Texture::GetHeight() const
{
    return m_height;
}
