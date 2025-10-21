//
// Created by parth on 10/14/2025.
//

#ifndef ADV_GAME_PROG_TECH_ASSETMANAGER_H
#define ADV_GAME_PROG_TECH_ASSETMANAGER_H
#include <string>
#include <unordered_map>

#include "../ecs/Component.h"

class AssetManager {
  static std::unordered_map<std::string, Animation> animations;
  static Animation loadAnimationFromXML(const char *path);

public:
  static void loadAnimation(const std::string& clipName, const char *path);
  static const Animation& getAnimation(const std::string& clipName);
};

#endif //ADV_GAME_PROG_TECH_ASSETMANAGER_H