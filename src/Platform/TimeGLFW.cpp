//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Platform/TimeGLFW.h"
#include <GLFW/glfw3.h>

float TimeGLFW::getTime() const {
    return static_cast<float>(glfwGetTime());
}