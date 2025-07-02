//
// Created by jimmy on 2025/7/1.
//

#include <fstream>
#include <iostream>
#include <json.hpp>
#include "../../include/Utils/Config.h"

using json = nlohmann::json;

Config Config::load(const std::string& path) {
    Config config;
    std::ifstream file(path);
    if (!file) {
        std::cerr << "[Config] Failed to open " << path << ". Using default config.\n";
        return config;
    }

    try {
        json j;
        file >> j;

        config.windowWidth = j["window"]["width"].get<int>();
        config.windowHeight = j["window"]["height"].get<int>();
        config.windowTitle = j["window"]["title"].get<std::string>();

        std::string platformStr = j["platform"].get<std::string>();
        if (platformStr == "OpenGL") config.platformType = PlatformType::OpenGL;
        else config.platformType = PlatformType::Unknown;

    } catch (std::exception& e) {
        std::cerr << "[Config] Error parsing JSON: " << e.what() << ". Using defaults.\n";
    }

    return config;
}

int Config::getWindowWidth() const { return windowWidth; }

int Config::getWindowHeight() const { return windowHeight; }

const std::string& Config::getWindowTitle() const { return windowTitle; }

PlatformType Config::getPlatformType() const { return platformType; }