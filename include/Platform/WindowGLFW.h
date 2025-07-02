//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <string>

#include "IWindow.h"
#include "GLFW/glfw3.h"

class WindowGLFW : public IWindow {
public:
    WindowGLFW(int width, int height, const std::string& title);
    ~WindowGLFW() override;

    void makeContextCurrent() override;
    void swapBuffers() override;
    [[nodiscard]] bool shouldClose() const override;
    void pollEvents() override;
    void shutdown() override;
    void* getNativeHandle() override;
    [[nodiscard]] GLFWwindow* getWindow() const;

private:
    GLFWwindow* window;
};

