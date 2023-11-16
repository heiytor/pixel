#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

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
    isRunning = false;
    mWindow = nullptr;
    mRenderer = nullptr;
}

Game::~Game() {

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
    this->isRunning = true;
    while (this->isRunning) {
       Process();
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

void Game::Update() {

}

void Game::Render() {
    SDL_check(SDL_SetRenderDrawColor(this->mRenderer, 255, 0, 0, 255), "SDL_SetRenderDrawColor");
    SDL_check(SDL_RenderClear(this->mRenderer), "SDL_RenderClear");

    // TODO: render the game...

    SDL_RenderPresent(this->mRenderer);
}
