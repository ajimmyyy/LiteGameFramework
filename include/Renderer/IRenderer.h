//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "../Resources/Model.h"
#include "../Resources/Texture.h"

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void beginFrame() = 0;
    virtual void endFrame() = 0;

    // 繪製模型,貼圖
    virtual void draw(Model& model, const Texture& texture) = 0;
    virtual void draw(Model& model) = 0;

    // 設定相機、光源
    virtual void setViewMatrix(const glm::mat4& view, const glm::mat4& projection) = 0;

    // 提供初始化、釋放資源的方法
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
};