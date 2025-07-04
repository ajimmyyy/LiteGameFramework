//
// Created by jimmy on 2025/6/30.
//

#pragma once

#include <memory>

#include "IPlatform.h"
#include "WindowGLFW.h"
#include "../Input/InputManager.h"

class PlatformGLFW : public IPlatform {
public:
    explicit PlatformGLFW(int width, int height, const std::string& title);

    void pollEvents() override;
    [[nodiscard]] bool shouldExit() const override;
    void swapBuffers() override;
    [[nodiscard]] WindowGLFW* getWindow() const override;
    [[nodiscard]] InputManager* getInputManager() const override;

private:
    std::unique_ptr<WindowGLFW> window;
    std::unique_ptr<InputManager> inputManager;
};
