//
// Created by jimmy on 2025/7/3.
//

#include "../../include/Input/KeyBoardState.h"

void KeyBoardState::setKey(const KeyCode code, const bool isDown) {
    keyMap[code] = isDown;
}

bool KeyBoardState::isKeyDown(const KeyCode code) const {
    auto it = keyMap.find(code);
    return it != keyMap.end() && it->second;
}