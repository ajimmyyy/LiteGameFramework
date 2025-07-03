//
// Created by jimmy on 2025/7/3.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct CameraComponent {
    glm::vec3 position{0.0f, 0.0f, 5.0f};
    glm::vec3 target{0.0f, 0.0f, 0.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    float fov = 45.0f;
    float aspect = 4.0f / 3.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    void updateMatrices() {
        viewMatrix = glm::lookAt(position, target, up);
        projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    }
};

