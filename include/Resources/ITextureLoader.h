//
// Created by jimmy on 2025/6/28.
//

#pragma once
#include <string>
#include "Texture.h"

struct ITextureLoader {
    virtual ~ITextureLoader() = default;
    virtual Texture LoadFromFile(const std::string& path) = 0;
};
