//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>

#include "IPlatform.h"
#include "ITime.h"
#include "../Renderer/IRenderer.h"

struct PlatformEnv {
    std::unique_ptr<IPlatform> platform;
    std::unique_ptr<ITime> time;
    std::unique_ptr<IRenderer> renderer;
};
