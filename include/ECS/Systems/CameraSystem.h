//
// Created by jimmy on 2025/7/3.
//

#pragma once

#include <optional>

#include "ISystem.h"
#include "../Components/CameraComponent.h"
#include "../Tags/MainCameraTag.h"
#include "../../Platform/IWindow.h"
#include "../../Renderer/IRenderer.h"
#include "../EntityManager.h"

class CameraSystem : public ISystem {
public:
    CameraSystem(IWindow* window, IRenderer* renderer, EntityManager* entityManager);

    void update(float deltaTime) override;

private:
    IWindow* window;
    IRenderer* renderer;
    EntityManager* entityManager;
    std::optional<Entity> mainCameraEntity;
};
