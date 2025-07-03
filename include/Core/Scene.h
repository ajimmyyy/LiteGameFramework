//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>

#include "../ECS/ECSWorld.h"
#include "../Renderer/IRenderer.h"
#include "../Platform/IWindow.h"

class Scene {
public:
    void init(IWindow* window, IRenderer* renderer);
    void update(float deltaTime) const;
    void render(float alpha) const;
    [[nodiscard]] ECSWorld& getECSWorld() const;

private:
    std::unique_ptr<ECSWorld> world;
    IRenderer* renderer = nullptr;
};