//
// Created by jimmy on 2025/7/4.
//

#include "../../include/ECS/Systems/TextRenderSystem.h"

#include <ranges>

TextRenderSystem::TextRenderSystem(IRenderer* renderer, EntityManager* entityManager)
    : renderer(renderer), entityManager(entityManager) {}

void TextRenderSystem::render(float alpha) {
    auto& texts = entityManager->getComponentMap<TextComponent>();
    for (auto &text: texts | std::views::values) {
        if (text.visible) {
            renderer->drawText(
                text.content,
                text.screenPosition.x,
                text.screenPosition.y,
                text.color,
                text.scale
            );
        }
    }
}