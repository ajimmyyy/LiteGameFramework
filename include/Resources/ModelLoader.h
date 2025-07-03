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
    Model loadFromOBJ(const std::string& path) override;
};
