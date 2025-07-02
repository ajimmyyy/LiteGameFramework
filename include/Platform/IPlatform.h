//
// Created by jimmy on 2025/6/30.
//

#pragma once

class IPlatform {
public:
    virtual ~IPlatform() = default;
    virtual void pollEvents() = 0;
    virtual bool shouldExit() const = 0;
    virtual void swapBuffers() = 0;
};
