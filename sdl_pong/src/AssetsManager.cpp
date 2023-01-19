#include "AssetsManager.hpp"
#include "MemoryBlock.hpp"
#include "Graphics.hpp"
#include "Texture.hpp"
#include "Graphics.hpp"
#include "Sound.hpp"
#include "Font.hpp"

#include <stdexcept>
#include <format>

#include <SDL.h>

using namespace sdl_pong;

namespace
{
    MemoryBlock get_memory_block_from_file(const std::string& name, const std::string& log_tag)
    {
        auto fullname = "assets/" + name;
        auto rwops = SDL_RWFromFile(fullname.c_str(), "r");
        if (!rwops)
            throw std::runtime_error(
                std::format("{} error: {}", log_tag, SDL_GetError())
            );

        auto size = SDL_RWsize(rwops);
        MemoryBlock memory_block(static_cast<std::size_t>(size));
        auto read_size = static_cast<decltype(size)>(SDL_RWread(rwops, memory_block.GetData(), 1, size));
        if (read_size != size)
            throw std::runtime_error(
                std::format("{} error: {}", log_tag, SDL_GetError())
            );

        return memory_block;
    }

}
TexturePtr AssetsManager::GetTexture(const std::string& name)
{
    auto graphics = m_graphics.lock();
    if (!graphics)
        throw std::runtime_error("AssetsManager.GetTexture: graphics is not valid");

    auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        auto memory_block = get_memory_block_from_file(name, "AssetsManager.GetTexture");
        auto texture = graphics->CreateTexture(std::move(memory_block));
        it = m_textures.insert({ name, texture }).first;
    }
    return it->second;
}

SoundPtr AssetsManager::GetSound(const std::string& name)
{
    auto it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        auto memory_block = get_memory_block_from_file(name, "AssetsManager.GetSound");
        SoundPtr sound(new Sound(std::move(memory_block)));
        it = m_sounds.insert({ name, sound }).first;
    }
    return it->second;
}

FontPtr AssetsManager::GetFont(const std::string& name, int size)
{
    auto it = m_fonts.find(std::pair{ name, size });
    if (it == m_fonts.end())
    {
        auto memory_block = get_memory_block_from_file(name, "AssetsManager.GetFont");
        FontPtr font(new Font(std::move(memory_block), size, m_graphics));
        it = m_fonts.insert({ std::pair{ name, size }, font }).first;
    }
    return it->second;
}

void AssetsManager::SetGraphics(GraphicsPtr graphics)
{
    m_graphics = std::move(graphics);
}
