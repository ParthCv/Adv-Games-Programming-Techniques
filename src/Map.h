//
// Created by parth on 9/9/2025.
//

#ifndef ADV_GAME_PROG_TECH_MAP_H
#define ADV_GAME_PROG_TECH_MAP_H

#include "Game.h"

class Map {
    public:
        Map();
        ~Map();

        void load(int data[10][15]);
        void draw();

    private:
        SDL_FRect src{}, dst{}; // brace initialization, all members would be set to 0
        SDL_Texture *water = nullptr;
        SDL_Texture *dirt = nullptr;
        SDL_Texture *ball = nullptr;
        SDL_Texture *grass = nullptr;

        int map[10][15]{};
};

#endif //ADV_GAME_PROG_TECH_MAP_H