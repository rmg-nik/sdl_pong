#include "Levels/PongLevel.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include "Label.hpp"
#include "AssetsManager.hpp"
#include "constants.hpp"

#include <random>

#include <SDL.h>

using namespace sdl_pong;

namespace
{
    const float min_ball_speed = 500.f;
    const float max_ball_speed = 5000.f;
    const float ball_speed_delta = 100.f;
}

std::vector<ObjectPtr> PongLevel::PrepareLevel(AssetsManagerPtr asset_manager)
{
    m_started = false;

    auto background_texture = asset_manager->GetTexture("background.png");
    SpritePtr background(new Sprite(background_texture));

    auto border_texture = asset_manager->GetTexture("border.png");
    SpritePtr border_top(new Sprite(border_texture));
    border_top->SetPos(0.f, 0.f);
    SpritePtr border_bottom(new Sprite(border_texture));
    border_bottom->SetPos(0.f, static_cast<float>(WORLD_HEIGHT - border_texture->GetHeight()));

    auto paddle_texture = asset_manager->GetTexture("paddle.png");
    m_player_paddle.reset(new Sprite(paddle_texture));

    m_bot_paddle.reset(new Sprite(paddle_texture));
    
    auto gate_texture = asset_manager->GetTexture("gate.png");
    SpritePtr gate_left(new Sprite(gate_texture));
    gate_left->SetPos(0.f, static_cast<float>(WORLD_HEIGHT - gate_texture->GetHeight()));
    SpritePtr gate_right(new Sprite(gate_texture));
    gate_right->SetPos(static_cast<float>(WORLD_WIDTH - gate_texture->GetWidth()), static_cast<float>(WORLD_HEIGHT - gate_texture->GetHeight()));

    auto ball_texture = asset_manager->GetTexture("ball.png");
    m_ball.reset(new Sprite(ball_texture));
    
    auto font = asset_manager->GetFont("OpenSans-Bold.ttf", 48);
    m_counter_label.reset(new Label(font, { 0, 255, 0, 255 }));

    m_collide_sound = asset_manager->GetSound("sound_effect.ogg");

    m_gate_left_bounds = gate_left->GetBounds();
    m_gate_right_bounds = gate_right->GetBounds();
    m_border_top_bounds = border_top->GetBounds();
    m_border_bottom_bounds = border_bottom->GetBounds();

    Init();

    return {
        background,
        gate_left,
        gate_right,
        border_top,
        border_bottom,
        m_player_paddle,
        m_bot_paddle,
        m_ball,
        shared_from_this()
    };
}

