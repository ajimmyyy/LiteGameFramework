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
    static void Init();  // optional: 設定資源路徑
    static void Shutdown();

    // Loader
    static void SetModelLoader(std::shared_ptr<IModelLoader> loader);
    static void SetTextureLoader(std::shared_ptr<ITextureLoader> loader);

    // Model
    static std::shared_ptr<Model> LoadModel(const std::string& path);
    static std::shared_ptr<Model> GetModel(const std::string& path);
    //Texture
    static std::shared_ptr<Texture> LoadTexture(const std::string& path);
    static std::shared_ptr<Texture> GetTexture(const std::string& path);

private:
    inline static std::shared_ptr<IModelLoader> modelLoader = nullptr;
    inline static std::shared_ptr<ITextureLoader> textureLoader = nullptr;
    inline static std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;
    inline static std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;
};