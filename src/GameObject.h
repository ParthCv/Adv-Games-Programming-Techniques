//
// Created by parth on 9/9/2025.
//

#ifndef ADV_GAME_PROG_TECH_GAMEOBJECT_H
#define ADV_GAME_PROG_TECH_GAMEOBJECT_H

#include "Game.h"

class GameObject {
public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update();
    void draw();

private:
    int x{}, y{};
    SDL_Texture* texture{nullptr};
    SDL_FRect srcRect{}, destRect{};

};

#endif //ADV_GAME_PROG_TECH_GAMEOBJECT_H