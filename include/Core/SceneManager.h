//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>
#include "Scene.h"
#include "../Renderer/IRenderer.h"

class SceneManager {
public:
    void loadInitialScene(IRenderer* renderer);
    void update(float deltaTime) const;
    void render(float alpha) const;

private:
    std::unique_ptr<Scene> currentScene;
};
