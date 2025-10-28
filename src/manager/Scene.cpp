//
// Created by parth on 10/21/2025.
//

#include "Scene.h"

#include <iostream>

#include "AssetManager.h"

Scene::Scene(const char *sceneName, const char *mapPath,const int windowWidth,const int windowHeight): name(sceneName) {
    // load map
    world.getMap().load(mapPath, TextureManager::load("../asset/spritesheet.png"));

    auto& camera = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    camera.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    // Add colliders
    for (auto &collider_data : world.getMap().colliders) {
        auto& entity = world.createEntity();
        entity.addComponent<Transform>(Vector2D(collider_data.rect.x, collider_data.rect.y), 0.0f, 1.0f);
        auto& collider = entity.addComponent<Collider>("W");

        collider.rect.x = collider_data.rect.x;
        collider.rect.y = collider_data.rect.y;
        collider.rect.w = collider_data.rect.w;
        collider.rect.h = collider_data.rect.h;

        SDL_Texture* texture = TextureManager::load("../asset/spritesheet.png");
        SDL_FRect source {0, 32, 32, 32};
        SDL_FRect destination {collider.rect.x, collider.rect.y, collider.rect.w, collider.rect.h};
        //entity.addComponent<Sprite>(texture, source, destination);
    }

    // Add Items
    for (auto &item_spawn_position : world.getMap().itemSpawnPositions) {
        auto& item (world.createEntity());
        auto& itemTransform = item.addComponent<Transform>(Vector2D(item_spawn_position.x,item_spawn_position.y), 0.0f, 1.0f);

        SDL_Texture *itemTexture = TextureManager::load("../asset/coin.png");
        SDL_FRect itemSrcRect = {0,0,32,32};
        SDL_FRect itemDstRect = {itemTransform.position.x,itemTransform.position.y,32,32};

        item.addComponent<Sprite>(itemTexture, itemSrcRect, itemDstRect);
        auto& itemCollider = item.addComponent<Collider>("Coin");
        itemCollider.rect.x = item_spawn_position.x;  // ADD THIS
        itemCollider.rect.y = item_spawn_position.y;  // ADD THIS
        itemCollider.rect.w = itemDstRect.w;
        itemCollider.rect.h = itemDstRect.h;
    }

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(400,400), 0.0f, 1.0f);

    Animation animation = AssetManager::getAnimation("player");
    player.addComponent<Animation>(animation);

    SDL_Texture *texture = TextureManager::load("../asset/animations/Rooster_animation_with_shadow.png");
    SDL_FRect playerSrcRect = animation.clips[animation.currentClip].frameIndices[0];
    SDL_FRect playerDstRect = {playerTransform.position.x,playerTransform.position.y,64,64};

    player.addComponent<Velocity>(Vector2D(0.0,0.0), 120.0f);
    player.addComponent<Sprite>(texture, playerSrcRect, playerDstRect);

    auto& playerCollider = player.addComponent<Collider>("Player");
    playerCollider.rect.w = playerDstRect.w;
    playerCollider.rect.h = playerDstRect.h;

    player.addComponent<PlayerTag>();

    auto& spawner(world.createEntity());
    Transform transform = spawner.addComponent<Transform>(Vector2D(windowWidth/2, windowHeight - 5), 0.0f, 1.0f);

    Entity* spawnPtr = &spawner;

    spawner.addComponent<TimedSpawner>(2.0f, [this, spawnPtr] {
        std::cout << "Spawning" << std::endl;
        if (!spawnPtr->isActive()) return;

        auto& transform = spawnPtr->getComponent<Transform>();
        auto& e(world.createDeferredEntity());
        std::cout << "Entity created"<< std::endl;
        e.addComponent<Transform>(Vector2D(100,150), 0.0f, 1.0f);
        e.addComponent<Velocity>(Vector2D(0.0f, -1.0f), 100.0f);

        Animation animation = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(animation);

        SDL_Texture* texture = TextureManager::load("../asset/animations/bird_anim.png");
        SDL_FRect src = {0,0,32,32};
        SDL_FRect dest = {transform.position.x,transform.position.y,32,32};
        e.addComponent<Sprite>(texture, src, dest);

        Collider collider = e.addComponent<Collider>("projectile");
        collider.rect.w = dest.w;
        collider.rect.h = dest.h;

        e.addComponent<ProjectileTag>();

        std::cout << "Entity fully configured!" << std::endl;
    });


    auto &state(world.createEntity());
    state.addComponent<SceneState>();
}
