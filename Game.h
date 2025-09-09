//
// Created by parth on 9/2/2025.
//

// #ifndef ADV_GAME_PROG_TECH_GAME_H
// #define ADV_GAME_PROG_TECH_GAME_H
//
// #endif //ADV_GAME_PROG_TECH_GAME_H

#pragma once
#include <SDL3/SDL.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void destroy();
    void changeToRandomColor();

    bool running() {
        return isRunning;
    }

private:
    int frameCount = 0;
    bool isRunning;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Uint8 r, g, b, a;
};