//
// Created by parth on 9/16/2025.
//

#ifndef ADV_GAME_PROG_TECH_RENDERSYSTEM_H
#define ADV_GAME_PROG_TECH_RENDERSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"
#include "../../TextureManager.h"

class RenderSystem {
public:
    void render(std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Position>() && entity->hasComponent<Sprite>()) {
                auto& position = entity->getComponent<Position>();
                auto& sprite = entity->getComponent<Sprite>();
                sprite.dest.x = position.x;
                sprite.dest.y = position.y;
                TextureManager::draw(sprite.texture,sprite.src, sprite.dest);
            }
        }

    }
};

#endif //ADV_GAME_PROG_TECH_RENDERSYSTEM_H