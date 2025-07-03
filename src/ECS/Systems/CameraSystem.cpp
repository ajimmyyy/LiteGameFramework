//
// Created by jimmy on 2025/7/3.
//

#include "../../../include/ECS/Systems/CameraSystem.h"

#include <iostream>
#include <ranges>

CameraSystem::CameraSystem(IWindow* window, IRenderer* renderer, EntityManager* entityManager):
window(window), renderer(renderer), entityManager(entityManager) {}

void CameraSystem::update(float deltaTime) {
    auto& cameras = entityManager->getComponentMap<CameraComponent>();
    auto& mainCameraTags = entityManager->getComponentMap<MainCameraTag>();

    int w, h;
    window->getSize(w, h);

    for (auto &camera: cameras | std::views::values) {
        camera.aspect = static_cast<float>(w) / static_cast<float>(h);
        camera.updateMatrices();
    }

    // 檢查
    if (mainCameraTags.empty()) {
        std::cerr << "[CameraSystem] Warning: No entity has MainCameraTag!\n";
        return;
    }

    if (mainCameraTags.size() > 1) {
        std::cerr << "[CameraSystem] Warning: Multiple entities have MainCameraTag!\n";
    }

    for (const auto &entity: mainCameraTags | std::views::keys) {
        if (cameras.contains(entity)) {
            const auto& camera = cameras.at(entity);
            renderer->setViewMatrix(camera.viewMatrix, camera.projectionMatrix);
        } else {
            std::cerr << "[CameraSystem] Warning: Entity with MainCameraTag has no CameraComponent!\n";
        }
        break;
    }
}