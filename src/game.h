#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

    public:
        bool isRunning;

        Game();
        ~Game();
        
        void Initialize();
        void Run();
        void Destroy();

        void Process();
        void Update();
        void Render();
};

#endif // GAME_H
