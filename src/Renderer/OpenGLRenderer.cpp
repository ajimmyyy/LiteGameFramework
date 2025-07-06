//
// Created by jimmy on 2025/6/29.
//

#include "../../include/Renderer/OpenGLRenderer.h"
#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

OpenGLRenderer::OpenGLRenderer(IWindow* win)
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
    glfwGetFramebufferSize(static_cast<GLFWwindow*>(window->getNativeHandle()), &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    // 綁定 framebuffer size callback
    glfwSetFramebufferSizeCallback(
        static_cast<GLFWwindow*>(window->getNativeHandle()),
        [](GLFWwindow* win, int width, int height) {
            glViewport(0, 0, width, height);
    });

    // 設定shaders
    if (!setupShaders()) return false;

    // 設定Text
    if (!setupText()) return false;

    // 開啟深度測試
    glEnable(GL_DEPTH_TEST);

    // 開啟混和
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 預設相機設置
    viewMatrix = glm::lookAt(
        glm::vec3(0, 0, 5),
        glm::vec3(0),
        glm::vec3(0, 1, 0)
        );
    projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f / 3.f, 0.1f, 100.f);

    // 設置文字框位置
    int width, height;
    window->getSize(width, height);
    orthoMatrix = glm::ortho(
        0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height)
    );

    // 預設材質
    createDefaultTexture();

    return true;
}

bool OpenGLRenderer::setupShaders() {
    // === model shader ===
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

    // === Text shader ===
    const char* textVertexShaderSrc = R"(
        #version 330 core
        layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

        out vec2 TexCoord;

        uniform mat4 projection;

        void main() {
            gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
            TexCoord = vertex.zw;
        }
    )";

    const char* textFragmentShaderSrc = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;

        uniform sampler2D text;
        uniform vec3 textColor;

        void main() {
            float alpha = texture(text, TexCoord).r;
            FragColor = vec4(textColor, alpha);
        }
    )";

    GLuint textVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(textVertexShader, 1, &textVertexShaderSrc, nullptr);
    glCompileShader(textVertexShader);
    // TODO: 錯誤檢查

    GLuint textFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(textFragmentShader, 1, &textFragmentShaderSrc, nullptr);
    glCompileShader(textFragmentShader);
    // TODO: 錯誤檢查

    textShaderProgram = glCreateProgram();
    glAttachShader(textShaderProgram, textVertexShader);
    glAttachShader(textShaderProgram, textFragmentShader);
    glLinkProgram(textShaderProgram);

    glDeleteShader(textVertexShader);
    glDeleteShader(textFragmentShader);

    return true;
}

bool OpenGLRenderer::setupText() {
    // setup freeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";
        return false;
    }

    // 載入字型
    FT_Face face;
    if (FT_New_Face(ft, "../assets/fonts/arial.ttf", 0, &face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font\n";
        FT_Done_FreeType(ft);
        return false;
    }
    // 設定像素大小
    FT_Set_Pixel_Sizes(face, 0, 48);

    // 啟用字元對齊
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // === 3. 載入前128個 ASCII 字元 ===
    for (unsigned char c = 0; c < 128; c++) {
        // 載入字型 glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYPE: Failed to load Glyph " << c << "\n";
            continue;
        }

        // 建立 OpenGL texture
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 建立 Character
        Character ch;
        ch.textureID = tex;
        ch.metrics.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        ch.metrics.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        ch.metrics.advance = face->glyph->advance.x;

        characterCache.insert(std::pair<char, Character>(c, ch));
    }

    // 清除
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

void OpenGLRenderer::drawText(const std::string& text, float x, float y, glm::vec3 color, float scale) {
    glDisable(GL_DEPTH_TEST);

    glUseProgram(textShaderProgram);
    glUniform3f(glGetUniformLocation(textShaderProgram, "textColor"), color.r, color.g, color.b);
    glUniformMatrix4fv(glGetUniformLocation(textShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(orthoMatrix));
    glUniform1i(glGetUniformLocation(textShaderProgram, "text"), 0);
    glActiveTexture(GL_TEXTURE0);

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    for (char c : text) {
        const auto& charData = characterCache[c];
        const auto& metrics = charData.metrics;

        float xpos = x + metrics.bearing.x * scale;
        float ypos = y - (metrics.size.y - metrics.bearing.y) * scale;
        float w = metrics.size.x * scale;
        float h = metrics.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, charData.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (metrics.advance >> 6) * scale;
    }

    // 釋放vao, vbo
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glEnable(GL_DEPTH_TEST);
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

void OpenGLRenderer::createDefaultTexture() {
    glGenTextures(1, &defaultTexture);
    glBindTexture(GL_TEXTURE_2D, defaultTexture);

    unsigned char whitePixel[4] = { 255, 255, 255, 255 };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}