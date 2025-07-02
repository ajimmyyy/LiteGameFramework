//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>

#include "../Renderer/IRenderer.h"
#include "SceneManager.h"
#include "GameLoop.h"

class Game {
public:
    void init();
    void run() const;
    void shutdown();

private:
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<GameLoop> gameLoop;
};

