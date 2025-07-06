//
// Created by jimmy on 2025/7/3.
//

#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <glm/glm.hpp>

#include "../../Input/KeyCode.h"

enum class KeyState {
    Up,
    Down,
    Held
};

struct InputAction {
    std::string name;

    std::function<void()> onPressed = [](){};
    std::function<void()> onHeld = [](){};
    std::function<void()> onReleased = [](){};

    InputAction() = default;

    InputAction(
        const std::string& name,
        std::function<void()> onPressed,
        std::function<void()> onHeld,
        std::function<void()> onReleased)
        : name(name),
          onPressed(onPressed ? onPressed : [](){}),
          onHeld(onHeld ? onHeld : [](){}),
          onReleased(onReleased ? onReleased : [](){}) {}
};

struct InputComponent {
    // key, keyState
    std::unordered_map<KeyCode, KeyState> keys;

    // key -> action name
    std::unordered_map<KeyCode, std::string> keyToAction;

    // action name -> action callback
    std::unordered_map<std::string, InputAction> actions;

    // 滑鼠位置
    float mouseX = 0.0f;
    float mouseY = 0.0f;

    // 是否有滑鼠移動
    bool mouseMoved = false;

    // 上一幀滑鼠位置
    float lastMouseX = 0.0f;
    float lastMouseY = 0.0f;

    InputComponent() = default;
};