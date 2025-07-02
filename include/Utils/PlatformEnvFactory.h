//
// Created by jimmy on 2025/6/30.
//

#pragma once

#include <string>

#include "../Platform/PlatformEnv.h"
#include "PlatformType.h"

class PlatformEnvFactory {
public:
    static PlatformEnv create(PlatformType type, int width, int height, const std::string& title);
};
