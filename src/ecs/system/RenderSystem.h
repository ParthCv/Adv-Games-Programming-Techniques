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

        Entity* cameraEntity = nullptr;

        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }

        if (!cameraEntity) {
            return;
        }

        auto& camera = cameraEntity->getComponent<Camera>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                sprite.dest.x = t.position.x - camera.view.x;
                sprite.dest.y = t.position.y - camera.view.y;

                if (entity->hasComponent<Animation>()) {
                    auto& anim = entity->getComponent<Animation>();
                    sprite.src = anim.clips[anim.currentClip].frameIndices[anim.currentFrame];
                }

                TextureManager::draw(sprite.texture,sprite.src, sprite.dest);
            }
        }

    }
};

#endif //ADV_GAME_PROG_TECH_RENDERSYSTEM_H