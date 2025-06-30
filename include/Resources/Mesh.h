//
// Created by jimmy on 2025/6/26.
//

#pragma once
#include <vector>
#include "Vertex.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
