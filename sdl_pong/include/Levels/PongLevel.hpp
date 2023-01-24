#pragma once

#include "GameLevel.hpp"
#include "Object.hpp"

namespace sdl_pong
{
    class PongLevel : public GameLevel, public Object, public std::enable_shared_from_this<PongLevel>
    {
    public:

        std::vector<ObjectPtr> PrepareLevel(AssetsManagerPtr asset_manager) override;

        void Update(float dt) override;

        void HandleEvent(const SDL_Event& event) override;

    private:

        void Init();

    private:

        bool m_started{ false };

        ObjectPtr m_player_paddle;
        ObjectPtr m_bot_paddle;
        ObjectPtr m_ball;
        SoundPtr  m_collide_sound;
        LabelPtr  m_counter_label;

        Bounds m_gate_left_bounds{ };
        Bounds m_gate_right_bounds{ };
        Bounds m_border_top_bounds{ };
        Bounds m_border_bottom_bounds{ };

        int m_user_paddle_direction{ 0 };
        int m_bot_paddle_direction{ 0 };

        float m_current_ball_speed{ 0.f };

        Vec2 m_ball_direction{ };
    };
}
