//
// Created by jimmy on 2025/6/28.
//

#pragma once

class System {
public:
    virtual ~System() = default;
    virtual void update() = 0;
};