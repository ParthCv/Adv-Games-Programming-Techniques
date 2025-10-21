//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_COMPONENT_H
#define ADV_GAME_PROG_TECH_COMPONENT_H
#include <functional>
#include <string>
#include <unordered_map>
#include <SDL3/SDL_render.h>

#include "../utils/Vector.h"
#include "system/AnimationClip.h"

struct Transform {
    Vector2D position{};
    float scale{};
    float rotation{};
    Vector2D oldPosition{};
};

struct Velocity {
    Vector2D direction{};
    float speed{};
};

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dest{};
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
};

struct Animation {
    // Key is the animation name and clip will hold the animation
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{};
    int currentFrame{};
    float speed = 0.1f;
};

struct Camera {
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback{};
    float timer{};
};

struct SceneState {
    int coinsCollected = 0;
};

struct ProjectileTag {};

struct PlayerTag{};

#endif //ADV_GAME_PROG_TECH_COMPONENT_H