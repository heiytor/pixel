#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>

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
    while (true) {
    
    }
}

void Game::Destroy() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::Process() {

}

void Game::Update() {

}

void Game::Render() {

}
