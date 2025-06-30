//
// Created by jimmy on 2025/6/29.
//

#pragma once
#include "glad/glad.h"

struct GLMeshResource {
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei indexCount = 0;
};
