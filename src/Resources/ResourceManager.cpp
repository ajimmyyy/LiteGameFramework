//
// Created by jimmy on 2025/6/27.
//

#include "../../include/Resources/ResourceManager.h"
#include "../../include/Resources/ModelLoader.h"
#include "../../include/Resources/TextureLoader.h"
#include "../../include/Resources/AudioLoader.h"

void ResourceManager::Init() {
    // 可設定 basePath、讀取設定檔等
}

void ResourceManager::Shutdown() {
    modelCache.clear();
    textureCache.clear();
}

void ResourceManager::SetModelLoader(std::shared_ptr<IModelLoader> loader) {
    modelLoader = std::move(loader);
}

void ResourceManager::SetTextureLoader(std::shared_ptr<ITextureLoader> loader) {
    textureLoader = std::move(loader);
}

std::shared_ptr<Model> ResourceManager::LoadModel(const std::string& path) {
    auto it = modelCache.find(path);
    if (it != modelCache.end())
        return it->second;

    Model m = modelLoader->LoadFromOBJ(path);
    auto ptr = std::make_shared<Model>(std::move(m));
    modelCache[path] = ptr;
    return ptr;
}

std::shared_ptr<Model> ResourceManager::GetModel(const std::string& path) {
    auto it = modelCache.find(path);
    if (it != modelCache.end())
        return it->second;
    return nullptr;
}

// Texture
std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;

    Texture t = textureLoader->LoadFromFile(path);
    auto ptr = std::make_shared<Texture>(std::move(t));
    textureCache[path] = ptr;
    return ptr;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end())
        return it->second;
    return nullptr;
}
