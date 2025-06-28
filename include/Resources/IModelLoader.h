//
// Created by jimmy on 2025/6/28.
//

#pragma once
#include <string>
#include "Model.h"

struct IModelLoader {
    virtual ~IModelLoader() = default;
    virtual Model LoadFromOBJ(const std::string& path) = 0;
};