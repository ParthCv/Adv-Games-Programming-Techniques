//
// Created by parth on 10/21/2025.
//

#ifndef ADV_GAME_PROG_TECH_DESTRUCTIONSYSTEM_H
#define ADV_GAME_PROG_TECH_DESTRUCTIONSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class DestructionSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* cameraEntity = nullptr;

        for (const auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }

        if (!cameraEntity) return;
        auto& camera = cameraEntity->getComponent<Camera>();

        for (const auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<ProjectileTag>()) {
                auto& transform = entity->getComponent<Transform>();

                if (
                    transform.position.x > camera.view.x + camera.view.w ||
                    transform.position.x < camera.view.x ||
                    transform.position.y > camera.view.y + camera.view.h ||
                    transform.position.y < camera.view.y)
                {
                        entity->destroy();

                }
            }
        }
    }
};

#endif //ADV_GAME_PROG_TECH_DESTRUCTIONSYSTEM_H