#pragma once

#include "fwd.hpp"
#include "Sprite.hpp"
#include "Color.hpp"

#include <string>
#include <string_view>

namespace sdl_pong
{
    class Label : public Sprite
    {
    public:

        Label(FontPtr font, Color color);

        void SetText(std::string text);

    private:

        std::string m_text{ " " };

        FontPtr m_font;

        Color m_color{ };
    };

    using LabelPtr = std::shared_ptr<Label>;
}
