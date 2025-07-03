//
// Created by jimmy on 2025/6/30.
//

#pragma once

#include "SceneManager.h"
#include "../Platform/ITime.h"
#include "../Platform/IPlatform.h"

class GameLoop {
public:
    GameLoop(SceneManager* sceneManager, std::unique_ptr<ITime> t, std::unique_ptr<IPlatform> p);
    void run();

private:
    SceneManager* sceneManager;
    std::unique_ptr<IPlatform> platform;
    std::unique_ptr<ITime> time;

    const float fixedDelta = 1.0f / 60.0f;
    float accumulator = 0.0f;
    float lastFrameTime = 0.0f;

    float calculateDeltaTime();
};