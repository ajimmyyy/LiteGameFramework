//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/SceneManager.h"

void SceneManager::loadInitialScene(IRenderer* renderer) {
    currentScene = std::make_unique<Scene>();
    currentScene->init(renderer);
}

void SceneManager::update(float deltaTime) const {
    if (currentScene) currentScene->update(deltaTime);
}

void SceneManager::render(float alpha) const {
    if (currentScene) currentScene->render(alpha);
}
