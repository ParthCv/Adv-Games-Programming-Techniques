//
// Created by parth on 9/9/2025.
//

#ifndef ADV_GAME_PROG_TECH_TEXTUREMANAGER_H
#define ADV_GAME_PROG_TECH_TEXTUREMANAGER_H

#include <string>
#include <unordered_map>

#include "SDL3_Image/SDL_image.h"

class TextureManager {
    static std::unordered_map<std::string, SDL_Texture*> textures;
public:
    static SDL_Texture* load(const char* path);

    // FLoating point rects, basically rect hv x,y,width and height
    static void draw(SDL_Texture* texture, SDL_FRect src, SDL_FRect dst);
    static void clean();
};

#endif //ADV_GAME_PROG_TECH_TEXTUREMANAGER_H