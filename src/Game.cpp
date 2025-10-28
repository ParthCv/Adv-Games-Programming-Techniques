//
// Created by parth on 9/2/2025.
//

#include "Game.h"
#include "Map.h"

#include <iostream>
#include <ostream>

#include "manager/AssetManager.h"

std::function<void(std::string)> Game::onSceneChangeRequest;

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

    AssetManager::loadAnimation("player", "../asset/animations/rooster.xml");
    AssetManager::loadAnimation("enemy", "../asset/animations/bird_animations.xml");

    //
    sceneManager.loadScene("level1", "../asset/map.tmx", width, height);
    sceneManager.loadScene("level2", "../asset/map2.tmx", width, height);

    sceneManager.changeSceneDeferred("level1");

    onSceneChangeRequest = [this](std::string sceneName) {
        if (sceneManager.currentScene->getName() == "level2" && sceneName == "level2") {
            std::cout << "You Win" << std::endl;
            isRunning = false;
            return;
        }

        if (sceneName == "gameover") {
            isRunning = false;
            return;
        }

        sceneManager.changeSceneDeferred(sceneName);
    };

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
    sceneManager.update(deltaTime, event);
    frameCount++;
    // std::cout << frameCount << " delta time :" << deltaTime << std::endl;
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
    sceneManager.render();
    SDL_RenderPresent(renderer);
}


void Game::destroy() {
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "destroyed game" << std::endl;
}



