//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>
#include "Scene.h"
#include "../Renderer/IRenderer.h"
#include "../Platform/IWindow.h"
#include "../Input/InputManager.h"

class SceneManager {
public:
    void loadInitialScene(IWindow* window, IRenderer* renderer, InputManager* inputManager);
    void update(float deltaTime) const;
    void render(float alpha) const;
    [[nodiscard]] ECSWorld& getECSWorld() const;

private:
    std::unique_ptr<Scene> currentScene;
};
