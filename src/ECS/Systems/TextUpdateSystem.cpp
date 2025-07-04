//
// Created by jimmy on 2025/7/4.
//

#include "../../include/ECS/Systems/TextUpdateSystem.h"

#include <ranges>

void TextUpdateSystem::update(float deltaTime) {
    auto& texts = entityManager->getComponentMap<TextComponent>();

    for (auto &text: texts | std::views::values) {
        if (text.generator)
            text.content = text.generator();
    }
}

