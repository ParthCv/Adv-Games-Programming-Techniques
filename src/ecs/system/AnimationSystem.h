//
// Created by parth on 10/14/2025.
//

#ifndef ADV_GAME_PROG_TECH_ANIMATIONSYSTEM_H
#define ADV_GAME_PROG_TECH_ANIMATIONSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class AnimationSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Animation>() && entity->hasComponent<Velocity>() && entity->hasComponent<PlayerTag>()) {
                auto& animation = entity->getComponent<Animation>();
                auto& velocity = entity->getComponent<Velocity>();

                std::string newClip;

                if (velocity.direction.x > 0.0f) {
                    newClip = "walk_right";
                } else if (velocity.direction.x < 0.0f) {
                    newClip = "walk_left";
                } else if (velocity.direction.y > 0.0f) {
                    newClip = "walk_down";
                } else if (velocity.direction.y < 0.0f) {
                    newClip = "walk_up";
                } else {
                    newClip = "idle";
                }

                //check for anim switch
                if (newClip != animation.currentClip) {
                    animation.currentClip = newClip;
                    animation.time = 0.0f;
                    animation.currentFrame =0;
                }

                float animationFrameSpeed = animation.speed;
                auto clip = animation.clips[animation.currentClip];

                animation.time += deltaTime;

                if (animation.time >= animationFrameSpeed) {
                    animation.time -= animationFrameSpeed;

                    std::size_t totalFrames = clip.frameIndices.size();
                    animation.currentFrame = (animation.currentFrame + 1) % totalFrames;
                }
            } else if (entity->hasComponent<Animation>() && entity->hasComponent<Velocity>() && entity->hasComponent<ProjectileTag>()) {
                auto& animation = entity->getComponent<Animation>();
                auto& velocity = entity->getComponent<Velocity>();

                std::string newClip;

                newClip = "idle_right";
                //check for anim switch
                if (newClip != animation.currentClip) {
                    animation.currentClip = newClip;
                    animation.time = 0.0f;
                    animation.currentFrame =0;
                }

                float animationFrameSpeed = animation.speed;
                auto clip = animation.clips[animation.currentClip];

                animation.time += deltaTime;

                if (animation.time >= animationFrameSpeed) {
                    animation.time -= animationFrameSpeed;

                    std::size_t totalFrames = clip.frameIndices.size();
                    animation.currentFrame = (animation.currentFrame + 1) % totalFrames;
                }
            }
        }
    }
};

#endif //ADV_GAME_PROG_TECH_ANIMATIONSYSTEM_H