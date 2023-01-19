#pragma once

#include "fwd.hpp"

#include <vector>

namespace sdl_pong
{
    class GameLevel
    {
    public:

        GameLevel() = default;

        GameLevel(const GameLevel&) = delete;

        GameLevel& operator=(const GameLevel&) = delete;

        virtual ~GameLevel() = default;

        virtual std::vector<ObjectPtr> PrepareLevel(AssetsManagerPtr asset_manager) = 0;
    };
}
