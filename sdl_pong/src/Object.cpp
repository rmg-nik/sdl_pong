#include "Object.hpp"

#include <utility>

using namespace sdl_pong;

void Object::SetPos(float x, float y)
{
    m_bounds.pos.x = x;
    m_bounds.pos.y = y;
}

void Object::SetSize(float w, float h)
{
    m_bounds.size.w = w;
    m_bounds.size.h = h;
}

Vec2 Object::GetPos() const
{
    return m_bounds.pos;
}

Size Object::GetSize() const
{
    return m_bounds.size;
}

Bounds Object::GetBounds() const
{
    return m_bounds;
}

void Object::Update(float)
{
}

void Object::Draw(const GraphicsPtr&)
{
}

void Object::HandleEvent(const SDL_Event&)
{
}
