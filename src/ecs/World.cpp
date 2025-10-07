//
// Created by parth on 10/2/2025.
//

#include "World.h"

#include <iostream>

void onCollision(const CollisionEvent& collision) {
    if (collision.entityA == nullptr || collision.entityB == nullptr) return;

    if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

    auto& colliderA = collision.entityA->getComponent<Collider>();
    auto& colliderB = collision.entityB->getComponent<Collider>();
    std::cout << "Collision occurred between " << colliderA.tag << " and " << colliderB.tag << "." << std::endl;
}

World::World() {
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision) {
        if (collision.entityA == nullptr || collision.entityB == nullptr) return;

        if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;

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

    });

    eventManager.subscribe<CollisionEvent>(onCollision);
}