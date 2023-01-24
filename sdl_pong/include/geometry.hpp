#pragma once

#include <cmath>

namespace sdl_pong
{
    struct Vec2
    {
        float x{ };
        float y{ };

        Vec2 operator-() noexcept
        {
            Vec2 ret{ -x, -y };
            return ret;
        }

        Vec2& operator+(const Vec2& other) noexcept
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2& operator-(const Vec2& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vec2& operator*(float val) noexcept
        {
            x *= val;
            y *= val;
            return *this;
        }

        Vec2& operator*=(float val) noexcept
        {
            x *= val;
            y *= val;
            return *this;
        }

        float length() const noexcept
        {
            return std::sqrtf(x * x + y * y);
        }

        Vec2& normalize() noexcept
        {
            const auto len = length();
            if (len)
            {
                x /= len;
                y /= len;
            }
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
