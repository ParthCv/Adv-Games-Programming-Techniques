//
// Created by parth on 10/14/2025.
//

#include "AssetManager.h"

#include "../vendor/tinyxml2.h"

std::unordered_map<std::string, Animation> AssetManager::animations;

void AssetManager::loadAnimation(const std::string &clipName, const char *path) {
    Animation animation = loadAnimationFromXML(path);
    animations[clipName] = animation;
}

const Animation &AssetManager::getAnimation(const std::string &clipName) {
    return animations[clipName];
}

Animation AssetManager::loadAnimationFromXML(const char *path) {
    Animation animation;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto* root = doc.FirstChildElement("animations");
    for (auto* clipElem = root->FirstChildElement(); clipElem; clipElem = clipElem->NextSiblingElement()) {
        std::string clipName = clipElem->Name();
        AnimationClip clip;

        for (auto *framElem = clipElem->FirstChildElement("frame"); framElem; framElem = framElem->NextSiblingElement("frame")) {
            SDL_FRect rect;
            framElem->QueryFloatAttribute("x", &rect.x);
            framElem->QueryFloatAttribute("y", &rect.y);
            framElem->QueryFloatAttribute("w", &rect.w);
            framElem->QueryFloatAttribute("h", &rect.h);

            clip.frameIndices.push_back(rect);
        }

        animation.clips[clipName] = clip;
    }

    if (!animation.clips.empty()) {
        animation.currentClip = animation.clips.begin()->first;
    }

    return animation;
}


