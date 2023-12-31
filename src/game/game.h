#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <cstddef>

const std::size_t DEFAULT_MAX_FPS = 60;
const int MILLISECOND = 1000;

class Game {
  private:
    std::size_t FPS;
    int msPrevFrame;

    double deltaTime;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

  public:
    // TODO: isRunning must be a private attribute
    bool isRunning;

    Game();
    ~Game();

    inline void setDeltaTime();

    /**
     * Multiplies the value `v` by the delta time.
     */
    template <typename T>
    [[nodiscard]] inline T byDeltaTime(T v);

    /**
     * Sets the maximum FPS that the game should target. Set it to 0 for
     * unlimited FPS.
     */
    void SetMaxFPS(std::size_t fps);

    void Initialize();
    void Setup();
    void Run();
    void Destroy();

    void Process();
    void Update();
    void Render();
};

#endif // GAME_H
