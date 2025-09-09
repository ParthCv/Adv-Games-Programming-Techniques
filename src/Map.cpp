//
// Created by parth on 9/9/2025.
//

#include "Map.h"
#include "TextureManager.h"

int mapData[10][15] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,2,2,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,2,2,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

Map::Map() :
water(TextureManager::load("../asset/water.png")),
dirt(TextureManager::load("../asset/dirt.png")),
grass(TextureManager::load("../asset/grass.png")){
    load(mapData);

    // source
    src.x = src.y = 0;
    src.w = src.h = 32;

    // destination
    dst.x = dst.y = 0;
    dst.w = dst.h = 64;
}

Map::~Map() {
    if (water) SDL_DestroyTexture(water);
    if (dirt) SDL_DestroyTexture(dirt);
    if (grass) SDL_DestroyTexture(grass);
}

void Map::load(int data[10][15]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            mapData[i][j] = data[i][j];
        }
    }
}

void Map::draw() {
    int type = 0;

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            type = mapData[row][col];

            dst.x = static_cast<float>(col) * 64;
            dst.y = static_cast<float>(row) * 64;

            switch (type) {
                case 0:
                    TextureManager::draw(water, src, dst);
                    break;
                case 1:
                    TextureManager::draw(dirt, src, dst);
                    break;
                case 2:
                    TextureManager::draw(grass, src, dst);
                    break;
                default:
                    break;
            }

        }
    }
}

