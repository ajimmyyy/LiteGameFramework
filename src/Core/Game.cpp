//
// Created by jimmy on 2025/6/30.
//

#include "../../include/Core/Game.h"
#include "../../include/Core/SceneManager.h"
#include "../../include/Core/GameLoop.h"
#include "../../include/Utils/PlatformEnvFactory.h"
#include "../../include/Utils/Config.h"

#include <iostream>

void Game::init() {
    Config config = Config::load("../config.json");

    std::cout << "[Game] Initializing...\n";

    // 建立平台環境
    auto env = PlatformEnvFactory::create(
        config.getPlatformType(),
        config.getWindowWidth(),
        config.getWindowHeight(),
        config.getWindowTitle()
    );

    if (!env.platform || !env.time || !env.renderer) {
        std::cerr << "[Game] Failed to initialize platform environment!\n";
        return;
    }
    std::cout << "[Game] Initialized platform environment\n";

    // 初始化渲染器
    renderer = std::move(env.renderer);
    if (!renderer || !renderer->initialize()) {
        std::cerr << "[Game] Failed to initialize renderer!\n";
        return;
    }
    std::cout << "[Game] Initialized renderer\n";

    // 建立場景管理器並載入預設場景
    sceneManager = std::make_unique<SceneManager>();
    sceneManager->loadInitialScene(renderer.get());

    // 建立並設定主循環
    gameLoop = std::make_unique<GameLoop>(
        sceneManager.get(),
        std::move(env.time),
        std::move(env.platform)
    );

    std::cout << "[Game] Initialized.\n";
}

void Game::run() const {
    if (gameLoop)
        gameLoop->Run();
}

void Game::shutdown() {
    std::cout << "[Game] Shutting down...\n";
    if (renderer) {
        renderer->shutdown();
    }
    gameLoop.reset();
    sceneManager.reset();
    renderer.reset();
    std::cout << "[Game] Shutdown complete.\n";
}
