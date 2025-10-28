//
// Created by parth on 10/21/2025.
//

#ifndef ADV_GAME_PROG_TECH_SCENEMANAGER_H
#define ADV_GAME_PROG_TECH_SCENEMANAGER_H
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Scene.h"

struct SceneParams {
    std::string name;           // Changed from const char* to std::string
    std::string mapPath;        // Changed from const char* to std::string
    int windowWidth;            // Removed const
    int windowHeight;           // Removed const
};

class SceneManager {
    std::unordered_map<std::string, SceneParams> scenesParams;
    std::string pendingScene;

    void changeScene(const std::string& sceneName) {
        auto it = scenesParams.find(sceneName);
        if (it != scenesParams.end()) {
            const auto& scene = it->second;
            currentScene = std::make_unique<Scene>(
                scene.name.c_str(),      // Convert back to const char*
                scene.mapPath.c_str(),   // Convert back to const char*
                scene.windowWidth,
                scene.windowHeight);
        } else {
            std::cout << "Scene not found: " << sceneName << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;

    void loadScene(const char* sceneName, const char* mapPath, int windowWidth, int windowHeight) {
        scenesParams[sceneName] = {sceneName, mapPath, windowWidth, windowHeight};
    }

    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(float dt, const SDL_Event& e) {
        if (currentScene) currentScene->update(dt, e);
        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() {
        if (currentScene) currentScene->render();
    }
};

#endif //ADV_GAME_PROG_TECH_SCENEMANAGER_H