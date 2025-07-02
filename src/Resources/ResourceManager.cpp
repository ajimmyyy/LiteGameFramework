//
// Created by jimmy on 2025/6/27.
//

#include "../../include/Resources/ResourceManager.h"
#include "../../include/Resources/ModelLoader.h"
#include "../../include/Resources/TextureLoader.h"
#include "../../include/Resources/AudioLoader.h"

void ResourceManager::init() {
    // 可設定 basePath、讀取設定檔等
}

void ResourceManager::shutdown() {
    modelCache.clear();
    textureCache.clear();
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

    Model m = modelLoader->loadFromOBJ(path);
    auto ptr = std::make_shared<Model>(std::move(m));
    modelCache[path] = ptr;
    return ptr;
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

    Texture t = textureLoader->loadFromFile(path);
    auto ptr = std::make_shared<Texture>(std::move(t));
    textureCache[path] = ptr;
    return ptr;
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;
    return nullptr;
}
