//
// Created by jimmy on 2025/6/28.
//

#include "../../../include/ECS/Systems/RenderSystem.h"
#include "../../../include/Renderer/IRenderer.h"
#include <ranges>

RenderSystem::RenderSystem(IRenderer* renderer, EntityManager* entityManager)
    : renderer(renderer), entityManager(entityManager) {}

void RenderSystem::render(float alpha) {
    renderer->beginFrame();

    auto& map = entityManager->getComponentMap<RenderComponent>();
    for (auto& rc : map | std::views::values) {
        if (rc.model) {
            if (rc.texture) {
                renderer->draw(*rc.model, *rc.texture);
            } else {
                renderer->draw(*rc.model);
            }
        }
    }

    renderer->endFrame();
}