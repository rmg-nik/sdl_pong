#pragma once

#include "fwd.hpp"

#include <map>
#include <string>


namespace sdl_pong
{
    class AssetsManager
    {
    public:

        AssetsManager() = default;

        AssetsManager(const AssetsManager&) = delete;

        AssetsManager& operator=(const AssetsManager&) = delete;

        TexturePtr GetTexture(const std::string& name);

        SoundPtr GetSound(const std::string& name);

        FontPtr GetFont(const std::string& name, int size);

        void SetGraphics(GraphicsPtr graphics);

    private:

        std::map<std::string, TexturePtr> m_textures;

        std::map<std::string, SoundPtr> m_sounds;

        std::map<std::pair<std::string, int>, FontPtr> m_fonts;

        GraphicsWeakPtr m_graphics;
    };
}
