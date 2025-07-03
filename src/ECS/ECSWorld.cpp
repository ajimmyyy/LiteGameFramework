//
// Created by jimmy on 2025/6/28.
//

#include "../../include/ECS/ECSWorld.h"

#include "../../include/ECS/Systems/CameraSystem.h"
#include "../../include/ECS/Systems/RenderSystem.h"

ECSWorld::ECSWorld() = default;

void ECSWorld::init(IWindow* window, IRenderer* renderer) {
    // addUpdateSystem(std::make_unique<InputSystem>());
    addRenderSystem(std::make_unique<RenderSystem>(renderer, &entityManager));
    addUpdateSystem(std::make_unique<CameraSystem>(window, renderer, &entityManager));
}

void ECSWorld::addUpdateSystem(const std::shared_ptr<ISystem>& system) {
    updateSystems.push_back(system);
}

void ECSWorld::addRenderSystem(const std::shared_ptr<IRenderSystem>& renderSystem) {
    renderSystems.push_back(renderSystem);
}

void ECSWorld::update(float deltaTime) const {
    for (auto& sys : updateSystems) {
        sys->update(deltaTime);
    }
}

void ECSWorld::render(float alpha) const {
    for (auto& sys : renderSystems) {
        sys->render(alpha);
    }
}

EntityManager& ECSWorld::getEntityManager() {
    return entityManager;
}
