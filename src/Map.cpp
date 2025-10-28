//
// Created by parth on 9/9/2025.
//

#include "Map.h"

#include <cmath>
#include <iostream>

#include "TextureManager.h"
#include <sstream>
#include "vendor/tinyxml2.h"

void Map::load(const char *path, SDL_Texture *texture) {
    tileset = texture;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto mapNode = doc.FirstChildElement("map");
    width = mapNode->IntAttribute("width");
    height = mapNode->IntAttribute("height");

    auto* layer = mapNode->FirstChildElement("layer");
    auto* data = layer->FirstChildElement("data");
    std::string csv = data->GetText();
    std::stringstream ss(csv);

    tileData = std::vector(height, std::vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;
            if (!std::getline(ss, val, ',')) break;
            tileData[i][j] = std::stoi(val);
        }
    }

    for (auto* objectGroup = mapNode->FirstChildElement("objectgroup");
         objectGroup != nullptr;
         objectGroup = objectGroup->NextSiblingElement("objectgroup")) {
        const char* groupName = objectGroup->Attribute("name");
        if (!groupName) {
            std::cout << "Warning: Found objectgroup without name attribute, skipping" << std::endl;
            continue;
        }

        std::string groupNameStr(groupName);
        std::cout << "Processing object group: " << groupNameStr << std::endl;

        // Process Collision Layer
        if (groupNameStr == "Collision Layer") {
            for (auto* obj = objectGroup->FirstChildElement("object");
                 obj != nullptr;
                 obj = obj->NextSiblingElement("object")) {
                Collider collider;
                collider.rect.x = obj->FloatAttribute("x");
                collider.rect.y = obj->FloatAttribute("y");
                collider.rect.w = obj->FloatAttribute("width");
                collider.rect.h = obj->FloatAttribute("height");
                colliders.push_back(collider);
                 }
            std::cout << "  Loaded " << colliders.size() << " colliders" << std::endl;
        }

        else if (groupNameStr == "Item Layer" || groupNameStr == "ItemSpawns") {
            for (auto* obj = objectGroup->FirstChildElement("object");
                 obj != nullptr;
                 obj = obj->NextSiblingElement("object")) {
                Position spawn;
                spawn.x = obj->FloatAttribute("x");
                spawn.y = obj->FloatAttribute("y");
                itemSpawnPositions.push_back(spawn);
                 }
            std::cout << "  Loaded " << itemSpawnPositions.size() << " item spawn points" << std::endl;
        }

        else {
            std::cout << "  Unknown object group type: " << groupNameStr << " (skipping)" << std::endl;
        }
    }
}


void Map::draw(const Camera &camera) {

    SDL_FRect src{}, dst{};

    dst.w = 32;
    dst.h = 32;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int type = tileData[row][col];

            float worldX = static_cast<float>(col) * dst.w;
            float worldY = static_cast<float>(row) * dst.h;

            dst.x = std::round(worldX - camera.view.x);
            dst.y = std::round(worldY - camera.view.y);

            switch (type) {
                case 1:
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    continue;
            }

            TextureManager::draw(tileset, src, dst);
        }
    }
}

