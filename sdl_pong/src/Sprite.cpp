#include "Sprite.hpp"
#include "Graphics.hpp"

using namespace sdl_pong;

Sprite::Sprite(TexturePtr texture)
{
    SetTexture(texture);
}

void Sprite::Draw(const GraphicsPtr& graphics)
{
    graphics->Draw(m_texture, GetBounds());
}

void Sprite::SetTexture(TexturePtr texture)
{
    m_texture = std::move(texture);
    SetSize(static_cast<float>(m_texture->GetWidth()), static_cast<float>(m_texture->GetHeight()));

}
