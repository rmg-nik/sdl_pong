#pragma once

#include "GameLevel.hpp"
#include "Object.hpp"

namespace sdl_pong
{
    class TestLevel: public GameLevel, public Object, public std::enable_shared_from_this<TestLevel>
    {
    public:

        std::vector<ObjectPtr> PrepareLevel(AssetsManagerPtr asset_manager) override;

        void Update(float dt) override;

        void HandleEvent(const SDL_Event& event) override;

    private:

        ObjectPtr m_movable_object;
        ObjectPtr m_mouse_object;
        SoundPtr  m_collide_sound;
        LabelPtr  m_counter_label;
    };
}
