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
            if (entity->hasComponent<Position>()) {
                auto& position = entity->getComponent<Position>();
                position.x += 60 * dt;
                position.y += 60 * dt;
            }
        }

    };
};

#endif //ADV_GAME_PROG_TECH_MOVEMENTSYSTEM_H