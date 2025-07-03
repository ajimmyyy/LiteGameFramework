//
// Created by jimmy on 2025/6/27.
//

#include "../../include/Resources/ResourceManager.h"

#include <iostream>

#include "../../include/Resources/ModelLoader.h"
#include "../../include/Resources/TextureLoader.h"
#include "../../include/Resources/AudioLoader.h"

bool ResourceManager::init() {
    setModelLoader(std::make_shared<ModelLoader>());
    setTextureLoader(std::make_shared<TextureLoader>());
    return true;
}

void ResourceManager::shutdown() {
    modelCache.clear();
    textureCache.clear();

    modelLoader.reset();
    textureLoader.reset();
}

void ResourceManager::setModelLoader(std::shared_ptr<IModelLoader> loader) {
    modelLoader = std::move(loader);
}

void ResourceManager::setTextureLoader(std::shared_ptr<ITextureLoader> loader) {
    textureLoader = std::move(loader);
}

std::shared_ptr<Model> ResourceManager::loadModel(const std::string& path) {
    auto it = modelCache.find(path);
    if (it != modelCache.end())
        return it->second;

    try {
        Model m = modelLoader->loadFromOBJ(path);
        auto ptr = std::make_shared<Model>(std::move(m));
        modelCache[path] = ptr;
        return ptr;
    } catch (const std::exception& e) {
        std::cerr << "[ResourceManager] Failed to load model: " << path << "\n";
        return nullptr;
    }
}

std::shared_ptr<Model> ResourceManager::getModel(const std::string& path) {
    auto it = modelCache.find(path);
    if (it != modelCache.end())
        return it->second;
    return nullptr;
}

// Texture
std::shared_ptr<Texture> ResourceManager::loadTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;

    try {
        Texture t = textureLoader->loadFromFile(path);
        auto ptr = std::make_shared<Texture>(std::move(t));
        textureCache[path] = ptr;
        return ptr;
    } catch (const std::exception& e) {
        std::cerr << "[ResourceManager] Failed to load texture: " << path << "\n";
        return nullptr;
    }
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;
    return nullptr;
}
