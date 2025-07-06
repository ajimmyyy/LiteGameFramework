//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/Scene.h"

void Scene::init(IWindow* window, IRenderer* renderer, InputManager* inputManager) {
    this->renderer = renderer;
    world = std::make_unique<ECSWorld>();
    world->init(window, renderer, inputManager);
}

void Scene::update(float deltaTime) const {
    world->update(deltaTime);
}

void Scene::render(float alpha) const {
    world->render(alpha);
}

ECSWorld& Scene::getECSWorld() const {
    assert(world && "ECSWorld must not be null");
    return *world;
}