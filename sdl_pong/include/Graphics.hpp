#pragma once

#include "fwd.hpp"
#include "MemoryBlock.hpp"
#include "geometry.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

namespace sdl_pong
{
    class Graphics
    {
    public:

        Graphics() = default;

        Graphics(const Graphics&) = delete;

        Graphics& operator=(const Graphics&) = delete;

        ~Graphics();

        void Init();

        void Close();

        void PrepareFrame();

        void Draw(const TexturePtr& texture, const Bounds& dst);

        void Flush();

        TexturePtr CreateTexture(MemoryBlock memory_block);

        TexturePtr CreateTexture(SDL_Surface* sfc);

    private:

        SDL_Window*     m_window{ nullptr };
        SDL_Renderer*   m_renderer{ nullptr };

    };
}
