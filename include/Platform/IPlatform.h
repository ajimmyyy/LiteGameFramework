//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include "IWindow.h"

class IPlatform {
public:
    virtual ~IPlatform() = default;
    virtual void pollEvents() = 0;
    [[nodiscard]] virtual bool shouldExit() const = 0;
    virtual void swapBuffers() = 0;
    [[nodiscard]] virtual IWindow* getWindow() const = 0;
};
