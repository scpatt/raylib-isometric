//
// Created by Sam.Patterson on 31/05/2025.
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <ranges>
#include <string>
#include <unordered_map>

#include "raylib.h"

class TextureManager {
private:
    std::unordered_map<std::string, Texture2D> textureMap;

    TextureManager() = default;

public:
    static TextureManager& getInstance() {
        static TextureManager instance;

        return instance;
    }

    TextureManager(const TextureManager&) = delete;
    void operator=(const TextureManager&) = delete;

    Texture2D loadTexture(const std::string& path) {
        auto it = textureMap.find(path);

        if (it != textureMap.end()) {
            return it->second;
        }

        const Texture2D texture = LoadTexture(path.c_str());

        textureMap[path] = texture;

        return texture;
    }

    Texture2D getTexture(const std::string& path) {
        auto it = textureMap.find(path);

        if (it != textureMap.end()) {
            return it->second;
        }

        return loadTexture(path);
    }

    void unloadTextures() {
        for (auto &val: textureMap | std::views::values) {
            UnloadTexture(val);
        }

        textureMap.clear();
    }
};

#endif //TEXTURE_MANAGER_H
