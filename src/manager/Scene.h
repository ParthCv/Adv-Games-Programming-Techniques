//
// Created by parth on 10/21/2025.
//

#ifndef ADV_GAME_PROG_TECH_SCENE_H
#define ADV_GAME_PROG_TECH_SCENE_H
#include <string>
#include <SDL3/SDL_events.h>

#include "../utils/Vector.h"
#include "../ecs/World.h"

class Scene {
public:
    Scene(const char* sceneName, const char* mapPath, const int windowWidth,const int windowHeight);

    void update(const float dt, const SDL_Event &e) {
        world.update(dt, e);
    }

    void render() {
        world.render();
    }

    World world;
    const std::string getName()const { return name; }
private:
    std::string name;
    void createProjectile(Vector2D pos, Vector2D dir, int speed);
};

#endif //ADV_GAME_PROG_TECH_SCENE_H