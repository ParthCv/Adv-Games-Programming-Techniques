//
// Created by parth on 9/2/2025.
//

#include "Game.h"
#include "Map.h"

#include <iostream>
#include <ostream>


Map *map = nullptr;

Game::Game() {

}

Game::~Game() {
    destroy();
}

void Game::init(const char *title, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1) {
        std::cout << "SDL_InitSubSystem Initialized: " << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);
        if (window) {
            std::cout << "SDL_CreateWindow: " << title << std::endl;
        }

        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer) {
            std::cout << "renderer created" << std::endl;
        } else {
            std::cout << "renderer could not be created" << std::endl;
            return;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    // Load our map
    map = new Map();

    //player = new GameObject("../asset/ball.png", 0, 0);

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0,0), 0.0f, 1.0f);

    SDL_Texture *texture = TextureManager::load("../asset/mario.png");
    SDL_FRect playerSrcRect = {0,0,32,44};
    SDL_FRect playerDstRect = {playerTransform.position.x,playerTransform.position.y,64,88};

    player.addComponent<Velocity>(Vector2D(0.5,1.5), 60.0f);

    player.addComponent<Sprite>(texture, playerSrcRect, playerDstRect);
}

void Game::handleEvents() {
    //SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    auto currentTime = static_cast<float>(SDL_GetTicks());
    if (lastFrameTime == 0.0) {
        lastFrameTime = currentTime;
    }

    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentTime;

    frameCount++;
    std::cout << frameCount << " delta time :" << deltaTime << std::endl;
    world.update(deltaTime, event);
}

void Game::render() {
    // Uint64 currentTime = SDL_GetTicks();
    // int colorIndex = (currentTime / 1000) % 6;
    //
    // switch(colorIndex) {
    //     case 0: r = 255; g = 0;   b = 0;   break; // Red
    //     case 1: r = 0;   g = 255; b = 0;   break; // Green
    //     case 2: r = 0;   g = 0;   b = 255; break; // Blue
    //     case 3: r = 255; g = 255; b = 0;   break; // Yellow
    //     case 4: r = 255; g = 0;   b = 255; break; // Magenta
    //     case 5: r = 0;   g = 255; b = 255; break; // Cyan
    //     default: r = 0;   g = 0;   b = 255; break;
    // }
    // a = 255;
    //
    // SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    map->draw();

    world.render();

    SDL_RenderPresent(renderer);
}


void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "destroyed game" << std::endl;
}



