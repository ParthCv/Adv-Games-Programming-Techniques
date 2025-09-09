//
// Created by parth on 9/9/2025.
//

#include "GameObject.h"

#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y) : x(x), y(y), texture(TextureManager::load(path)) {}

GameObject::~GameObject() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void GameObject::update(float deltaTime) {
    // Move object 1 pixel
    x += deltaTime * speed;
    y += deltaTime * speed;

    // start and where to crop
    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;

    destRect.x = static_cast<float>(x);
    destRect.y = static_cast<float>(y);

    destRect.w = destRect.h = 32;
}

void GameObject::draw() {
    TextureManager::draw(texture, srcRect, destRect);
}

