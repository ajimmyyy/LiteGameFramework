//
// Created by jimmy on 2025/7/3.
//

#include <ranges>

#include "../../include/ECS/Systems/InputSystem.h"

void InputSystem::update(float deltaTime) {
    auto& components = entityManager->getComponentMap<InputComponent>();

    for (auto &input: components | std::views::values) {
        input.mouseMoved = false;

        // 更新滑鼠位置
        float x = inputManager->getMouseState().x;
        float y = inputManager->getMouseState().y;
        if (input.mouseX != x || input.mouseY != y) {
            input.mouseMoved = true;
        }
        input.mouseX = x;
        input.mouseY = y;

        // 更新按鍵狀態
        for (auto& [key, state] : input.keys) {
            bool isDown = inputManager->getKeyState().isKeyDown(key);
            if (isDown) {
                if (state == KeyState::Up)
                    state = KeyState::Down;
                else
                    state = KeyState::Held;
            } else {
                state = KeyState::Up;
            }
        }

        // action callback
        for (auto& [key, actionName] : input.keyToAction) {
            auto it = input.actions.find(actionName);
                if (it != input.actions.end()) {
                switch (input.keys[key]) {
                    case KeyState::Up:
                        it->second.onReleased();
                        break;
                    case KeyState::Down:
                        it->second.onPressed();
                        break;
                    case KeyState::Held:
                        it->second.onHeld();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}