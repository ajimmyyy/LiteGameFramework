#include <iostream>

#include "cmake-build-debug/_deps/catch2-src/src/catch2/internal/catch_stdstreams.hpp"
#include "include/Core/Game.h"
#include "include/ECS/Components/CameraComponent.h"
#include "include/ECS/Components/InputComponent.h"
#include "include/ECS/Components/RenderComponent.h"
#include "include/ECS/Components/TextComponent.h"
#include "include/ECS/Tags/MainCameraTag.h"
#include "include/Input/KeyCode.h"

int main(int argc, char** argv) {
    // init
    Game* game = new Game;
    game->init();

    ECSWorld world = game->getECSWorld();
    EntityManager entityManager = world.getEntityManager();

    // create entity
    auto teapot_e = entityManager.createEntity();
    auto teapot_c = RenderComponent(
        ResourceManager::loadModel("../assets/models/teapot.obj")
    );
    entityManager.addComponent(teapot_e, teapot_c);

    auto camera_e = entityManager.createEntity();
    auto camera_c = CameraComponent{
        .position = glm::vec3(0.0f, 0.0f, 200.0f),
        .mode = CameraMode::LookAtTarget,
    };
    entityManager.addComponent(camera_e, camera_c);
    entityManager.addComponent(camera_e, MainCameraTag{});

    auto input_c = InputComponent();
    {
        // 初始狀態
        input_c.keys[KeyCode::W] = KeyState::Up;
        input_c.keys[KeyCode::S] = KeyState::Up;
        input_c.keys[KeyCode::A] = KeyState::Up;
        input_c.keys[KeyCode::D] = KeyState::Up;
        input_c.keys[KeyCode::Space] = KeyState::Up;
        input_c.keys[KeyCode::LeftShift] = KeyState::Up;

        // 對應動作
        input_c.keyToAction[KeyCode::W] = "MoveForward";
        input_c.keyToAction[KeyCode::S] = "MoveBackward";
        input_c.keyToAction[KeyCode::A] = "MoveLeft";
        input_c.keyToAction[KeyCode::D] = "MoveRight";
        input_c.keyToAction[KeyCode::Space] = "MoveUp";
        input_c.keyToAction[KeyCode::LeftShift] = "MoveDown";

        // callback
        input_c.actions["MoveForward"] = InputAction{
            "MoveForward",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(0, 0, -1.0f);
            },
            nullptr
        };
        input_c.actions["MoveBackward"] = InputAction{
            "MoveBackward",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(0, 0, 1.0f);
            },
            nullptr
        };
        input_c.actions["MoveLeft"] = InputAction{
            "MoveLeft",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(-1.0f, 0, 0);
            },
            nullptr
        };
        input_c.actions["MoveRight"] = InputAction{
            "MoveRight",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(1.0f, 0, 0);
            },
            nullptr
        };
        input_c.actions["MoveUp"] = InputAction{
            "MoveUp",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(0, 1.0f, 0);
            },
            nullptr
        };
        input_c.actions["MoveDown"] = InputAction{
            "MoveDown",
            nullptr,
            [camera_e, &entityManager]() {
                auto& cam = entityManager.getComponent<CameraComponent>(camera_e);
                cam.position += glm::vec3(0, -1.0f, 0);
            },
            nullptr
        };
    }
    entityManager.addComponent(camera_e, input_c);



    game->run();
}