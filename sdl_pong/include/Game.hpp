#pragma once

#include "fwd.hpp"

#include <vector>

namespace sdl_pong
{
    class Game
    {
    public:

        Game();

        ~Game();

        Game(const Game&) = delete;

        Game& operator=(const Game&) = delete;

        void Run();

    private:

        GraphicsPtr m_graphics;

        AssetsManagerPtr m_asset_manager;

        GameLevelPtr m_active_game_level;

        std::vector<ObjectPtr> m_game_objects;
    };
}
