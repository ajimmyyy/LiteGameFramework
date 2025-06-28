//
// Created by jimmy on 2025/6/28.
//

#pragma once
#include <trompeloeil.hpp>
#include "../../include/Resources/ITextureLoader.h"

class MockTextureLoader : public ITextureLoader {
public:
    MAKE_MOCK1(LoadFromFile, Texture(const std::string&), override);
};
