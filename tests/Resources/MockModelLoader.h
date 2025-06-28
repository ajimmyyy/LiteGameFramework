//
// Created by jimmy on 2025/6/28.
//

#pragma once
#include <trompeloeil.hpp>
#include "../../include/Resources/IModelLoader.h"

class MockModelLoader : public IModelLoader {
public:
    MAKE_MOCK1(LoadFromOBJ, Model(const std::string&), override);
};
