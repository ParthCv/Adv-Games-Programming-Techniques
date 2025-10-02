//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_COMPONENT_H
#define ADV_GAME_PROG_TECH_COMPONENT_H
#include <string>
#include <SDL3/SDL_render.h>

#include "../utils/Vector.h"

struct Transform {
    Vector2D position{};
    float scale{};
    float rotation{};
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

#endif //ADV_GAME_PROG_TECH_COMPONENT_H