//
// Created by jimmy on 2025/7/3.
//

#include "../../include/Input/InputManager.h"

KeyBoardState& InputManager::getKeyState() {
    return keyState;
}

MouseState& InputManager::getMouseState() {
    return mouseState;
}

void InputManager::onKey(const KeyCode key, const bool isDown) {
    keyState.setKey(key, isDown);
}

void InputManager::onMouseMove(const float x, const float y) {
    mouseState.x = x;
    mouseState.y = y;
}