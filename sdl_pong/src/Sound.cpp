#include "Sound.hpp"

#include <stdexcept>

#include <SDL.h>
#include <SDL_mixer.h>

using namespace sdl_pong;

Sound::Sound(MemoryBlock memory_block)
{
    SDL_RWops* rwops = SDL_RWFromConstMem(memory_block.GetData(), static_cast<int>(memory_block.GetLength()));
    if (!rwops)
        throw std::runtime_error(std::string("Sound.Sound: ") + SDL_GetError());

    m_chunk = Mix_LoadWAV_RW(rwops, 1);
    if (!m_chunk)
        throw std::runtime_error(std::string("Sound.Sound: ") + SDL_GetError());
}

Sound::~Sound()
{
    Stop();
    Mix_FreeChunk(m_chunk);
}

void Sound::Play(int loops)
{
    static int current_channel = 0;
    m_current_channel = current_channel++;
    if (Mix_PlayChannel(m_current_channel, m_chunk, loops) < 0)
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Sound.Play: %s", SDL_GetError());
}

void Sound::Stop()
{
    if (Mix_HaltChannel(m_current_channel) < 0)
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Sound.Stop: %s", SDL_GetError());
}
