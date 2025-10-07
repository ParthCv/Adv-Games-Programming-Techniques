//
// Created by parth on 9/9/2025.
//

#ifndef ADV_GAME_PROG_TECH_MAP_H
#define ADV_GAME_PROG_TECH_MAP_H

#include <vector>
#include <SDL3/SDL.h>
#include "./ecs/Component.h"

class Map {
    public:
        Map() = default;
        ~Map() = default;

        void load(const char *path, SDL_Texture *texture);
        void draw();

        SDL_Texture *tileset = nullptr;
        int width{}, height{};
        std::vector<std::vector<int>> tileData;
        std::vector<Collider> colliders;
        std::vector<Position> itemSpawnPositions;

    private:
        SDL_FRect src{}, dst{}; // brace initialization, all members would be set to 0
};

#endif //ADV_GAME_PROG_TECH_MAP_H