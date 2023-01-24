#pragma once

#include "fwd.hpp"
#include "geometry.hpp"

union SDL_Event;

namespace sdl_pong
{
    class Object
    {
    public:

        Object() = default;

        Object(const Object&) = delete;

        Object& operator=(const Object&) = delete;

        virtual ~Object() = default;

        void SetPos(float x, float y);

        void SetSize(float w, float h);

        Vec2 GetPos() const;

        Size GetSize() const;

        Bounds GetBounds() const;

        bool IsVisible() const;

        void SetVisible(bool visible);

        virtual void Update(float dt);

        virtual void Draw(const GraphicsPtr& graphics);

        virtual void HandleEvent(const SDL_Event& event);

    private:

        Bounds m_bounds{ };

        bool m_is_visible{ true };
    };
}
