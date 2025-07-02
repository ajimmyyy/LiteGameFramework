//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Platform/WindowGLFW.h"

#include <stdexcept>

WindowGLFW::WindowGLFW(int width, int height, const std::string& title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
}

WindowGLFW::~WindowGLFW() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void WindowGLFW::makeContextCurrent() {
    glfwMakeContextCurrent(window);
}

void WindowGLFW::swapBuffers() {
    glfwSwapBuffers(window);
}

bool WindowGLFW::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void WindowGLFW::pollEvents() {
    glfwPollEvents();
}

void WindowGLFW::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void* WindowGLFW::getNativeHandle() {
    return static_cast<void*>(window);
}

GLFWwindow* WindowGLFW::getWindow() const {
    return window;
}
