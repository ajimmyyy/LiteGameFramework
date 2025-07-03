//
// Created by jimmy on 2025/6/29.
//

#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GLMeshResource.h"
#include "IRenderer.h"
#include "../resources/Model.h"
#include "../resources/Texture.h"
#include "../Platform/WindowGLFW.h"

class OpenGLRenderer : public IRenderer {
public:
    explicit OpenGLRenderer(WindowGLFW* win);
    ~OpenGLRenderer() override;

    void beginFrame() override;
    void endFrame() override;

    bool initialize() override;
    void shutdown() override;

    void draw(Model& model, const Texture& texture) override;
    void draw(Model& model) override;

    void setViewMatrix(const glm::mat4& view, const glm::mat4& projection) override;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
    WindowGLFW* window = nullptr;

    // Shader
    GLuint shaderProgram = 0;

    // MVP
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    //Cache
    std::unordered_map<std::string, GLuint> textureCache;
    std::unordered_map<const Mesh*, GLMeshResource> meshResourceCache;
    GLuint defaultTexture = 0;

    bool setupShaders();
    void uploadMesh(Mesh& mesh);
    GLuint uploadTexture(const Texture& texture);
    void createDefaultTexture();
};

