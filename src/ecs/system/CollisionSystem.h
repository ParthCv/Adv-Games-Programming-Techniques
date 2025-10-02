//
// Created by parth on 10/2/2025.
//

#ifndef ADV_GAME_PROG_TECH_COLLISIONSYSTEM_H
#define ADV_GAME_PROG_TECH_COLLISIONSYSTEM_H
#include "../Entity.h"
#include <vector>
#include <memory>


class World;

class CollisionSystem {
public:
    void update(World& world);
private:
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);
};

#endif //ADV_GAME_PROG_TECH_COLLISIONSYSTEM_H