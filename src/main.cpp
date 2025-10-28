#include <iostream>

#include "Game.h"

Game *game = nullptr;

int main() {
    const int FPS = 60;
    const int desiredFrameTime = 1000 / FPS;

    Uint64 ticks;
    int actualFrameTime;

    game = new Game();
    game->init("Tutorial", 800, 600, false);

    while (game->running()) {
        ticks = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        actualFrameTime = SDL_GetTicks() - ticks;

        if (actualFrameTime < desiredFrameTime) {
            SDL_Delay(desiredFrameTime - actualFrameTime);
        }
    }

    delete game;

    return 0;
}