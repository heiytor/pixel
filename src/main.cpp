#include "game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.Initialize();
    game.SetMaxFPS(0);

    game.Run();

    game.Destroy();
    return 0;
}
