//
// Created by jimmy on 2025/6/28.
//

#pragma once

class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void update(float deltaTime) = 0;
};