#include "Game.hpp"
#include "Graphics.hpp"
#include "AssetsManager.hpp"
#include "Object.hpp"
#include "constants.hpp"
#include "Levels/PongLevel.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace sdl_pong;

Game::Game()
{
    if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(std::string("Game.Game: ") + SDL_GetError());

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(44100, AUDIO_S16, 2, 512);
    Mix_AllocateChannels(MIXER_TRACKS);

    if (TTF_Init() < 0)
        throw std::runtime_error(std::string("Game.Game: ") + TTF_GetError());

    m_graphics.reset(new Graphics);
    m_asset_manager.reset(new AssetsManager);

    m_graphics->Init();
    m_asset_manager->SetGraphics(m_graphics);
}

Game::~Game()
{
    m_active_game_level.reset();
    m_game_objects.clear();
    m_asset_manager.reset();
    m_graphics.reset();

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
}

void Game::Run()
{
    m_active_game_level.reset(new PongLevel);
    m_game_objects = m_active_game_level->PrepareLevel(m_asset_manager);

    SDL_Event evt;
    bool is_running = true;

    auto last_tick = SDL_GetTicks64();
    double accumulator = 0.;

    while (is_running)
    {
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                is_running = false;
                break;
            }

            for (auto& obj : m_game_objects)
                obj->HandleEvent(evt);
        }

        auto current_tick = SDL_GetTicks64();
        float frame_time = (current_tick - last_tick) / 1000.f;
        if (frame_time > 0.25)
            frame_time = 0.25; //to prevent hanging in Update loop
        last_tick = current_tick;

        constexpr float dt = 1.f / 500;
        accumulator += frame_time;

        while (accumulator >= dt)
        {
            for (auto& obj : m_game_objects)
                obj->Update(dt);

            accumulator -= dt;
        }
        m_graphics->PrepareFrame();

        for (auto& obj : m_game_objects)
            obj->Draw(m_graphics);

        m_graphics->Flush();

        SDL_Delay(1);
    }

    m_active_game_level.reset();
}
