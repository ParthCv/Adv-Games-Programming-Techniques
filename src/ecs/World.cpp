//
// Created by parth on 10/2/2025.
//

#include "World.h"
#include "../Game.h"

#include <iostream>

void onCollision(const CollisionEvent& collision) {
    if (collision.entityA == nullptr || collision.entityB == nullptr) return;

    if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

    auto& colliderA = collision.entityA->getComponent<Collider>();
    auto& colliderB = collision.entityB->getComponent<Collider>();
    // std::cout << "Collision occurred between " << colliderA.tag << " and " << colliderB.tag << "." << std::endl;
}

World::World() {
    eventManager.subscribe([this](const CollisionEvent& collision) {

        Entity* sceneStateEntity = nullptr;

        for (auto& e:entities) {
           if(e->hasComponent<SceneState>()) {
               sceneStateEntity = e.get();
               break;
           }
        }

        if (sceneStateEntity == nullptr) return;

        if (collision.entityA == nullptr || collision.entityB == nullptr) return;

        if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;
        Entity* projectile = nullptr;

        if (colliderA.tag == "Player" && colliderB.tag == "Coin") {
            player = collision.entityA;
            item = collision.entityB;
        } else if (colliderB.tag == "Player" && colliderA.tag == "Coin") {
            player = collision.entityB;
            item = collision.entityA;
        }

        if (player && item) {
            std::cout << "Coin destroyed" << std::endl;
            item->destroy();
            auto& sceneState = sceneStateEntity->getComponent<SceneState>();
            sceneState.coinsCollected++;

            if (sceneState.coinsCollected > 1) {
                std::cout << "level2" << std::endl;
                Game::onSceneChangeRequest("level2");
            }
        }


        if (colliderA.tag == "Player" && colliderB.tag == "Wall") {
            player = collision.entityA;
            wall = collision.entityB;
        } else if (colliderB.tag == "Player" && colliderA.tag == "Wall") {
            player = collision.entityB;
            wall = collision.entityA;
        }

        if (player && wall) {
            std::cout << "Player collided with wall" << std::endl;
            auto& transform = player->getComponent<Transform>();
            transform.position = transform.oldPosition;
        }

        if (colliderA.tag == "Player" && colliderB.tag == "projectile") {
            player = collision.entityA;
            projectile = collision.entityB;
        } else if (colliderB.tag == "Player" && colliderA.tag == "projectile") {
            player = collision.entityB;
            projectile = collision.entityA;
        }

        if (player && projectile) {
            player->destroy();
            std::cout << "game over"<< std::endl;
            Game::onSceneChangeRequest("gameover");
        }

    });

    eventManager.subscribe(onCollision);
}