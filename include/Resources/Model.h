//
// Created by jimmy on 2025/6/26.
//

#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

struct Model {
    std::string name;
    std::vector<Mesh> meshes;
};
