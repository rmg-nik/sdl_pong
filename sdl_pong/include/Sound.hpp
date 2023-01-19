#pragma once

#include "fwd.hpp"
#include "MemoryBlock.hpp"

struct Mix_Chunk;

namespace sdl_pong
{
    class Sound
    {
    public:

        Sound(MemoryBlock memory_block);

        Sound(const Sound&) = delete;

        Sound& operator=(const Sound&) = delete;

        ~Sound();

        void Play(int loops = 0);

        void Stop();

    private:

        Mix_Chunk* m_chunk{ nullptr };

        int m_current_channel{ 0 };
    };
}
