//
// Created by jimmy on 2025/7/1.
//

#pragma once

#include <string>

#include "PlatformType.h"

class Config {
public:
    static Config load(const std::string& path);

    [[nodiscard]] int getWindowWidth() const;
    [[nodiscard]] int getWindowHeight() const;
    [[nodiscard]] const std::string& getWindowTitle() const;

    [[nodiscard]] PlatformType getPlatformType() const;

private:
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string windowTitle = "Game";

    PlatformType platformType = PlatformType::OpenGL;
};

