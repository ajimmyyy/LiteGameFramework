//
// Created by jimmy on 2025/7/1.
//

#pragma once

class IRenderSystem {
public:
    virtual ~IRenderSystem() = default;
    virtual void render(float alpha) = 0;
};