//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_WORLD_H
#define ADV_GAME_PROG_TECH_WORLD_H
#include <memory>
#include <vector>

#include "Entity.h"
#include "EventManager.h"
#include "../Map.h"
#include "system/AnimationSystem.h"
#include "system/CameraSystem.h"
#include "system/CollisionSystem.h"
#include "system/KeyboardInputSystem.h"
#include "system/MovementSystem.h"
#include "system/RenderSystem.h"

class World {
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    EventManager eventManager;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
public:
    World();
    void update(float dt, SDL_Event event) {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        animationSystem.update(entities, dt);
        cameraSystem.update(entities);
        cleanup();
    };

    void render() {
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                map.draw(entity->getComponent<Camera>());
                break;
            }
        }

        renderSystem.render(entities);
    }

    Entity& createEntity() {
        entities.emplace_back(std::make_unique<Entity>());
        return *entities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanup() {
        std::erase_if(
            entities,
            [](std::unique_ptr<Entity>& e) {
                return !e->isActive();
            }
        );
    }

    EventManager& getEventManager() {
        return eventManager;
    }

    Map& getMap() {
        return map;
    }

};

#endif //ADV_GAME_PROG_TECH_WORLD_H