//
// Created by jimmy on 2025/6/30.
//

#pragma once

class ITime {
public:
    virtual ~ITime() = default;
    virtual float getTime() const = 0;
};
