//
// Created by jimmy on 2025/6/29.
//

#include "../../include/Renderer/OpenGLRenderer.h"
#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

OpenGLRenderer::OpenGLRenderer(WindowGLFW* win)
    : viewMatrix(1.0f), projectionMatrix(1.0f) {
    window = win;
}

OpenGLRenderer::~OpenGLRenderer() {
    OpenGLRenderer::shutdown();
}

bool OpenGLRenderer::initialize() {
    // 初始化OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return false;
    }

    // 設定 viewport
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window->getWindow(), &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // 綁定 framebuffer size callback
    glfwSetFramebufferSizeCallback(window->getWindow(), framebufferSizeCallback);

    // 設定shaders
    if (!setupShaders()) return false;

    // 開啟深度測試
    glEnable(GL_DEPTH_TEST);

    // 預設相機設置
    viewMatrix = glm::lookAt(
        glm::vec3(0, 0, 5),
        glm::vec3(0),
        glm::vec3(0, 1, 0)
        );
    projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f / 3.f, 0.1f, 100.f);

    // 預設材質
    createDefaultTexture();

    return true;
}

bool OpenGLRenderer::setupShaders() {
    // 硬編碼的 shader，用於測試
    const char* vertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aTexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec2 TexCoord;

        void main() {
            TexCoord = aTexCoord;
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;
        uniform sampler2D texture1;

        void main() {
            FragColor = texture(texture1, TexCoord);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);
    // TODO: 加入錯誤檢查

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);
    // TODO: 加入錯誤檢查

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void OpenGLRenderer::shutdown() {
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }

    if (window) {
        window->shutdown();
        window = nullptr;
    }
}

void OpenGLRenderer::beginFrame() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::endFrame() {
    window->swapBuffers();
}

void OpenGLRenderer::draw(Model& model, const Texture& texture) {
    glUseProgram(shaderProgram);

    // 設定 MVP
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

    auto identity = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // 貼圖
    GLuint texId = uploadTexture(texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    for (auto& mesh : model.meshes) {
        if (!meshResourceCache.contains(&mesh)) {
            uploadMesh(mesh);
        }

        const auto& res = meshResourceCache[&mesh];
        glBindVertexArray(res.vao);
        glDrawElements(GL_TRIANGLES, res.indexCount, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

void OpenGLRenderer::draw(Model& model) {
    glUseProgram(shaderProgram);

    // 設定 MVP
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc  = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc  = glGetUniformLocation(shaderProgram, "projection");

    auto identity = glm::mat4(1.0f);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(identity));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, defaultTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    for (auto& mesh : model.meshes) {
        if (!meshResourceCache.contains(&mesh)) {
            uploadMesh(mesh);
        }

        const auto& res = meshResourceCache[&mesh];
        glBindVertexArray(res.vao);
        glDrawElements(GL_TRIANGLES, res.indexCount, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

void OpenGLRenderer::setViewMatrix(const glm::mat4& view, const glm::mat4& projection) {
    viewMatrix = view;
    projectionMatrix = projection;
}

GLuint OpenGLRenderer::uploadTexture(const Texture& texture) {
    if (auto it = textureCache.find(texture.name); it != textureCache.end()) {
        return it->second;
    }

    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0,
                 texture.channels == 4 ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, texture.pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    textureCache[texture.name] = texId;
    return texId;
}

void OpenGLRenderer::uploadMesh(Mesh& mesh) {
    if (meshResourceCache.contains(&mesh)) return;

    GLMeshResource res;
    res.indexCount = static_cast<GLsizei>(mesh.indices.size());

    glGenVertexArrays(1, &res.vao);
    glGenBuffers(1, &res.vbo);
    glGenBuffers(1, &res.ebo);

    glBindVertexArray(res.vao);

    glBindBuffer(GL_ARRAY_BUFFER, res.vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    meshResourceCache[&mesh] = res;
}

void OpenGLRenderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::createDefaultTexture() {
    glGenTextures(1, &defaultTexture);
    glBindTexture(GL_TEXTURE_2D, defaultTexture);

    unsigned char whitePixel[4] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
