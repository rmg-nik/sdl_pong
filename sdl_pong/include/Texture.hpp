#pragma once

#include "fwd.hpp"
#include "MemoryBlock.hpp"

struct SDL_Texture;

namespace sdl_pong
{
    class Texture
    {
        friend class Graphics;

    public:

        
        Texture(const Texture&) = delete;

        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) = delete;

        Texture& operator=(Texture&& other) = delete;

        ~Texture();

        SDL_Texture* GetSdlTexture() const;

        int GetWidth() const;

        int GetHeight() const;

    private:

        Texture(SDL_Texture* texture, int w, int h);

    private:

        SDL_Texture* m_texture{ nullptr };

        int m_width{ 0 };

        int m_height{ 0 };
    };
}
