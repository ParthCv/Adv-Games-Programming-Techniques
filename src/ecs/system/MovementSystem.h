//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_MOVEMENTSYSTEM_H
#define ADV_GAME_PROG_TECH_MOVEMENTSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& transform = entity->getComponent<Transform>();
                auto& velocity = entity->getComponent<Velocity>();

                transform.oldPosition = transform.position;

                Vector2D directionVec = velocity.direction;

                directionVec.normalize();

                Vector2D velocityVec = directionVec * velocity.speed;

                transform.position += (velocityVec * dt);
            }
        }

    };
};

#endif //ADV_GAME_PROG_TECH_MOVEMENTSYSTEM_H