void PongLevel::Update(float dt)
{
    if (!m_started)
        return;

    const float max_paddle_speed = 500.f;

    {
        auto pos = m_ball->GetPos();
        auto size = m_ball->GetSize();

        pos.y += m_ball_direction.y * m_current_ball_speed * dt;
        if (pos.y + size.h > m_border_bottom_bounds.pos.y)
        {
            m_ball_direction.y = -m_ball_direction.y;
            pos.y = m_border_bottom_bounds.pos.y - size.h;
        }
        else if (pos.y < m_border_top_bounds.pos.y + m_border_top_bounds.size.h)
        {
            m_ball_direction.y = -m_ball_direction.y;
            pos.y = m_border_top_bounds.pos.y + m_border_top_bounds.size.h;
        }

        pos.x += m_ball_direction.x * m_current_ball_speed * dt;
        if (pos.y + size.h > m_border_bottom_bounds.pos.y)
        {
            m_ball_direction.y = -m_ball_direction.y;
            pos.y = m_border_bottom_bounds.pos.y - size.h;
        }
        else if (pos.y < m_border_top_bounds.pos.y + m_border_top_bounds.size.h)
        {
            m_ball_direction.y = -m_ball_direction.y;
            pos.y = m_border_top_bounds.pos.y + m_border_top_bounds.size.h;
        }

        m_ball->SetPos(pos.x, pos.y);
    }

    {
        auto pos = m_ball->GetPos();
        auto size = m_ball->GetSize();

        if (pos.x + size.w >= m_gate_right_bounds.pos.x)
        {
            m_started = false;
        }
        else if (pos.x <= m_gate_left_bounds.pos.x + m_gate_left_bounds.size.w)
        {
            m_started = false;
        }
    }

    {
        if (m_user_paddle_direction)
        {
            auto pos = m_player_paddle->GetPos();
            auto size = m_player_paddle->GetSize();

            pos.y += m_user_paddle_direction * max_paddle_speed * dt;
            if (pos.y + size.h > m_border_bottom_bounds.pos.y)
            {
                pos.y = m_border_bottom_bounds.pos.y - size.h;
            }
            else if (pos.y < m_border_top_bounds.pos.y + m_border_top_bounds.size.h)
            {
                pos.y = m_border_top_bounds.pos.y + m_border_top_bounds.size.h;
            }

            m_player_paddle->SetPos(pos.x, pos.y);
        }
    }

    {
        auto pos = m_bot_paddle->GetPos();
        auto size = m_bot_paddle->GetSize();

        const auto ball_center_y = m_ball->GetPos().y + m_ball->GetSize().h / 2;
        const auto bot_paddle_center_y = pos.y + size.h / 2;
        const auto max_offset = max_paddle_speed * dt;
        const auto center_diff = ball_center_y - bot_paddle_center_y;
        const auto offset = std::min(max_offset, std::fabs(center_diff));
        pos.y += std::copysignf(offset, center_diff);
        if (pos.y + size.h > m_border_bottom_bounds.pos.y)
        {
            pos.y = m_border_bottom_bounds.pos.y - size.h;
        }
        else if (pos.y < m_border_top_bounds.pos.y + m_border_top_bounds.size.h)
        {
            pos.y = m_border_top_bounds.pos.y + m_border_top_bounds.size.h;
        }

        m_bot_paddle->SetPos(pos.x, pos.y);
    }

    {
        auto ball_pos = m_ball->GetPos();
        auto ball_size = m_ball->GetSize();

        auto paddle_pos = m_player_paddle->GetPos();
        auto paddle_size = m_player_paddle->GetSize();

        if (ball_pos.x <= paddle_pos.x + paddle_size.w)
        {
            if ((ball_pos.y + ball_size.h >= paddle_pos.y) && (ball_pos.y <= paddle_pos.y + paddle_size.h))
            {
                m_ball_direction.x = -m_ball_direction.x;
                m_current_ball_speed += ball_speed_delta;
                m_current_ball_speed = std::min(m_current_ball_speed, max_ball_speed);

                m_ball->SetPos(paddle_pos.x + paddle_size.w, ball_pos.y);

                const auto ball_center_y = m_ball->GetPos().y + m_ball->GetSize().h / 2;
                const auto paddle_center_y = paddle_pos.y + paddle_size.h / 2;
                const auto tmp = (ball_center_y - paddle_center_y) / paddle_size.h;
                m_ball_direction.y += tmp;
                m_ball_direction.normalize();
            }
        }

        
    }

    {
        auto ball_pos = m_ball->GetPos();
        auto ball_size = m_ball->GetSize();

        auto paddle_pos = m_bot_paddle->GetPos();
        auto paddle_size = m_bot_paddle->GetSize();

        if (ball_pos.x + ball_size.w >= paddle_pos.x)
        {
            if ((ball_pos.y + ball_size.h >= paddle_pos.y) && (ball_pos.y <= paddle_pos.y + paddle_size.h))
            {
                m_ball_direction.x = -m_ball_direction.x;
                m_current_ball_speed += ball_speed_delta;
                m_current_ball_speed = std::min(m_current_ball_speed, max_ball_speed);

                m_ball->SetPos(paddle_pos.x - ball_size.w, ball_pos.y);

                const auto ball_center_y = m_ball->GetPos().y + m_ball->GetSize().h / 2;
                const auto paddle_center_y = paddle_pos.y + paddle_size.h / 2;
                const auto tmp = (ball_center_y - paddle_center_y) / paddle_size.h;
                m_ball_direction.y += tmp;
                m_ball_direction.normalize();
            }
        }
    }
}

void PongLevel::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_w && !event.key.repeat)
        {
            --m_user_paddle_direction;
        }
        else if (event.key.keysym.sym == SDLK_s && !event.key.repeat)
        {
            ++m_user_paddle_direction;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_w)
        {
            ++m_user_paddle_direction;
        }
        else if (event.key.keysym.sym == SDLK_s)
        {
            --m_user_paddle_direction;
        }
        else if (event.key.keysym.sym == SDLK_SPACE && !m_started)
        {
            m_started = true;
            Init();
        }
    }
}

void PongLevel::Init()
{
    m_user_paddle_direction = 0;
    m_bot_paddle_direction = 0;

    m_current_ball_speed = 0.f;

    m_ball_direction = {};

    m_player_paddle->SetPos(50.f - m_player_paddle->GetSize().w / 2.f,
                            (WORLD_HEIGHT - m_player_paddle->GetSize().h) / 2.f);
    m_bot_paddle->SetPos(WORLD_WIDTH - 50.f - m_bot_paddle->GetSize().w / 2.f,
                        (WORLD_HEIGHT - m_bot_paddle->GetSize().h) / 2.f);
    m_ball->SetPos(
        (WORLD_WIDTH - m_ball->GetSize().w) / 2.f,
        (WORLD_HEIGHT - m_ball->GetSize().h) / 2.f);


    std::mt19937 rand(SDL_GetTicks());
    m_ball_direction.x = WORLD_WIDTH / 2.f;
    m_ball_direction.y = static_cast<float>(rand() % (WORLD_HEIGHT / 2));
    m_ball_direction.normalize();
    if (rand() % 2)
        m_ball_direction *= -1.f;

    m_current_ball_speed = min_ball_speed;
}
