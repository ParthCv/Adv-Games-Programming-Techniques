//
// Created by parth on 9/9/2025.
//

#include "TextureManager.h"

#include <iostream>
#include <ostream>

// Doesnt create any new memory just grabs it from memory
extern Game* game;

SDL_Texture *TextureManager::load(const char *path) {
    // Create a surface, which is an image in RAM, we put in ram so we can do something to th image before
    // we store it in GPU

    SDL_Surface* tempSurface = IMG_Load(path);
    if (!tempSurface) {
        std::cout << "Failed to load image: " << path << std::endl;
    }

    // Texture is the image stored in VRAM
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    SDL_DestroySurface(tempSurface);

    return texture;
}

void TextureManager::draw(SDL_Texture *texture, SDL_FRect src, SDL_FRect dst) {
    // draw the texture to screen from VRAM
    SDL_RenderTexture(game->renderer, texture, &src, &dst);
}



