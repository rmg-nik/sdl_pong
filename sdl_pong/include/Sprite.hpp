#pragma once

#include "Object.hpp"
#include "Texture.hpp"

namespace sdl_pong
{
    class Sprite: public Object
    {
    public:

        Sprite(TexturePtr texture);

        Sprite(const Sprite&) = delete;

        Sprite& operator=(const Sprite&) = delete;

        void Draw(const GraphicsPtr& graphics) override;

        void SetTexture(TexturePtr texture);

    private:

        TexturePtr m_texture;
    };

    using SpritePtr = std::shared_ptr<Sprite>;
}
