//
// Created by jimmy on 2025/6/26.
//

#pragma once
#include <functional>
#include <string>

#include "IModelLoader.h"
#include "Model.h"
#include "../Platform/FileSystem.h"

class ModelLoader : public IModelLoader {
public:
    using ReadTextFunc = std::function<std::string(const std::string&)>;
    static Model loadFromOBJ(const std::string& path, ReadTextFunc readFunc = FileSystem::readTextFile);
};
