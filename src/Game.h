//
// Created by parth on 9/2/2025.
//

// #ifndef ADV_GAME_PROG_TECH_GAME_H
// #define ADV_GAME_PROG_TECH_GAME_H
//
// #endif //ADV_GAME_PROG_TECH_GAME_H

#pragma once
#include <SDL3/SDL.h>

#include "ecs/World.h"

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

    SDL_Renderer* renderer = nullptr;

    World world;

private:
    int frameCount = 0;
    bool isRunning = false;
    float lastFrameTime = 0.0f;

    SDL_Window* window = nullptr;

    Uint8 r, g, b, a;
};
