#include "Label.hpp"
#include "Font.hpp"

using namespace sdl_pong;

Label::Label(FontPtr font, Color color)
    : Sprite(font->RenderText("test", color))
    , m_font{ font }
    , m_color{ color }
{
}

void Label::SetText(std::string text)
{
    if (text.empty())
        m_text = " ";
    else
        m_text = text;
    SetTexture(m_font->RenderText(m_text, m_color));
}
