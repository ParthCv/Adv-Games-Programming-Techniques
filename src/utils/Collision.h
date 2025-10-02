//
// Created by parth on 10/2/2025.
//

#ifndef ADV_GAME_PROG_TECH_COLLISION_H
#define ADV_GAME_PROG_TECH_COLLISION_H
#include <SDL3/SDL_rect.h>

#include "../ecs/Component.h"

class Collision {
public:
    // axis aligned bounding box
    static bool AABB(const SDL_FRect& r1, const SDL_FRect& r2);
    static bool AABB(const Collider& c1, const Collider& c2);

};

#endif //ADV_GAME_PROG_TECH_COLLISION_H