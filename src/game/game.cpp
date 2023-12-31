#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <cstdlib>
#include <glm/glm.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>

#include "../ECS.h"
#include "game.h"

/**
 * TODO...
 */
#define SDL_check(fn, msg) \
    if ((fn) != 0) {       \
    }

Game::Game() {
    FPS = DEFAULT_MAX_FPS;
    msPrevFrame = 0;
    deltaTime = 0.0;
    isRunning = false;

    spdlog::info("Game initialized with default settings:");
    spdlog::info("  - Maximum FPS: {}", FPS);
}

Game::~Game() {
}

void Game::SetMaxFPS(std::size_t fps) {
    if (fps == 0) {
        spdlog::info("Setting maximum FPS to unlimited (0).");
    } else {
        spdlog::info("Setting maximum FPS to {}.", fps);
    }

    this->FPS = fps;
}

template <typename T>
[[nodiscard]] inline T Game::byDeltaTime(T v) {
    return v * this->deltaTime;
}

inline void Game::setDeltaTime() {
    this->deltaTime = (SDL_GetTicks() - this->msPrevFrame) / 1000.0f;
}

void Game::Initialize() {
    SDL_Init(SDL_INIT_EVERYTHING);

    mWindow = SDL_CreateWindow(
        "pixel",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1380,
        720,
        SDL_WINDOW_BORDERLESS);
    if (!mWindow) {
        exit(EXIT_FAILURE);
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (!mRenderer) {
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

        this->setDeltaTime();
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
    while (SDL_PollEvent(&events)) {
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

// glm::vec2 pos;
// glm::vec2 vel;

void Game::Setup() {
    System sys;

    Entity en1(1);
    Entity en2(2);

    sys.addEntity(en1);
    sys.addEntity(en2);

    for (Entity entity : sys.getEntities()) {
        spdlog::info("{}", entity.getID());
    }

    sys.removeEntity(en1);
    sys.removeEntity(en2);

    for (Entity entity : sys.getEntities()) {
        spdlog::info("{}", entity.getID());
    }

    // pos = glm::vec2(10.0, 20.0);
    // vel = glm::vec2(40.0, 10.0);
}

void Game::Update() {
    // pos.x += this->byDeltaTime(vel.x);
    // pos.y += this->byDeltaTime(vel.y);
}

void Game::Render() {
    SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(this->mRenderer);

    // TODO: render the game...
    // SDL_Texture *texture = IMG_LoadTexture(this->mRenderer, "./assets/images/tank-tiger-right.png");
    //
    // SDL_Rect dstRect = {
    //     static_cast<int>(pos.x), static_cast<int>(pos.y),
    //     32, 32};
    //
    // SDL_RenderCopy(this->mRenderer, texture, NULL, &dstRect);

    SDL_RenderPresent(this->mRenderer);
}
