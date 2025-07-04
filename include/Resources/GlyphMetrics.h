//
// Created by jimmy on 2025/7/4.
//

#pragma once
#include "glm/glm.hpp"

struct GlyphMetrics {
    glm::ivec2 size;     // 字元寬高
    glm::ivec2 bearing;  // 與基線的偏移
    uint32_t advance;    // 下一個字元的位置偏移 (位移單位為1/64像素)
};
