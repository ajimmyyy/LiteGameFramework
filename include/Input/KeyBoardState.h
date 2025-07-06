//
// Created by jimmy on 2025/7/3.
//

#pragma once
#include <unordered_map>

#include "KeyCode.h"

class KeyBoardState {
public:
    void setKey(KeyCode code, bool isDown);
    bool isKeyDown(KeyCode code) const;

private:
    std::unordered_map<KeyCode, bool> keyMap;
};
