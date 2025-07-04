//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/SceneManager.h"

void SceneManager::loadInitialScene(IWindow* window, IRenderer* renderer, InputManager* inputManager) {
    currentScene = std::make_unique<Scene>();
    currentScene->init(window, renderer, inputManager);
}

void SceneManager::update(float deltaTime) const {
    if (currentScene) currentScene->update(deltaTime);
}

void SceneManager::render(float alpha) const {
    if (currentScene) currentScene->render(alpha);
}

ECSWorld& SceneManager::getECSWorld() const {
    return currentScene->getECSWorld();
}