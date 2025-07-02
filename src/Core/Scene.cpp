//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/Scene.h"

void Scene::init(IRenderer* renderer) {
    this->renderer = renderer;
    world = std::make_unique<ECSWorld>();
    world->init(renderer);
}

void Scene::update(float deltaTime) const {
    world->update(deltaTime);
}

void Scene::render(float alpha) const {
    world->render(alpha);
}
