#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_image.h"
#include "SDL_surface.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    SDL_Window* w;
    SDL_Renderer* r;
    char* title;

    int is_running;
} 
px_Game;

int px_init(px_Game* game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return 1; // TODO: docs
    }

    // TODO: initial x,y,w,h and optional fullscreen
    game->w = SDL_CreateWindow(game->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
    if (game->w == NULL) {
        return 2; // TODO: docs
    }

    game->r = SDL_CreateRenderer(game->w, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (game->r == NULL) {
        return 3; // TODO: docs
    }

    game->is_running = 1; // TODO
    return 0;
};

void px_run(px_Game *game) {

}

void px_finish(px_Game *game) {
    SDL_DestroyRenderer(game->r);
    SDL_DestroyWindow(game->w);
    free(game);
}

int main(void)
{
    px_Game* g = malloc(sizeof(px_Game));
    memset(g, 0, sizeof(px_Game));
    g->title = "My Game!";

    px_init(g);

    while (g->is_running) {
        // Process
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    g->is_running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        g->is_running = 0;
                    }
                    break;
                default:
                    break;
            }
        }

        // Update

        // Render
        SDL_SetRenderDrawColor(g->r, 255, 0, 0, 255);
        SDL_RenderClear(g->r);

        SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(g->r, surface);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(g->r, texture, NULL, &(SDL_Rect){20,20,32,32});
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(g->r);
    }

    px_finish(g); // TODO: defer
    return 0;
}
