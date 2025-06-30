//
// Created by jimmy on 2025/6/29.
//

#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLMeshResource.h"
#include "IRenderer.h"
#include "../resources/Model.h"
#include "../resources/Texture.h"

class OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer() override;

    bool initialize() override;
    void shutdown() override;

    void draw(Model& model, const Texture& texture) override;

private:
    GLFWwindow* window = nullptr;

    // Shader
    GLuint shaderProgram = 0;

    // MVP
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    //Cache
    std::unordered_map<std::string, GLuint> textureCache;
    std::unordered_map<const Mesh*, GLMeshResource> meshResourceCache;

    bool setupWindow();
    bool setupShaders();
    void uploadMesh(Mesh& mesh);
    GLuint uploadTexture(const Texture& texture);
};

