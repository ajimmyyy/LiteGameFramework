//
// Created by jimmy on 2025/6/28.
//

#pragma once

#include "../Resources/Model.h"
#include "../Resources/Texture.h"

class IRenderer {
public:
    virtual ~IRenderer() = default;

    // 繪製模型,貼圖
    virtual void draw(Model& model, const Texture& texture) = 0;

    // 設定相機、光源
    // virtual void setViewMatrix(const Matrix4& view) = 0;
    // virtual void setProjectionMatrix(const Matrix4& proj) = 0;

    // 提供初始化、釋放資源的方法
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
};