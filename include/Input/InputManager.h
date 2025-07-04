//
// Created by jimmy on 2025/7/3.
//

#pragma once
#include "KeyBoardState.h"
#include "MouseState.h"

class InputManager {
public:
    KeyBoardState& getKeyState();
    MouseState& getMouseState();

    void onKey(KeyCode key, bool isDown);
    void onMouseMove(float x, float y);

private:
    KeyBoardState keyState;
    MouseState mouseState;
};
