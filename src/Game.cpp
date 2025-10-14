//
// Created by parth on 9/2/2025.
//

#include "Game.h"
#include "Map.h"

#include <iostream>
#include <ostream>

#include "AssetManager.h"

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

    // load map
    world.getMap().load("../asset/map.tmx", TextureManager::load("../asset/spritesheet.png"));

    auto& camera = world.createEntity();
    SDL_FRect camView{};
    camView.w = width;
    camView.h = height;
    camera.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    // Add colliders
    for (auto &collider_data : world.getMap().colliders) {
        auto& entity = world.createEntity();
        entity.addComponent<Transform>(Vector2D(collider_data.rect.x, collider_data.rect.y), 0.0f, 1.0f);
        auto& collider = entity.addComponent<Collider>("W");

        collider.rect.x = collider_data.rect.x;
        collider.rect.y = collider_data.rect.y;
        collider.rect.w = collider_data.rect.w;
        collider.rect.h = collider_data.rect.h;

        SDL_Texture* texture = TextureManager::load("../asset/spritesheet.png");
        SDL_FRect source {0, 32, 32, 32};
        SDL_FRect destination {collider.rect.x, collider.rect.y, collider.rect.w, collider.rect.h};
        //entity.addComponent<Sprite>(texture, source, destination);
    }

    // Add Items
    for (auto &item_spawn_position : world.getMap().itemSpawnPositions) {
        auto& item (world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(item_spawn_position.x,item_spawn_position.y), 0.0f, 1.0f);

        SDL_Texture *itemTexture = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrcRect = {0,0,32,32};
        SDL_FRect itemDstRect = {itemTransform.position.x,itemTransform.position.y,32,32};

        item.addComponent<Sprite>(itemTexture, itemSrcRect, itemDstRect);
        auto& itemCollider = item.addComponent<Collider>("Coin");
        itemCollider.rect.w = itemDstRect.w;
        itemCollider.rect.h = itemDstRect.h;
    }

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(200,50), 0.0f, 1.0f);

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture *texture = TextureManager::load("../asset/animations/Rooster_animation_with_shadow.png");
    SDL_FRect playerSrcRect = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDstRect = {playerTransform.position.x,playerTransform.position.y,64,64};

    player.addComponent<Velocity>(Vector2D(0.0,0.0), 120.0f);
    player.addComponent<Sprite>(texture, playerSrcRect, playerDstRect);

    auto& playerCollider = player.addComponent<Collider>("Player");
    playerCollider.rect.w = playerDstRect.w;
    playerCollider.rect.h = playerDstRect.h;

    player.addComponent<PlayerTag>();

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

    world.render();

    SDL_RenderPresent(renderer);
}


void Game::destroy() {
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "destroyed game" << std::endl;
}



