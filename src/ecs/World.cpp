//
// Created by parth on 10/2/2025.
//

#include "World.h"

#include <iostream>

World::World() {
    eventManager.subscribe<CollisionEvent>([](const CollisionEvent& collision) {
    if (collision.entityA == nullptr || collision.entityB == nullptr) return;

    if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

    auto& colliderA = collision.entityA->getComponent<Collider>();
    auto& colliderB = collision.entityB->getComponent<Collider>();

    Entity* player = nullptr;
    Entity* item = nullptr;

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
});
}
