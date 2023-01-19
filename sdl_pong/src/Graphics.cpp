#include "Graphics.hpp"
#include "Texture.hpp"
#include "constants.hpp"

#include <stdexcept>
#include <format>
#include <cassert>

#include <SDL.h>
#include <SDL_image.h>


using namespace sdl_pong;

Graphics::~Graphics()
{
    Close();
}

void Graphics::Init()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(
            std::format("Graphics.Init: cannot init video '{}'", SDL_GetError()));

    m_window = SDL_CreateWindow("SDL PONG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, 0);

    if (!m_window)
        throw std::runtime_error(
            std::format("Graphics.Init: cannot create window '{}'", SDL_GetError()));

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
        throw std::runtime_error(
            std::format("Graphics.Init: cannot create renderer '{}'", SDL_GetError()));

    SDL_RenderSetLogicalSize(m_renderer, WORLD_WIDTH, WORLD_HEIGHT);
}

void Graphics::Close()
{
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;

    if (m_window)
        SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

void Graphics::PrepareFrame()
{
    SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255);
    SDL_RenderClear(m_renderer);
}

void Graphics::Draw(const TexturePtr& texture, const Bounds& dst)
{
    auto sdl_texture = texture->GetSdlTexture();
    SDL_FRect sdl_rect{ dst.pos.x, dst.pos.y, dst.size.w, dst.size.h };
    if (SDL_RenderCopyExF(m_renderer, sdl_texture, nullptr, &sdl_rect, 0.0, nullptr, SDL_FLIP_NONE) < 0)
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Graphics.Draw: %s", SDL_GetError());
}

void Graphics::Flush()
{
    SDL_RenderPresent(m_renderer);
}

TexturePtr Graphics::CreateTexture(MemoryBlock memory_block)
{
    assert(memory_block.GetData());

    TexturePtr ret{ nullptr };
    SDL_Surface* sfc{ nullptr };
    try
    {
        SDL_RWops* rwops = SDL_RWFromConstMem(memory_block.GetData(), static_cast<int>(memory_block.GetLength()));
        if (!rwops)
            throw std::runtime_error(std::string("Graphics.CreateTexture: ") + SDL_GetError());

        sfc = IMG_Load_RW(rwops, 1);
        if (!sfc)
            throw std::runtime_error(std::string("Graphics.CreateTexture: ") + SDL_GetError());

        auto texture = SDL_CreateTextureFromSurface(m_renderer, sfc);
        if (!texture)
            throw std::runtime_error(std::string("Graphics.CreateTexture: ") + SDL_GetError());

        ret.reset(new Texture(texture, sfc->w, sfc->h));

        SDL_FreeSurface(sfc);
    }
    catch (...)
    {
        if (sfc)
            SDL_FreeSurface(sfc);
        throw;
    }

    return ret;
}

TexturePtr Graphics::CreateTexture(SDL_Surface* sfc)
{
    assert(sfc);

    TexturePtr ret{ nullptr };
    auto texture = SDL_CreateTextureFromSurface(m_renderer, sfc);
    if (!texture)
        throw std::runtime_error(std::string("Graphics.CreateTexture: ") + SDL_GetError());

    ret.reset(new Texture(texture, sfc->w, sfc->h));
    return ret;
}
