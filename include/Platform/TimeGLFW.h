//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include "ITime.h"

class TimeGLFW : public ITime {
public:
    [[nodiscard]] float getTime() const override;
};