//
// Created by jimmy on 2025/6/27.
//

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "IModelLoader.h"
#include "ITextureLoader.h"
#include "Model.h"
#include "Texture.h"

class ResourceManager {
public:
    static bool init();  // optional: 設定資源路徑
    static void shutdown();

    // Loader
    static void setModelLoader(std::shared_ptr<IModelLoader> loader);
    static void setTextureLoader(std::shared_ptr<ITextureLoader> loader);

    // Model
    static std::shared_ptr<Model> loadModel(const std::string& path);
    static std::shared_ptr<Model> getModel(const std::string& path);
    //Texture
    static std::shared_ptr<Texture> loadTexture(const std::string& path);
    static std::shared_ptr<Texture> getTexture(const std::string& path);

private:
    inline static std::shared_ptr<IModelLoader> modelLoader = nullptr;
    inline static std::shared_ptr<ITextureLoader> textureLoader = nullptr;
    inline static std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;
    inline static std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;
};