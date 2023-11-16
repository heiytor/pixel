#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"

/**
 * TODO...
 */
#define SDL_check(fn, msg) \
    if ((fn) != 0) { \
        std::cerr << msg << ": " << SDL_GetError() << std::endl; \
        exit(EXIT_FAILURE); \
    }

Game::Game() {
    FPS = DEFAULT_MAX_FPS;
    msPrevFrame = 0;
    dt = 0.0;
    isRunning = false;
}

Game::~Game() {
}

void Game::SetMaxFPS(std::size_t fps) {
    this->FPS = fps;
}

template<typename T>
[[nodiscard]] inline T Game::deltaTime(T v) {
    return v * this->dt;
}

void Game::Initialize() {
    SDL_check(SDL_Init(SDL_INIT_EVERYTHING), "SDL_Init");

    mWindow = SDL_CreateWindow(
        "pixel",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1380,
        720,
        SDL_WINDOW_BORDERLESS
    );
    if (!mWindow) {
        std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (!mRenderer) {
        std::cerr << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}


void Game::Run() {
    this->Setup();

    this->isRunning = true;
    while (this->isRunning) {
       Process();

       if (this->FPS != 0) {
           int delay = MILLISECOND / this->FPS - (SDL_GetTicks64() - this->msPrevFrame);
           if (delay > 0 && delay <= MILLISECOND / this->FPS) {
               SDL_Delay(delay);
           }
       }

       this->dt = (SDL_GetTicks() - this->msPrevFrame) / 1000.0f;

       this->msPrevFrame = SDL_GetTicks64();

       Update();
       Render();
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::Process() {
    SDL_Event events;
    while(SDL_PollEvent(&events)) {
        // TODO: maybe this switch can be in a different method that handle a custom event loop
        switch (events.type) {
            case SDL_QUIT: 
                this->isRunning = false;

                break;
            case SDL_KEYDOWN:
                // TODO: handle the key sym  must be in a different method
                switch (events.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        this->isRunning = false;
                        break;
                }

                break;
            default:
                break;
        }
    }
}

glm::vec2 pos;
glm::vec2 vel;

void Game::Setup() {
    pos = glm::vec2(10.0, 20.0);
    vel = glm::vec2(40.0, 10.0);
}

void Game::Update() {
    pos.x += this->deltaTime(vel.x);
    pos.y += this->deltaTime(vel.y);
}

void Game::Render() {
    SDL_check(SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255), "SDL_SetRenderDrawColor");
    SDL_check(SDL_RenderClear(this->mRenderer), "SDL_RenderClear");

    // TODO: render the game...
    SDL_Texture* texture = IMG_LoadTexture(this->mRenderer, "./assets/images/tank-tiger-right.png");

    SDL_Rect dstRect = {
        static_cast<int>(pos.x), static_cast<int>(pos.y),
        32, 32
    };

    SDL_RenderCopy(this->mRenderer, texture, NULL, &dstRect);

    SDL_RenderPresent(this->mRenderer);
}
