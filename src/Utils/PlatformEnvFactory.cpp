//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Platform/PlatformEnv.h"
#include "../../include/Utils/PlatformEnvFactory.h"
#include "../../include/Renderer/OpenGLRenderer.h"
#include "../../include/Platform/PlatformGLFW.h"
#include "../../include/Platform/TimeGLFW.h"
#include "../../include/Platform/WindowGLFW.h"

#include <iostream>

PlatformEnv PlatformEnvFactory::create(
    PlatformType type,
    int width,
    int height,
    const std::string& title
) {
    PlatformEnv env;

    switch (type) {
        case PlatformType::OpenGL: {
            auto platform = std::make_unique<PlatformGLFW>(width, height, title);
            env.renderer = std::make_unique<OpenGLRenderer>(platform->getWindow());
            env.platform = std::move(platform);
            env.time     = std::make_unique<TimeGLFW>();
            break;
        }
        default:
            std::cerr << "[PlatformEnvFactory] Unsupported platform.\n";
    }

    return env;
}
