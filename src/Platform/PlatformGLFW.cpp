//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Platform/PlatformGLFW.h"
#include "../../include/Input/InputAdapterGLFW.h"

PlatformGLFW::PlatformGLFW(int width, int height, const std::string& title) {
    window = std::make_unique<WindowGLFW>(width, height, title);
    window->makeContextCurrent();

    GLFWwindow* native = static_cast<GLFWwindow*>(window->getNativeHandle());
    glfwSetWindowUserPointer(native, this);

    inputManager = std::make_unique<InputManager>();

    glfwSetKeyCallback(native, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto platform = static_cast<PlatformGLFW*>(glfwGetWindowUserPointer(win));
        KeyCode code = glfwKeyToKeyCode(key);

        if (code == KeyCode::Unknown) return;

        if (platform && platform->inputManager) {
            bool isDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
            platform->inputManager->onKey(code, isDown);
        }
    });

    glfwSetCursorPosCallback(native, [](GLFWwindow* win, double xpos, double ypos) {
        auto platform = static_cast<PlatformGLFW*>(glfwGetWindowUserPointer(win));
        if (platform && platform->inputManager) {
            platform->inputManager->onMouseMove(xpos, ypos);
        }
    });
}

void PlatformGLFW::pollEvents() {
    window->pollEvents();
}

bool PlatformGLFW::shouldExit() const {
    return window->shouldClose();
}

void PlatformGLFW::swapBuffers() {
    window->swapBuffers();
}

WindowGLFW* PlatformGLFW::getWindow() const {
    return window.get();
}

InputManager* PlatformGLFW::getInputManager() const {
    return inputManager.get();
}