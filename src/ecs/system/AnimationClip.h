//
// Created by parth on 10/14/2025.
//

#ifndef ADV_GAME_PROG_TECH_ANIMATIONCLIP_H
#define ADV_GAME_PROG_TECH_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndices;
};

#endif //ADV_GAME_PROG_TECH_ANIMATIONCLIP_H