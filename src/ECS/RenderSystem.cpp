//
// Created by jimmy on 2025/6/28.
//

#include "../../include/ECS/RenderSystem.h"
#include "../../include/Renderer/IRenderer.h"
#include <ranges>

RenderSystem::RenderSystem(IRenderer* renderer, EntityManager* entityManager)
    : renderer(renderer), entityManager(entityManager) {}

void RenderSystem::update() {
    auto& map = entityManager->getComponentMap<RenderComponent>();
    for (auto& rc : map | std::views::values) {
        if (rc.model && rc.texture) {
            renderer->draw(*rc.model, *rc.texture);
        }
    }
}