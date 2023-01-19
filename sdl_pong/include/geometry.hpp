#pragma once

namespace sdl_pong
{
    struct Vec2
    {
        float x{ };
        float y{ };

        Vec2 operator-()
        {
            Vec2 ret{ -x, -y };
            return ret;
        }

        Vec2& operator+(const Vec2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2& operator-(const Vec2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
    };

    struct Size
    {
        float w{ };
        float h{ };
    };

    struct Bounds
    {
        Vec2 pos;
        Size size;
    };
}
