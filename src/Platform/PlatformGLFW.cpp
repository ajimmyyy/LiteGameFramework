//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Platform/PlatformGLFW.h"

PlatformGLFW::PlatformGLFW(int width, int height, const std::string& title) {
    window = std::make_unique<WindowGLFW>(width, height, title);
    window->makeContextCurrent();
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
