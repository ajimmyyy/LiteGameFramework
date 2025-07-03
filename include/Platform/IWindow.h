//
// Created by jimmy on 2025/6/30.
//

#pragma once

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void makeContextCurrent() = 0;
    virtual void swapBuffers() = 0;
    [[nodiscard]] virtual bool shouldClose() const = 0;
    virtual void pollEvents() = 0;
    virtual void shutdown() = 0;
    virtual void getSize(int& width, int& height) const = 0;

    virtual void* getNativeHandle() = 0;
};
