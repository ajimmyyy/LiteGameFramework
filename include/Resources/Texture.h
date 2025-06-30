//
// Created by jimmy on 2025/6/27.
//

#pragma once
#include <vector>

struct Texture {
    int width;
    int height;
    int channels;
    std::vector<unsigned char> pixels;
    std::string name;
};

