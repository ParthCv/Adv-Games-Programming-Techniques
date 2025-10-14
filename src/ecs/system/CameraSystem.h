//
// Created by parth on 10/14/2025.
//

#ifndef ADV_GAME_PROG_TECH_CAMERASYSTEM_H
#define ADV_GAME_PROG_TECH_CAMERASYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class CameraSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        for (auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>()) {
                playerEntity = entity.get();
                break;
            }
        }

        if (!playerEntity) return;

        auto& playerTransform = playerEntity->getComponent<Transform>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                auto& camera = entity->getComponent<Camera>();

                camera.view.x = playerTransform.position.x - camera.view.w / 2;
                camera.view.y = playerTransform.position.y - camera.view.h / 2;

                if (camera.view.x < 0) camera.view.x = 0;
                if (camera.view.y < 0) camera.view.y = 0;
                if (camera.view.x > camera.worldWidth - camera.view.w)
                    camera.view.x = camera.worldWidth - camera.view.w;
                if (camera.view.y > camera.worldHeight - camera.view.h)
                    camera.view.y = camera.worldHeight - camera.view.h;
            }
        }
    }
};

#endif //ADV_GAME_PROG_TECH_CAMERASYSTEM_H