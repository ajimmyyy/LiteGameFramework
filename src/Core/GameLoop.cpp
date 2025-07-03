//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/GameLoop.h"
#include "../../include/Core/SceneManager.h"
#include "../../include/Platform/ITime.h"

GameLoop::GameLoop(SceneManager* sm, std::unique_ptr<ITime> t, std::unique_ptr<IPlatform> p)
    : sceneManager(sm), time(std::move(t)), platform(std::move(p)) {
    lastFrameTime = time->getTime();
}

void GameLoop::run() {
    while (!platform->shouldExit()) {
        float dt = calculateDeltaTime();
        accumulator += dt;

        while (accumulator >= fixedDelta) {
            sceneManager->update(dt);
            accumulator -= fixedDelta;
        }

        float alpha = accumulator / fixedDelta;
        sceneManager->render(alpha);

        platform->pollEvents();
    }
}

float GameLoop::calculateDeltaTime() {
    float now = time->getTime();
    float delta = now - lastFrameTime;
    lastFrameTime = now;
    return delta;
}