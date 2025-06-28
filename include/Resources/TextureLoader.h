//
// Created by jimmy on 2025/6/27.
//

#pragma once

#include <string>

#include "ITextureLoader.h"
#include "Texture.h"

class TextureLoader : public ITextureLoader {
public:
    // 載入並建立 OpenGL 紋理，回傳 Texture 結構
    static Texture LoadFromFile(const std::string& path);

private:
};

