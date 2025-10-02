//
// Created by parth on 10/2/2025.
//

#include "Collision.h"

#include <SDL3/SDL_rect.h>
bool Collision::AABB(const SDL_FRect& r1, const SDL_FRect& r2) {
    // Check for edge collision
    if (
        r1.x + r1.w >= r2.x &&
        r2.x + r2.w >= r1.x &&
        r1.y + r1.h >= r2.y &&
        r2.y + r2.h >= r1.y
    ) {
        return true;
    }
    return false;
}

bool Collision::AABB(const Collider& c1, const Collider& c2) {
    return AABB(c1.rect, c2.rect);
}
