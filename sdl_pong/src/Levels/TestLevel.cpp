#include "Levels/TestLevel.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include "Label.hpp"
#include "AssetsManager.hpp"
#include "constants.hpp"

#include <SDL.h>

using namespace sdl_pong;

std::vector<ObjectPtr> sdl_pong::TestLevel::PrepareLevel(AssetsManagerPtr asset_manager)
{
    auto test_texture = asset_manager->GetTexture("awesomeface.png");
    m_movable_object.reset(new Sprite(test_texture));

    auto test_texture2 = asset_manager->GetTexture("awesomeface.png");
    m_mouse_object.reset(new Sprite(test_texture));
    m_mouse_object->SetSize(100.f, 100.f);

    auto test_font = asset_manager->GetFont("OpenSans-Bold.ttf", 48);
    m_counter_label.reset(new Label(test_font, { 0, 255, 0, 255 }));

    m_collide_sound = asset_manager->GetSound("sound_effect.ogg");

    return { m_counter_label, m_mouse_object, m_movable_object, shared_from_this()};
}

void TestLevel::Update(float dt)
{
    static float speed_x = 576.f;
    static float speed_y = 931.f;

    static int counter = 0;

    auto pos = m_movable_object->GetPos();
    auto size = m_movable_object->GetSize();

    bool has_collide{ false };
    pos.x += speed_x * dt;
    if (pos.x + size.w > WORLD_WIDTH)
    {
        speed_x = -speed_x;
        pos.x = WORLD_WIDTH - size.w;
        has_collide = true;
        ++counter;
    }
    else if (pos.x < 0.f)
    {
        speed_x = -speed_x;
        pos.x = 0.f;
        has_collide = true;
        ++counter;
    }

    pos.y += speed_y * dt;
    if (pos.y + size.w > WORLD_HEIGHT)
    {
        speed_y = -speed_y;
        pos.y = WORLD_HEIGHT - size.h;
        has_collide = true;
        ++counter;
    }
    else if (pos.y < 0.f)
    {
        speed_y = -speed_y;
        pos.y = 0.f;
        has_collide = true;
        ++counter;
    }

    m_counter_label->SetText("Count: " + std::to_string(counter));

    m_movable_object->SetPos(pos.x, pos.y);

    if (has_collide)
        m_collide_sound->Play();
}

void TestLevel::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        auto x = static_cast<float>(event.motion.x);
        auto y = static_cast<float>(event.motion.y);
        const auto& size = m_mouse_object->GetSize();
        m_mouse_object->SetPos(x - size.w / 2.f, y - size.h / 2.f);
    }
}
