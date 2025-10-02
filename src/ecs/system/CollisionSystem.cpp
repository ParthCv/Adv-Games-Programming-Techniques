//
// Created by parth on 10/2/2025.
//

#include "CollisionSystem.h"

#include <iostream>

#include "../World.h"
#include "../../utils/Collision.h"

void CollisionSystem::update (World& world) {
    const std::vector<Entity*> collidables = queryCollidables(world.getEntities());
    for (size_t i = 0; i < collidables.size(); i++) {
        auto entityA = collidables[i];
        auto& t = entityA->getComponent<Transform>();
        auto& colliderA = entityA->getComponent<Collider>();

        colliderA.rect.x = t.position.x;
        colliderA.rect.y = t.position.y;

        for (size_t j = i+1; j < collidables.size(); j++) {
            auto entityB = collidables[j];
            auto& colliderB = entityB->getComponent<Collider>();

            if (Collision::AABB(colliderA, colliderB)) {
                std::cout << colliderA.tag << " hit " << colliderB.tag << std::endl;
            }
        }
    }
}

std::vector<Entity *> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity> > &entities) {
    std::vector<Entity *> collidables;
    for (auto& e : entities) {
        if (e->hasComponent<Transform>() && e->hasComponent<Collider>()) {
            collidables.push_back(e.get());
        }
    }

    return collidables;
}
