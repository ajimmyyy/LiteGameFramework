//
// Created by jimmy on 2025/6/27.
//

#pragma once
#include <string>

struct AudioClip {
    unsigned int bufferId = 0;
    float duration = 0.0f;
    std::string path;
};
