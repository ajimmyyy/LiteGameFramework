//
// Created by jimmy on 2025/7/4.
//

#pragma once
#include <functional>
#include <string>

#include "glm/glm.hpp"

struct TextComponent {
    std::string content;
    glm::vec2 screenPosition;
    glm::vec3 color = {0.0f, 0.0f, 0.0f};
    float scale = 1.0f;
    bool visible = true;

    std::function<std::string()> generator;
};
