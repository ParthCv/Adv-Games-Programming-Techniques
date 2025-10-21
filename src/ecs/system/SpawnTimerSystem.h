//
// Created by parth on 10/21/2025.
//

#ifndef ADV_GAME_PROG_TECH_SPAWNTIMERSYSTEM_H
#define ADV_GAME_PROG_TECH_SPAWNTIMERSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class SpawnTimerSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const float dt) {
        for (const auto& entity : entities) {
            if (entity->hasComponent<TimedSpawner>()) {
                auto& spawner = entity->getComponent<TimedSpawner>();

                spawner.timer -= dt;

                if (spawner.timer <= 0) {
                    spawner.timer = spawner.spawnInterval;
                    spawner.spawnCallback();
                }
            }
        }
    }
};

#endif //ADV_GAME_PROG_TECH_SPAWNTIMERSYSTEM_H