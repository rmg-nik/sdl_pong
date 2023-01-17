#include <SDL.h>
#include <SDL_main.h>
#include <cstdlib>

int main(int, char**)
{

    SDL_Window* window = SDL_CreateWindow("SDL PONG",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, 0);

    SDL_Event evt;
    bool is_running = true;

    while (is_running)
    {
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
                case SDL_QUIT:
                {
                    is_running = false;
                    break;
                }
            }
        }
        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}
