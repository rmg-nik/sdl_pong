#pragma once

#include <memory>

namespace sdl_pong
{
    class Texture;
    using TexturePtr = std::shared_ptr<Texture>;

    class Graphics;
    using GraphicsPtr = std::shared_ptr<Graphics>;
    using GraphicsWeakPtr = std::weak_ptr<Graphics>;

    class AssetsManager;
    using AssetsManagerPtr = std::shared_ptr<AssetsManager>;

    class Object;
    using ObjectPtr = std::shared_ptr<Object>;

    class GameLevel;
    using GameLevelPtr = std::shared_ptr<GameLevel>;

    class Sound;
    using SoundPtr = std::shared_ptr<Sound>;

    class Sprite;
    using SpritePtr = std::shared_ptr<Sprite>;

    class Label;
    using LabelPtr = std::shared_ptr<Label>;

    class Font;
    using FontPtr = std::shared_ptr<Font>;
}
