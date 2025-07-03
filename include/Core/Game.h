//
// Created by jimmy on 2025/6/30.
//

#pragma once
#include <memory>

#include "../Resources/ResourceManager.h"
#include "../Renderer/IRenderer.h"
#include "SceneManager.h"
#include "GameLoop.h"

class Game {
public:
    void init();
    void run() const;
    void shutdown();
    [[nodiscard]] ECSWorld& getECSWorld() const;

private:
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<GameLoop> gameLoop;
};

