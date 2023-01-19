#include "Game.hpp"

#include <cstdlib>
#include <stdexcept>

#include <SDL_main.h>
#include <SDL.h>


int main(int, char**)
{
    try
    {
        sdl_pong::Game game;
        game.Run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", ex.what());
    }
    catch (...)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unknown exception while call game.Run()");
    }

    return EXIT_FAILURE;
}
